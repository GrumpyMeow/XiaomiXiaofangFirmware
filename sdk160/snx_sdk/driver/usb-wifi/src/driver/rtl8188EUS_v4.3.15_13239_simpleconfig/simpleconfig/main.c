#include<string.h>    //memset
#include <stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <netinet/ether.h>
#include <pthread.h>
#include <signal.h>
#include "sc_common.h"
#ifdef PLATFORM_MSTAR
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

#define DEFAULT_WLAN_BAND "bgn" //abgn

#define BUF_SIZ 10240

#define DEST_MAC0 0x01
#define DEST_MAC1 0x00
#define DEST_MAC2 0x5e

static void ProcessPacket(unsigned char* , int);
int collect_scanres();
void* doRecvfrom();


u8 g_abort = FALSE, g_reinit;
char ifName[IFNAMSIZ];
const unsigned char bc_mac[6]={0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const char *flag_str[] = {	"SC_SCAN", "SC_SAVE_PROFILE", "SC_DEL_PROFILE",
				"SC_RENAME", "SC_SUCCESS_ACK" };
char g_wpafile_path[512];



//   =====================	Custimize part	====================================

//const u8 def_chPlan[]= {1,6,11,2,3,4,5,7,8,9,10,12,13,36,40,44,48,52,56,60,64,100,104,108,112,116,132,136,140,149,153,157,161,165};
const u8 def_chPlan[]= {1, 6, 11};
#define MAX_CHNUM		50

#define DEFAULT_IF		"wlan0"
#define DEFAULT_WPAFILE_PATH	"./wpa.conf"
#define DEFAULT_DEVICE_NAME	"RTK_SC_DEV"
#define DEFAULT_PIN		"57289961"
#define DEFAULT_PRIVECMD 	"iwconfig"

#define	PATTERN_ADDRESS		"Address:"
#define	PATTERN_ESSID		"ESSID"
#define	PATTERN_CHANNEL		"Channel"
#define	PATTERN_ENCRYPTION	"Encryption"
#define	PATTERN_ISWPA		"WPA"
#define MAX_LINE_LEN		1024
#define MAX_SCAN_TIMES		10

#define SIG_SCPBC		SIGUSR1


#ifdef PLATFORM_MSTAR
int MSTAR_SYSTEM(const char * cmdstring)
{
    pid_t pid;
    int status;
 
    if (cmdstring == NULL) {
        return (1);
    }
 
    if ((pid = fork())<0) {
        status = -1;
    } else if (pid == 0) {
        execl("/sbin/busybox", "sh", "-c", cmdstring, (char *)0);	//Aries , ms918
        //execl("/system/xbin/busybox", "sh", "-c", cmdstring, (char *)0);
        exit(127);
    } else {
        sleep(1);
        while (waitpid(pid, &status, 0) < 0){
            if (errno != EINTR) {
                status = -1;
                break;
            }
        }
    }
 
    return status;
}
#endif

inline void RTK_SYSTEM(const char *cmd)
{
	DEBUG_PRINT("shell:  %s\n", cmd);
#ifdef	PLATFORM_MSTAR
	MSTAR_SYSTEM(cmd);
#else
	system(cmd);
#endif
}

/*
description:	the way of system to connect to tartget AP.
*/
int connect_ap()
{
	char cmdstr[200];

#ifndef ANDROID_ENV
#ifdef CONFIG_IOCTL_CFG80211
	sprintf(cmdstr, "./wpa_supplicant -i %s -c %s -Dnl80211 &", ifName, g_wpafile_path);
#else
	sprintf(cmdstr, "wpa_supplicant -i %s -c %s -Dwext &", ifName, g_wpafile_path);
#endif
	RTK_SYSTEM(cmdstr);
	sleep(5);
#else
	sprintf(cmdstr, "rmmod %s", WIFI_MODULE_NAME);
	RTK_SYSTEM(cmdstr);
	RTK_SYSTEM("svc wifi enable");
#endif
	return 0;
}

/*
description:	the way of system to get IP address.
*/
int request_ip()
{
	char cmdstr[250];
	
	//sprintf(cmdstr, "ifconfig %s 192.168.9.189", ifName);
	sprintf(cmdstr, "udhcpc -i %s ", ifName);
	RTK_SYSTEM(cmdstr);
	sleep(3);
	return 0;
}

/*
input:	@fd		: socket
	@buf		: received control request.
output:	@ctrl_cmd		: AP's ssid
	@accept_control	: <"on"/"off"> , AP's security
description:	parse the received control request and send corresponding response, 
	return 1 if receive a SC_SUCCESS_ACK, otherwise return 0. 
*/
static int ctrlmsg_handler(int fd, char *buf, int *ctrl_cmd, int *accept_control)
{
	int status = rtk_sc_valid_ctrlframe(buf);
	int flag;
	char dev_name[64];

	flag = rtk_sc_get_ctrlmsg_value(buf, CTRLMSG_DATAID_FLAG);
	DEBUG_PRINT("sockfd_ctrl!!  flag=%s \n", flag_str[flag]);
	switch(flag){
	case SC_SAVE_PROFILE:
		if(! (*accept_control))
			break;
		*ctrl_cmd = SC_SAVE_PROFILE;
		*accept_control = 0;
		rtw_sc_send_response_msg(fd, buf, SC_RSP_SAVE, status);
		break;
	case SC_DEL_PROFILE:
		if(! (*accept_control))
			break;
		*accept_control = 0;
		*ctrl_cmd  = SC_DEL_PROFILE;
//		reinit = SC_REINIT_WLAN;
		rtw_sc_send_response_msg(fd, buf, SC_RSP_DEL, status);
		break;
	case SC_RENAME:
		if(! (*accept_control))
			break;
		*accept_control = 0;
		*ctrl_cmd = SC_RENAME;
		rtk_sc_get_ctrlmsg_string(buf, CTRLMSG_DATAID_DEVICE_NAME, dev_name);
		rtk_sc_set_string_value(SC_DEVICE_NAME, dev_name);
		rtw_sc_send_response_msg(fd, buf, SC_RSP_RENAME, status);
		break;
	case SC_SUCCESS_ACK:
		DEBUG_PRINT("SC_SUCCESS_ACK! \n");
		return 1;
		break;
	default:
		DEBUG_PRINT("invalid request\n");
		rtw_sc_send_response_msg(fd, buf, SC_RSP_INVALID, 0);
		break;
	}
	return 0;
}

static void do_ctrl_cmd(int ctrl_cmd)
{
	char cmdstr[200];
	
	switch(ctrl_cmd) {
	case SC_SAVE_PROFILE:
		collect_scanres();
		break;
	case SC_DEL_PROFILE:
//		if(reinit == SC_REINIT_SYSTEM)
//			RTK_SYSTEM("reboot");
//		else if(reinit == SC_REINIT_WLAN) {
		/*      discard reinit system, always reinit wlan	*/
		sprintf(cmdstr, "rm -rf %s&", g_wpafile_path);
		RTK_SYSTEM(cmdstr);		
		RTK_SYSTEM("killall wpa_supplicant");
		RTK_SYSTEM("killall ping");
		sprintf(cmdstr, "rmmod %s", WIFI_MODULE_NAME);
		RTK_SYSTEM(cmdstr);
		exit(EXIT_SUCCESS);
		break;
	case SC_RENAME:
		break;
	}
}

/*
input:	@filepath		: path of wpa_supplicant config file which need to be stored.
	@ssid		: AP's ssid
	@cfgfile_type	: the security type of AP
	
description:	store the result as  wpa_supplicant config file  in given file path,
*/
int store_cfgfile(const char *filepath, char *ssid, int cfgfile_type)
{
	FILE *fd;

	char commset[]={"update_config=1\nctrl_interface=/var/run/wpa_supplicant\neapol_version=1\nfast_reauth=1\n"};	
	char WPAstr[]={"ap_scan=1\nnetwork={\n\tssid=\"%s\"\n\tscan_ssid=1\n\tpsk=\"%s\"\n}\n"};
	char OPENstr[]={"ap_scan=1\nnetwork={\n\tssid=\"%s\"\n\tkey_mgmt=NONE\n\tscan_ssid=1\n}\n"};
	char WEPstr[]={"ap_scan=1\nnetwork={\n\tssid=\"%s\"\n\tkey_mgmt=NONE\n\twep_key0=\"%s\"\n\twep_tx_keyidx=0\n\tscan_ssid=1\n}\n"};
	char CmdStr[2048], passwd[65];
	
	memset(passwd, 0, 65);
	fd=fopen(filepath, "w+");
	if( fd == NULL ) {
		printf("file open can not create file !!! \n");
		return -ENOENT;
	}
	//sprintf(CmdStr, commset, ifName);
	sprintf(CmdStr, commset);
	fprintf(fd,"%s", CmdStr);
	switch (cfgfile_type) {
	case CFGFILE_OPEN :
		sprintf(CmdStr, OPENstr, ssid);
		break;
	case CFGFILE_WPA :
		rtk_sc_get_string_value(SC_PASSWORD, passwd);
		sprintf(CmdStr, WPAstr, ssid, passwd);
		break;
	case CFGFILE_WEP :
		rtk_sc_get_string_value(SC_PASSWORD, passwd);
		sprintf(CmdStr, WEPstr, ssid, passwd);
		break;
	default :
		return -EINVAL;
		break;
	}
	DEBUG_PRINT("%s\n",CmdStr);
	fprintf(fd,"%s", CmdStr);
	fclose(fd);
	return 0;
}

/*
input:	@scan_res		: path of scan_result file
	@target_bssid	: bssid of target AP
output:	@ssid		: AP's ssid
	@sec		: <"on"/"off"> , AP's security
	@channel		: AP's channel
	@iswpa		: Is AP using WPA security.
	
description:	parse scan_result to get the information of corresponding AP by BSSID.
*/
static int parse_scanres(char *scan_res, char *target_bssid, 
			 char *ssid, char *sec,
			 char *channel, int *iswpa)
{
	char readline[MAX_LINE_LEN];
	char *ch, *name, *value;
	FILE* fp = NULL;
	int found = -EAGAIN;

	fp = fopen(scan_res, "r");
	if (!fp) {
	    printf("%s:Unable to open file [%s] \n", __func__, scan_res);
	    return -ENOENT;
	}
	if (strlen(target_bssid) < 10) {
		printf("%s:Error !! invalid BSSID [%s] \n", __func__, target_bssid);
		return -EINVAL;
	}
	*iswpa = 0;
	while (! feof(fp)) {
		if (fgets(readline, MAX_LINE_LEN , fp)) {
			// BSSID
			if ((ch = strstr(readline, PATTERN_ADDRESS))==NULL)
				continue;
			name = strtok(ch, ": \r\n");
			value = strtok(NULL, " \r\n");
			if (strncasecmp(value , target_bssid, strlen(target_bssid))!=0)
				continue;
			DEBUG_PRINT("BSSID = %s \n", value);
			found = TRUE;

			// SSID
			fgets(readline, MAX_LINE_LEN , fp);
			if ((ch = strstr(readline, PATTERN_ESSID))==NULL)
				continue;
			name = strtok(readline, ": \r\n");
			value = strtok(NULL, "= \r\n");
			value += 1;
			value[strlen(value)-1] = '\0';
			strcpy(ssid, value);
			DEBUG_PRINT("SSID = %s \n", ssid);

			// Channel
			fgets(readline, MAX_LINE_LEN , fp);
			if (!(ch = strstr(readline, PATTERN_CHANNEL)))
				continue;
			if ((name = strtok(ch, " )\r\n"))!=NULL 
				&& ((value = strtok(NULL, " )\r\n"))!=NULL))
				strcpy(channel, value);
			
			DEBUG_PRINT("%s = %s \n", name, channel);
			//Encryption
			fgets(readline, MAX_LINE_LEN , fp);
			if (!(ch = strstr(readline, PATTERN_ENCRYPTION)))
				continue;
			if ((name = strtok(ch, ":\r\n"))!=NULL 
				&& (value = strtok(NULL, ":\r\n"))!=NULL)
				strcpy(sec, value);

			DEBUG_PRINT("%s = %s \n", name, sec);
			// WPA ?
			fgets(readline, MAX_LINE_LEN , fp);
			ch = strstr(readline, PATTERN_ISWPA);
			if (ch)
				*iswpa = 1;
			DEBUG_PRINT("iswpa = %d \n", *iswpa);
			break;

			DEBUG_PRINT("%s \n", readline);
		}
	}
	fclose(fp);
	return found;
}

int collect_scanres()
{
	char cmdstr[250], ssid[64], sec[64], channel[64], target_bssid_str[64], target_bssid[ETH_ALEN];
	int iswpa = 0, ret = -100, i;

	memset(ssid, 0, 64);
	memset(target_bssid, 0, ETH_ALEN);
	memset(target_bssid_str, 0, ETH_ALEN);
	memset(sec, 0, 64);
	memset(channel, 0, 64);
	rtk_sc_get_string_value(SC_BSSID, target_bssid);
	sprintf(target_bssid_str, "%02x:%02x:%02x:%02x:%02x:%02x", 
			(u8)target_bssid[0], (u8)target_bssid[1], (u8)target_bssid[2],
			(u8)target_bssid[3], (u8)target_bssid[4], (u8)target_bssid[5]);
	printf("%s() target_bssid=[%s] \n",__func__, target_bssid_str);
	for (i = 0; i < MAX_SCAN_TIMES; i++) {
		sprintf(cmdstr, "iwlist %s scan | grep -e ESSID -e Channel -e Encryption -e WPA -e \"Address:\" > scan_res", ifName);
		RTK_SYSTEM(cmdstr);
		sleep(2);
		if ((parse_scanres("./scan_res", target_bssid_str, ssid, sec, channel , &iswpa))!=TRUE)
			continue;
		if (strcmp(sec, "on") != 0)
			ret = store_cfgfile(g_wpafile_path, ssid, CFGFILE_OPEN);
		else if (iswpa)
			ret = store_cfgfile(g_wpafile_path, ssid, CFGFILE_WPA);
		else
			ret = store_cfgfile(g_wpafile_path, ssid, CFGFILE_WEP);
		break;
	}
#ifdef ANDROID_ENV
	RTK_SYSTEM("cat ./wpa_conf > /data/misc/wifi/wpa_supplicant.conf");
	RTK_SYSTEM("cat /data/misc/wifi/wpa_supplicant.conf");
	RTK_SYSTEM("chmod 777 /data/misc/wifi/wpa_supplicant.conf");
#endif
	if (ret == -100)
		printf("Error!! bssid:%s not found \n", target_bssid);
	return ret;
}



int run_ping()
{
	char cmdstr[250];
	struct in_addr addr1;

	addr1.s_addr = rtk_sc_get_phoneip();
	sprintf(cmdstr, "ping %s &", inet_ntoa(addr1));
	DEBUG_PRINT("%s\n", cmdstr);
	RTK_SYSTEM(cmdstr);
	return 0;
}



#if defined(SIMPLE_CONFIG_PBC_SUPPORT)
//  monitor HW button (ex: gpio pin) to capture pbc event.
void* pbc_monitor()
{
	while (1) {
	//	if (hw SC_PBC event be triggered) {
	//		kill(getpid(), SIG_SCPBC);
	//		printf("pbc_monitor  trigger \n");	
	//	}
		sleep(1);
	}
	return NULL;
}
#endif

//=====================		Custimize part ending	====================================



#ifdef PROBE_SNIFFER_CH
/*
	description : open & parse the file (scan_res), collect the ap channel list and channel number
	@ap_chlist : A channel list of all AP's channel by parsing scan result
	@ap_chcnt  : How many channels in @ap_chlist
	Note : same channel may be showed several times because the source not be sorted.
*/
static int get_ap_ch_list(char *scan_res, u8 *ap_chlist, int *ap_chcnt)
{
	char readline[MAX_LINE_LEN];
	char *ch, *name, *value;
	FILE* fp = NULL;
	int  channel, last_channel = 0, linecnt = 0;
	
	fp = fopen(scan_res, "r");
	if (!fp) {
	    perror("Error opening file");
	    return -ENOENT;
	}
	if ((!ap_chlist) || (!ap_chcnt))
		return -EINVAL;
	*ap_chcnt = 0;
	while (!feof(fp)) {
		if (fgets(readline, MAX_LINE_LEN , fp)) {
			linecnt++;
			fgets(readline, MAX_LINE_LEN , fp);
			if (!(ch = strstr(readline, PATTERN_CHANNEL)))
				continue;
			if ((name = strtok(ch, " )\r\n"))!=NULL 
				&& ((value = strtok(NULL, " )\r\n"))!=NULL)) {
				channel = atoi(value);
				if (last_channel!=channel) {
					ap_chlist[*ap_chcnt] = channel;
					last_channel = channel;
					(*ap_chcnt)++;
				}
			}
		}
	}
	if (linecnt < 2) {
		DEBUG_PRINT("%s: scan result empty \n", scan_res);
		return -EPERM;
	}

	fclose(fp);
	return 0;
}
/* 
	1. Perform site-survey procedure for 3 times.
	2. Parse scan result to collect all AP's channel in air
	3. Intersect channel list in step2 and default channel plan,  
	    then we got a sniffer channel list.
	    
*/
void probe_chplan(u8 *chlist, int *chnum)	
{
	char cmdstr[250];
	u8 ap_chlist[MAX_CHNUM];
	int i, j, ap_chcnt = 0 , chidx=0;
	int def_chnum = sizeof(def_chPlan)/sizeof(def_chPlan[0]);

//	sprintf(cmdstr, "iwlist %s scan &", ifName);
//	RTK_SYSTEM(cmdstr);
	sprintf(cmdstr, "iwlist %s scan > /dev/null", ifName);
	RTK_SYSTEM(cmdstr);
	sprintf(cmdstr, "iwlist %s scan | grep -e ESSID -e Channel -e Encryption -e WPA > scan_res", ifName);
	RTK_SYSTEM(cmdstr);

	memset(ap_chlist, 0, MAX_CHNUM*sizeof(u8));
        if (get_ap_ch_list("./scan_res", ap_chlist, &ap_chcnt)==0) {
		for (i=0; i<def_chnum; i++) {
			for (j=0; j<ap_chcnt; j++) {
				if (ap_chlist[j] == def_chPlan[i]) {
					chlist[chidx++] = def_chPlan[i];
					break;
				}
			}
		}
		*chnum = chidx;
	} else {
		memcpy(chlist, def_chPlan, MAX_CHNUM);
		*chnum = def_chnum;
	}

	if(g_sc_debug == 2) {
		for (i=0; i<ap_chcnt; i++)
			printf("ap_chlist[%d]:%d \n", i, ap_chlist[i]);
		for (i=0; i<*chnum; i++)
			printf("probe_chplan[%d]:%d \n", i, chlist[i]);
	}
}
#endif

void monitor_mode_onoff(u8 onoff, const char *ifName)
{
	char cmdstr[200];

	//iwconfig wlanX mode monitor
	//iw dev wlanX set type monitor
	memset(cmdstr, 0, sizeof(char)*200);
#ifdef	CONFIG_IOCTL_CFG80211
	if (onoff)
		sprintf(cmdstr,"iw dev %s set type monitor\n", ifName);
	else
		sprintf(cmdstr,"iw dev %s set type auto\n", ifName);
#else
	if (onoff)
		sprintf(cmdstr,"iwconfig %s mode monitor\n", ifName);
	else
		sprintf(cmdstr,"iwconfig %s mode auto\n", ifName);
#endif
	RTK_SYSTEM(cmdstr);
}

static int get_rtheader_len(u8 *buf, size_t len)
{
	struct ieee80211_radiotap_header *rt_header;
	u16 rt_header_size;

	rt_header = (struct ieee80211_radiotap_header *)buf;
	/* check the radiotap header can actually be present */
	if (len < sizeof(struct ieee80211_radiotap_header))
		return -EILSEQ;
	 /* Linux only supports version 0 radiotap format */
	 if (rt_header->it_version)
		return -EILSEQ;
	rt_header_size = le16toh(rt_header->it_len);
	 /* sanity check for allowed length and radiotap length field */
	if (len < rt_header_size)
		return -EILSEQ;
	return rt_header_size;
}


void* doRecvfrom()
{
	int NumTotalPkts;
	int sockopt;
	ssize_t numbytes;
	struct ifreq ifopts;	/* set promiscuous mode */
	u8 buf[BUF_SIZ], *pkt;
	int rt_header_len = 0;

	//Create a raw socket that shall sniff
	/* Open PF_PACKET socket, listening for EtherType ETHER_TYPE */
	if ((sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
		printf("listener: socket"); 
		return NULL;
	}
	/* Set interface to promiscuous mode - do we need to do this every time? */
	strncpy(ifopts.ifr_name, ifName, IFNAMSIZ-1);
	ioctl(sockfd, SIOCGIFFLAGS, &ifopts);

	//memcpy(g_sc_ctx.dmac, ifopts.ifr_hwaddr.sa_data, ETH_ALEN);


	ifopts.ifr_flags |= IFF_PROMISC;
	ioctl(sockfd, SIOCSIFFLAGS, &ifopts);
	/* Allow the socket to be reused - incase connection is closed prematurely */
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
		printf("setsockopt");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	/* Bind to device */
	if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, ifName, IFNAMSIZ-1) == -1)	{
		printf("SO_BINDTODEVICE");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	
	NumTotalPkts=0;
	while(1) {
		numbytes = recvfrom(sockfd, buf, BUF_SIZ, 0, NULL, NULL);
		//printf("listener: got packet %d bytes , total packet Num :%d \n", numbytes,NumTotalPkts);
		if (numbytes < 0) {
			printf("Recvfrom error , failed to get packets\n");
			return NULL;
		}
		if( SC_STATUS_DONE == rtk_sc_get_value(SC_STATUS) )
			return NULL;

		// Get length of Radiotap header 
		if ((rt_header_len = get_rtheader_len(buf, (size_t)numbytes)) < 1)
			continue;
		//Now process the packet
		pkt = (u8 *)buf + rt_header_len;
		ProcessPacket(pkt, numbytes - rt_header_len);
		NumTotalPkts++;
	}
	close(sockfd);
	return NULL;
}

void reset_driver_stage(const char* ifName)
{
//	char cmdstr[200];

	monitor_mode_onoff(FALSE, ifName);
}

static void sig_handler(int sig)
{
	DEBUG_PRINT("%s: catch signal -- %d \n", __func__, sig);
	switch(sig) {
	case SIGINT:
		g_abort = TRUE;
		RTK_SYSTEM("killall wpa_supplicant");
		RTK_SYSTEM("killall ping");
		reset_driver_stage(ifName);
		exit(EXIT_FAILURE);
		break;
	case SIG_SCPBC:
		//  SC_PBC 
		g_reinit = TRUE;
		printf("sig_handler()  SIG_SCPBC  \n");
		break;
	default:
		break;
	}
}

static void print_usage()
{
	printf("\n\nUsage: \n\trtw_simple_config \t-i<ifname> -c<wpa_cfgfile> -n<dev_name> -p <pincode> \n\t\t\t\t-m <phone_mac> [-d] [-v]");
	printf("\n\nOPTIONS:\n\t");
	printf("-i = interface name\n\t");
	printf("-c = the path of wpa_supplicant config file\n\t");
	printf("-p = pincode\n\t");
//	printf("-P = private command\n\t");
	printf("-d = enable debug message\n\t");
	printf("-n = device name\n\t");
	printf("-m = filtering MAC, only accept the configuration frame which's from this MAC address\n\t");
	printf("-v = version\t\n\n");
	printf("example:\n\t");
	printf("rtw_simple_config -i wlan0 -c ./wpa_conf -n RTKSC_SAMPLE -m 10:bf:48:cc:f1:99 -d\n\t");
	printf("rtw_simple_config -i wlan0 -c ./wpa_conf -p 14825903 -n RTKSC_SAMPLE\n\n");

	return;
}

int parse_argv(int argc, char **argv)
{
	int opt;

	/*	initial variable by default valve	*/
	rtk_sc_set_string_value(SC_DEVICE_NAME, DEFAULT_DEVICE_NAME);
	memset(ifName, 0, IFNAMSIZ);
	strcpy(ifName, DEFAULT_IF);
	rtk_sc_set_string_value(SC_PIN, DEFAULT_PIN);
	rtk_sc_set_string_value(SC_DEFAULT_PIN, DEFAULT_PIN);
	strcpy(g_wpafile_path, DEFAULT_WPAFILE_PATH);
//	strcpy(priv_cmd, DEFAULT_PRIVECMD);
	rtk_sc_set_macaddr_filter("00:00:00:00:00:00");
	g_sc_debug = 0;

	while ((opt = getopt(argc, argv, "i:c:n:p:P:m:hdDv")) != -1) {
		switch (opt) {
		case 'n':	// device name
			rtk_sc_set_string_value(SC_DEVICE_NAME, optarg);
			break;
		case 'i':	// wlan interface
			strcpy(ifName, optarg);
			break;
		case 'c':	// wpa_supplicant config file path
			strcpy(g_wpafile_path, optarg);
			break;
		case 'p':	// pincode
			rtk_sc_set_string_value(SC_PIN, optarg);
			break;
//		case 'P':	// private cmd
//			strcpy(priv_cmd, optarg);
//			break;
		case 'm':	// mac address filter
			if (rtk_sc_set_macaddr_filter(optarg)) {
				printf("Invalid MAC address -- %s\n",optarg);
				return -EINVAL;
			}
			break;
		case 'd':	// enable debug message
			g_sc_debug = 1;
			break;
		case 'D':	// enable move debug message
			g_sc_debug = 2;
			break;
		case 'v':
			printf("%s -- %s\n", argv[0], PROGRAM_VERSION);
			exit(EXIT_SUCCESS);
		case 'h':
		default: /* '?' */
			print_usage();
			return -EINVAL;
		}
	}

	if(g_sc_debug) {
		char dbg_str[256];

		DEBUG_PRINT("========option parse========\n");
		rtk_sc_get_string_value(SC_PIN, dbg_str);
		DEBUG_PRINT("pincode = %s\n", dbg_str);
		rtk_sc_get_string_value(SC_DEVICE_NAME, dbg_str);
		DEBUG_PRINT("device name = %s\n",  dbg_str);
		DEBUG_PRINT("ifName = %s\n",  ifName);
		DEBUG_PRINT("g_wpafile_path = %s\n",  g_wpafile_path);
		DEBUG_PRINT("========================\n");
	}
	return 0;
}

int check_ip_timeout(const int timeout)
{
	int sockfd_ack, ret = 0; 
	unsigned int self_ipaddr=0;
	char smac[6];
	int i;

	if ((sockfd_ack = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		perror("socket");
		return errno;
	}
	
	for (i=0; i<timeout; i++) {
		ret = rtk_sc_get_addr(sockfd_ack, smac, &self_ipaddr);
		if (self_ipaddr != 0) {
			close(sockfd_ack);
			return 1;
		}
		sleep(1);
	}
	close(sockfd_ack);
	return ret;
}

int control_handler()
{
	int accept_control = 1, on = 1, flag, stop_comfirm = 0;
	int sockfd_scan, sockfd_ctrl;			// socket descriptors
	struct sockaddr_in device_addr;     		// my address information
	struct sockaddr sender; 			// connector’s address information
	socklen_t sendsize = sizeof(sender);
	int sc_run_time, ctrl_cmd, sc_config_success = 0;
	ssize_t numbytes;
	fd_set fds;
	int max_fd, selret;
	char buf[256];
	struct timeval timeout;

	if ((sockfd_scan = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		perror("create scan socket fail\n");
		exit(EXIT_FAILURE);
	}

	setsockopt( sockfd_scan, SOL_SOCKET, SO_BROADCAST|SO_REUSEADDR, &on, sizeof(on) );

	bzero(&device_addr,sizeof(struct sockaddr_in)); 
	device_addr.sin_family = AF_INET;         		// host byte order
	device_addr.sin_port = htons(SCAN_PORT);     		// short, network byte order
	device_addr.sin_addr.s_addr = INADDR_ANY;		// automatically fill with my IP

	// bind the socket with the address
	if (bind(sockfd_scan, (struct sockaddr *)&device_addr, sizeof(struct sockaddr)) == -1) 
	{
		perror("bind scan socket fail\n");
		close(sockfd_scan);
		exit(EXIT_FAILURE);
	}

	if ((sockfd_ctrl = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		perror("create control socket fail\n");
		exit(EXIT_FAILURE);
	}
	setsockopt( sockfd_scan, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

	bzero(&device_addr,sizeof(struct sockaddr_in)); 
	device_addr.sin_family = AF_INET;         		// host byte order
	device_addr.sin_port = htons(ACK_DEST_PORT);     	// short, network byte order
	device_addr.sin_addr.s_addr = INADDR_ANY;		// automatically fill with my IP

	// bind the socket with the address
	if (bind(sockfd_ctrl, (struct sockaddr *)&device_addr, sizeof(struct sockaddr)) == -1) 
	{
		perror("bind control socket fail\n");
		close(sockfd_scan);
		exit(EXIT_FAILURE);
	}

	sc_run_time=0;
	ctrl_cmd = SC_SCAN;
	while (1) {
		sc_run_time++;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		FD_ZERO(&fds);
		FD_SET(sockfd_scan, &fds);
		FD_SET(sockfd_ctrl, &fds);
		max_fd = (sockfd_ctrl > sockfd_scan) ? sockfd_ctrl : sockfd_scan;
		selret = select(max_fd+1, &fds, NULL, NULL, &timeout);
#if defined(SIMPLE_CONFIG_PBC_SUPPORT)
		if (g_reinit)
			return SC_REINIT_WLAN;
#endif
		if (!stop_comfirm)
			rtk_sc_send_socketack();

		if (selret && FD_ISSET(sockfd_scan, &fds)) {
			stop_comfirm = 1;
			memset(buf, 0, 256);
			if ((numbytes = recvfrom(sockfd_scan, buf, 256, 0,
						   &sender, &sendsize)) == -1) {
				fprintf(stderr,"Receive failed!!!\n");
				close(sockfd_scan);
				exit(EXIT_FAILURE);
			}
			flag = rtk_sc_get_scanmsg_value(buf, SCANMSG_DATAID_FLAG);
			DEBUG_PRINT("sockfd_scan !! pMsg->flag=%s\n", flag_str[flag]);
			switch(flag) {
			case SC_SUCCESS_ACK:
				DEBUG_PRINT("receive config success ack\n");
				ctrl_cmd = SC_SCAN;
				break;
			case SC_SCAN:
				rtw_sc_send_scan_ack(sockfd_scan, buf, SC_RSP_SCAN);
				break;
			default:
				printf("invalid request\n");
				break;
			}
		}
		
		/* Note: APK would continue sends several ctrl_message for one click on GUI, so we 
		    don't do action in receiving each message, we just keep it in "ctrl_cmd" then do_ctrl_cmd() 
		    after ctrl_message sending finish (receive a SC_SUCCESS_ACK message)			*/
		
		if (selret && FD_ISSET(sockfd_ctrl, &fds)) {
			stop_comfirm = 1;
			memset(buf, 0, 256);
			if ((numbytes = recvfrom(sockfd_ctrl, buf, 256, 0,
						   &sender, &sendsize)) == -1) {
				fprintf(stderr,"Receive failed!!!\n");
				close(sockfd_ctrl);
				exit(EXIT_FAILURE);
			}
			if(g_sc_debug == 2) {
				BYTEDUMP("received ctrl_msg: ", buf, numbytes);
				printf("the length is %d\n", 
					rtk_sc_get_ctrlmsg_value(buf, CTRLMSG_DATAID_LENGTH));
			}
			sc_config_success = ctrlmsg_handler(sockfd_ctrl, buf, &ctrl_cmd, &accept_control);
		}
		else {
			if(sc_config_success == 1) {
				do_ctrl_cmd(ctrl_cmd);
				ctrl_cmd = SC_SCAN;
				sc_config_success = 0;
			}
			accept_control = 1;
		}
	}
}

int main(int argc, char *argv[])
{
	int err, chidx = 0;
	char cmdstr[256];
	pthread_t tid[2];
	u8 chPlan[MAX_CHNUM];
	int chnum = sizeof(def_chPlan)/sizeof(def_chPlan[0]);

	//   Environment  init
	rtk_sc_init();
	if ( parse_argv(argc, argv))
		return -EINVAL;
	memcpy(chPlan, def_chPlan, chnum*sizeof(u8));
	memset(cmdstr,'\0',sizeof(cmdstr));
	signal(SIGINT, sig_handler);
	sprintf(cmdstr, "rm -rf %s&", g_wpafile_path);
	RTK_SYSTEM(cmdstr);
#if defined(SIMPLE_CONFIG_PBC_SUPPORT)
	signal(SIG_SCPBC, sig_handler);
	err = pthread_create(&(tid[1]), NULL, &pbc_monitor, NULL);
#endif

sc_reinit:

#ifdef ANDROID_ENV
	RTK_SYSTEM("svc wifi disable");
	RTK_SYSTEM("sleep 5");
#else
	RTK_SYSTEM("killall wpa_supplicant");
	RTK_SYSTEM("killall ping");
	sprintf(cmdstr, "rmmod %s", WIFI_MODULE_NAME);
	RTK_SYSTEM(cmdstr);
#endif
	sprintf(cmdstr, "insmod %s", WIFI_MODULE_NAME);
	RTK_SYSTEM(cmdstr);
	sleep(1);

	//interface UP and enter monitor mode
	sprintf(cmdstr,"ifconfig %s up\n",ifName);
	RTK_SYSTEM(cmdstr);
	sleep(2);
#ifdef PROBE_SNIFFER_CH
	if (chidx == 0)
		probe_chplan(chPlan, &chnum);
#endif
	monitor_mode_onoff(TRUE, ifName);

	rtk_sc_set_value(SC_DURATION_TIME, 120);
 	if (!g_reinit) {
		err = pthread_create(&(tid[0]), NULL,&doRecvfrom, NULL);
		printf("after pthread_create...\n");
		if (err != 0)
			printf("\ncan't create thread :[%s]", strerror(err));
		else
			printf("\n doRecvfrom Thread created successfully\n");
	}
	g_reinit = FALSE;
	rtk_restart_simple_config();

	while (1) {
#if defined(SIMPLE_CONFIG_PBC_SUPPORT)
		if (g_reinit)
			goto sc_reinit;
#endif
		// switch channel & bandwidth
		sprintf(cmdstr,"echo %d 0 0 > /proc/net/%s/%s/monitor \n", 
			chPlan[chidx++], PROC_MODULE_PATH, ifName);
		RTK_SYSTEM(cmdstr);
		sleep(TIME_CHSWITCH);
		if ((SC_STATUS_DECODE == rtk_sc_get_value(SC_STATUS))
			|| rtk_sc_get_fix_sa()) {
			int sec = 6 + rtk_sc_get_profile_pkt_index() * 2;
			int i;

			DEBUG_PRINT("decode phase!! staying for maximum [%d] seconds\n", sec);
			for (i = 0; i < sec; i++) {
				sleep(1);
				if (SC_STATUS_DONE == rtk_sc_get_value(SC_STATUS))
					break;
			}
		}

                if (SC_STATUS_DONE == rtk_sc_get_value(SC_STATUS))
                        break;
		rtk_restart_simple_config();
		if (chidx == chnum) {
			chnum = sizeof(def_chPlan)/sizeof(def_chPlan[0]); 	// scan fully channel plan if  first round doesn't success.
			memcpy(chPlan, def_chPlan, chnum*sizeof(u8));		// scan fully channel plan if  first round doesn't success.
			chidx = 0;						// start next scan round, 
		}
	}

	if (SC_STATUS_DONE == rtk_sc_get_value(SC_STATUS)) {
		monitor_mode_onoff(FALSE, ifName);		
		if (!collect_scanres()) {
			connect_ap();
#ifndef ANDROID_ENV
			request_ip();
#endif
			if (check_ip_timeout(15) && control_handler())
				exit(EXIT_FAILURE);
		}
	}
	return 0;
}
 
static void ProcessPacket(u8 *buffer, int size)
{
	struct rx_frinfo pfrinfo;
	u8 type;
//	u8 subtype;

	/*	80211 header format
		ver:	2bit
		type:	2bit
		subtype:	4bit
		tods:	1bit
		frds:	1bit
		other:	6bit		*/
	pfrinfo.pframe = buffer;
	type = *buffer & TYPE_MASK;
//	subtype = (*buffer & SUBTYPE_MASK) >> 4;	
	if (type != TYPE_DATA)
		return ;
	pfrinfo.to_fr_ds = *(buffer + 1) & FRTODS_MASK;
	if (pfrinfo.to_fr_ds == 1) {
		pfrinfo.sa = GetAddr2Ptr(pfrinfo.pframe);
		pfrinfo.da = GetAddr3Ptr(pfrinfo.pframe);
	} else if (pfrinfo.to_fr_ds == 2) {
		pfrinfo.sa = GetAddr3Ptr(pfrinfo.pframe);
		pfrinfo.da = GetAddr1Ptr(pfrinfo.pframe);
	}
	pfrinfo.pktlen = size;

	/*	SimpleConfigV1 -- Multicast packets	*/
	if (pfrinfo.da[0] == DEST_MAC0 &&
		pfrinfo.da[1] == DEST_MAC1 &&
		pfrinfo.da[2] == DEST_MAC2
	   )
	{
		if(CHECKSUM_OK(pfrinfo.da, ETH_ALEN))
		{
			rtk_sc_start_parse_packet(&pfrinfo);
		}
  	}
	else if (memcmp(pfrinfo.da, bc_mac, ETH_ALEN)==0) 	/* SimpleConfigV2 -- Broadcast packets	*/
	{
		rtk_sc_start_parse_bcpacket(&pfrinfo);
	}
	
}

