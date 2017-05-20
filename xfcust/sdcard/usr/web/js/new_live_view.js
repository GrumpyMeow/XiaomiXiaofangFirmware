/*common function ,I will move it later*/

/*common function ,I will move it later*/
var twowayaudio_running=false;
var ip = window.location.hostname;
var audiovalue=0;
var ret=-1;
function twowayaudio_change(){
	var select_value = document.getElementById("twowayaudio_select").value;
	var twowayaudio=document.getElementById("WinAudio");
	if(select_value=="off"){
		twowayaudio.Close_js();
		hidden_mic(true);
	}
	else{
		ret=twowayaudio.Open_js_ret(ip);
		if(ret==-1){
			alert(LV_TW_AUDIO_ERROR);
			document.getElementById("twowayaudio_select").value="off";
			return;
		}
		twowayaudio.Set_status_js(0);
		hidden_mic(false);
	}
	$.cookie("twowayaudio_status", $(this).val(), { expires: 365 * 2 });//save twowayaudio status to cookie
}
$(window).unload(function(){
	var twowayaudio=document.getElementById("WinAudio");
	//if(twowayaudio_running!=false)
		twowayaudio.Close_js();
	//twowayaudio_running=false;
	if(recording_flag)
		document.getElementById("recording").click(); //stop recording;
	vlc_stop();	
});
	//mymovie.audio.volume = 0;
function checkPathIsWirte(path)
{
	var num = 0;
	var strFile = path + "\\__vlc_write_test_" ;
	var fso = new ActiveXObject("Scripting.FileSystemObject");
	var objStream;	
	while(1)
	{
		var strFile = strFile + "_" + num.toString();
		if (fso.FileExists(strFile) == true) 
		{
			num = num + 1;
			//alert(num);
			if(num > 10)
				break;				
		}
		else
			break;	
	}
	try{
		objStream = fso.OpenTextFile(strFile, 2, true, false);	
   		objStream.WriteLine("for vlc write test!");
   		objStream.Close();
		var f = fso.GetFile(strFile);
   		f.Delete();
		return true;			
	}
	catch(e)
	{
		alert(LV_ALERT + " '" + path + "'");
		return false;
	}	
}

