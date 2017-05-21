
#include "rt_config.h"
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include "../../msc/msc.h"
#include "../../lib/plat.h"
#include <linux/version.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0))	
#include <../../fs/proc/internal.h>
#endif	

#define MSC_PROC_NAME "elian"

static int msc_proc_open(struct inode *inode, struct file *file);
static int msc_proc_release(struct inode *inode, struct file *file);
static int msc_proc_show(struct seq_file *seq, void *offset);
static ssize_t msc_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);

static struct proc_dir_entry *entry=NULL;

const struct file_operations msc_proc_fops = {
	.open           = msc_proc_open,
	.read           = seq_read,
	.write          = msc_proc_write,
	.llseek         = seq_lseek,
	.release        = msc_proc_release,
};

void evt_cb(unsigned int eid, struct msc_result *result)
{
	printk("[MSC] done: AM=%d, ssid=%s, pwd=%s, user=%s, cust_data_len=%d, cust_data=%s,\n",
				result->auth_mode, result->ssid, result->pwd, result->user, result->cust_data_len, result->cust_data);
	return;
}

int msc_proc_create(void *priv)
{
	printk("MSC msc_proc_create: %p\n", priv);
	if(entry == NULL)
	{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)     
	entry = proc_create_data(MSC_PROC_NAME, S_IRUSR|S_IWUSR, NULL, &msc_proc_fops, priv);
#else  
	entry = create_proc_entry(MSC_PROC_NAME, S_IRUGO, NULL);  
	if (!entry)  
		return -ENOMEM;        
	entry->proc_fops = &msc_proc_fops;
#endif   /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)     */
	}
	
	return 0;
}

void msc_proc_destroy(void)
{
	printk("MSC msc_proc_destroy: %s\n", MSC_PROC_NAME);
	if(entry != NULL)
	{
		remove_proc_entry(MSC_PROC_NAME, NULL);
		entry=NULL;
	}
	return;
}


static int msc_proc_show(struct seq_file *seq, void *offset)
{
	struct msc_result result;

	msc_get_result(&result);

#if 0
	for(i=0;i<SMTCNResult.msc_cust_tlv_len;i++)
		sprintf(SMTCNResult.msc_cust_tlv_str + i*3, "%02X-", SMTCNResult.msc_cust_tlv[i]);
	SMTCNResult.msc_cust_tlv_str[i*3-1] = 0;	
	printf("MSC_CORE: AM=%d, ssid=%s, pwd=%s, user=%s, cust_data_len=%d, cust_data=%s\n",
				test_result->auth_mode, test_result->ssid, test_result->pwd, test_result->user, test_result->cust_data_len, test_result->cust_data);
	seq_printf(seq, "SSID\t: %s\n"
			"PASSWORD\t: %s\n"
			"AUTHMODE\t: %d\n"
			"TLV_HEX\t: %s\n",
			SMTCNResult.msc_ssid, SMTCNResult.msc_pwd, SMTCNResult.msc_authmode, SMTCNResult.msc_cust_tlv_str);
#endif
	seq_printf(seq, "AM=%d, ssid=%s, pwd=%s, user=%s, cust_data_len=%d, cust_data=%s,\n",
				result.auth_mode, result.ssid, result.pwd, result.user, result.cust_data_len, result.cust_data);
		
	return 0;
}

static ssize_t msc_proc_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	int err = 0;
	char data[128];
	char result[128];

	if (count > sizeof(data))
		count = sizeof(data);

	if (copy_from_user(data, buf, count)) {
		err = -EFAULT;
		goto out;
	}
	data[count - 1] = 0;    /* Make string */
	

	msc_cmd_handler(data, (int)count, result, (void*)entry->data);
#if 0
	if (strcmp(data, "clear") == 0) {
		msc_reset();
	} else if (strcmp(data, "start") == 0) {
		memset(&g_para, 0, sizeof(g_para));
		g_para.evt_cb = evt_cb;
		msc_start(&g_para, entry->data);
	} else if (strcmp(data, "stop") == 0) {
		msc_stop(entry->data);
	}
#endif
	err = count;
out:
	return err;
}

static int msc_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, msc_proc_show, NULL);
}

static int msc_proc_release(struct inode *inode, struct file *file)
{
	int res = single_release(inode, file);
	return res;
}