var SAVE_PATH="D:\\";   //record path
function BrowseFolder(){ 

   var Folder = DemoCtrl.getpathname();
    var newstr = new String(Folder);
   if(newstr.length != 0)
   {
   		if(checkPathIsWirte(Folder) == true)
			document.getElementById("savePath").value=Folder;//savePath��ָ����Ŀؼ�id�� 
		
   }
   	

}
var playing_flag=false;
var recording_flag=false;
function record_change()
{
	recording_flag=!recording_flag;
	if(recording_flag)
	{
		document.getElementById("recording").src="/images/recording_stop.png";
		$('#rec_info').text(',' + LV_Recording);
	}
	else
	{
		document.getElementById("recording").src="/images/recording_start.png";
		$('#rec_info').text("");
	}
}
function priority()
{
		if(prio > 0)
		{
			var con=document.getElementsByName("controlptz");
			for(var i=0;i<con.length;i++)
			{
				con[i].setAttribute("disabled","disabled");
			}
			document.getElementById('twowayaudio_select').setAttribute("disabled","disabled");
			document.getElementById('if_mute_mic').setAttribute("disabled","disabled");
			document.getElementById('micVolDown').setAttribute("disabled","disabled");
			document.getElementById('micVolUp').setAttribute("disabled","disabled");
			document.getElementById('if_mute_spk').setAttribute("disabled","disabled");
			document.getElementById('spkVolDown').setAttribute("disabled","disabled");
			document.getElementById('spkVolUp').setAttribute("disabled","disabled");			
		}

}
$(document).ready(function(){
	getSystemClock();
	setInterval(function(){
			getSystemClock()
		},1000);
	
	$('#select_stream').change(function ()
	{
		var value = $(this).val();
		var date  = new Date().getTime().toString();
		var data = {streamNum: value, date: date};
		$.getJSON('/cgi-bin/getstreaminfo.cgi', data, processStreamInfo);
		return false;
	});
    	$("#radio_zoom").buttonset();
	$("#radio_zoom").change(function(){
		var value = $('input[type=radio]:checked').val();
		if( value == "auto")
		{
			var width = 640;
			var height = 480;
		}
		else
		{
			var array=$('#res_info').text().split("X");
			width = array[0];
			height = array[1];	
			width = width * parseFloat(value);
			height = height * parseFloat(value);						
		}
		if(navigator.appName.indexOf("Microsoft Internet Explorer") != -1)
		{
			$('#mymovie').width(width);
			$('#mymovie').height(height);
		}else
		{
			$('embed#mymovie').width(width);
			$('embed#mymovie').height(height);
		}
		
		//$('embed').attr("width",width);
		//$('embed').atrr("height",height);		
		//document.getElementById('mymovie').style.width=width;
		//document.getElementById('mymovie').style.height=height;
	});
	
    $("#twowayaudio_select").change(twowayaudio_change);
    var twowayaudio_status = $.cookie("twowayaudio_status"); //get twowayaudio status from cookie
    document.getElementById("WinAudio").Set_server_port_js(twy_port); 
    if (twowayaudio_status == "on") {//if the cookie is 'on', turn on twowayaudio
        $("#twowayaudio_select").val("on").change();
    }
    else if (twowayaudio_status == "off") {//if the cookie is 'off', turn off twowayaudio
        $("#twowayaudio_select").val("off").change();
    }
    else {//if first can't find the cookie ,create cookie for twowayaudio and set it as 'off'
        $.cookie("twowayaudio_status", "off", { expires: 365 * 2 });
	 hidden_mic(true);
    }	
});
function processSystemDate(dt, status){
	$('#date_info').text(dt.date);
}	
function getSystemClock()
{
	$.getJSON('/cgi-bin/getsystime.cgi?t=' + new Date().getTime() , null, processSystemDate);
}
function processStreamInfo(data, status)
{
	$('#codec_info').text(data.codec.toUpperCase());
	$('#res_info').text(data.res.toUpperCase());
	stream=data.url;
	init();
}
function hidden_mic(value)
{
	if(value == true)
	{
		$('.mic_ctr').fadeTo('normal', 0.75).attr("disabled","disabled");
		//alert("hide")
	}
	else
	{
		$('.mic_ctr').fadeTo('normal', 1).removeAttr("disabled","");
		//alert("show");
	}
}
function init_page()
{
	var value = $('#select_stream').val();
	var data = {streamNum: value};
	var date  = new Date().getTime().toString();
	var data = {streamNum: value, date: date};
	$.getJSON('/cgi-bin/getstreaminfo.cgi', data, processStreamInfo);
	//hidden_mic(true);
}
//function initial_language() {
	
	//$('#microphoneVolumeText').text(LV_Microphone_volume);
	//$('#speakerVolumeText').text(LV_Speaker_volume);	
	//$('#twowayaudioText').text(LV_TwoWayAudio);	
	//$('#t_full_duplex').text(LV_ON);	
	//$('#t_default').text(LV_OFF);		
	//$('#streamsourcetext').text(LV_Stream_source);		
	//$('#stream1').text(LV_Stream1);
	//$('#stream2').text(LV_Stream2);
	//$('#stream3').text(LV_Stream3);		
	//$('#protocaltext').text(LV_Protocol);		
	//$('#recordPathtext').text(LV_Record_path_set);		
    //$("#savePath").val(SAVE_PATH);
    //$("#path_browse").val(LV_Browse);		
//}
function initial_vlc() {
}
//var ifmute_mic=true;
//var ifmute_spk=true;
function initial_events() {
//    $("#if_mute_mic").click(function () {
//	     press_mic_mute();
//    });
//    $("#micVolDown").click(function () {
//	     mic_volume_down();
//    });	
//    $("#micVolUp").click(function () {
//	     mic_volume_up();
//    });		
//	if(mic_vol != 0) 
//		ifmute_mic=false;
//	$("#mic_vol").html(mic_vol);	
	//document.getElementById("mic_vol").innerHTML = mic_vol;	
//    $("#if_mute_spk").click(function () {
//	    press_spk_mute();
//   });	
//    $("#spkVolDown").click(function () {
//	    spk_volume_down();
//   });	
//    $("#spkVolUp").click(function () {
//	    spk_volume_up();
//   });	
//	if(spk_vol != 0) 
//		ifmute_spk=false;
//	$("#spk_vol").html(spk_vol);						
	//document.getElementById("spk_vol").innerHTML = spk_vol;
//    $("#play").click(function () {
//	    vlc_init();
//    });	
//    $("#stop").click(function () {
//	    vlc_stop();
//   });	
//    $("#snapshot").click(function () {
//	    vlc_snapshot($("#savePath").val());
//    });	
//    $("#fullscreen").click(function () {
//	    vlc_fullscreen();
//    });	
//    $("#recording").click(function () {
//	    vlc_record($("#savePath").val());
//    });	
//    $("#stream_protocol").change(function () {
//	    demultiplexer_setting($(this).val());
//    });		
//    $("#path_browse").click(function () {
//	    BrowseFolder();
//    });						
}


//document ready
$(function () {
	$('.label1 > span').text(LV_Auto);
//	initial_language();
	initial_events();
	init_page();
	priority();
});
