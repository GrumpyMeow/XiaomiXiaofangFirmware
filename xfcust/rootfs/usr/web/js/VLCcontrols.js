/*
<OWNER> = revolunet
<ORGANIZATION> = revolunet - Julien Bouquillon
<YEAR> = 2008

Copyright (c) 2008, revolunet
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met :


 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. 
 Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission. 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES ; LOSS OF USE, DATA, OR PROFITS ; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


*/

//var SimpleSlider_Lib_Uri = "SimpleSlider.js";

var VLC_controller= null;


// theses image are in the subfolder 'images' of your VLCjs lib
var VLC_controller_icon_play = "player_play.png";
var VLC_controller_icon_stop = "player_stop.png";
var VLC_controller_icon_voldown = "moins.gif";
var VLC_controller_icon_volup = "plus.gif";
var VLC_controller_icon_pause = "player_pause.png";
var VLC_controller_icon_sound = "sound.png";
var VLC_controller_icon_soundoff = "sound_mute.png";
var VLC_controller_icon_options = "options.png";
var VLC_controller_icon_infos = "info.png";
var VLC_controller_icon_fullscreen = "fullscreen.gif";

var VLC_status = new Array("standby", "ouverture", "buffering", "lecture", "pause", "stop", "erreur");
	
var VLC_controller_default_buffersize = "5";
var VLC_controller_log_verbosity = 0;



// function SimpleSliderLibReceived() {
	// VLC_controller.slider = new Slider(VLC_controller.id+"_slider", VLC_controller.width, "10");
	// VLC_controller.slider.onNewPosition = VLC_controller.slider_position_changed;
// }
 
 

function toolbar_icon(icon, alt, onclick, id) {
	return "<img id='" + id + "' width='16' height='16' src='" + icon + "' style='vertical-align:middle;cursor:pointer;margin:3px' onclick='" + onclick + "'/>";
}

function changeImageSrc(imgID, newSrc) {
	var tgt = document.getElementById(imgID);
	cursrc = tgt.src.substring(tgt.src.length - newSrc.length);
	if (cursrc != newSrc) tgt.src=newSrc;
}

// HTML FUNCTIONS
 
// function injectJS(uri) {
	// var s = document.createElement('script');
	// s.src = uri;
	// s.type = 'text/javascript';
	// document.body.appendChild(s);
// }

function addHTMLtoObj(obj, html, position) {
	if(self.Node&&self.Node.prototype){
		// mozilla
		var range = document.createRange();
		range.selectNode(obj);
		var htmlnode = range.createContextualFragment(html);
		var parent = obj.parentNode;
		
		position = position.toLowerCase();
		if (position=="beforebegin") parent.insertBefore(htmlnode, obj);
		else if(position=="afterend") parent.insertBefore(htmlnode, obj.nextSibling);
		else if(position=="afterbegin") obj.insertBefore(htmlnode, obj.childNodes[0]);
		else if(position=="beforeend") obj.appendChild(htmlnode);
		}
	else {
		//ie 
		obj.insertAdjacentHTML(position, html);
	}
}

function SimpleSlider_received() {
	//VLC_controller.target = new VLCobject(VLC_controller.id, VLC_controller.with, VLC_controller.height);
	//alert(VLC_controller);
	VLC_controller.libsReady();
}

function VLCcontrols(VLCobject, dodebug) {
	this.id = VLCobject.getAttribute('id');
	this.idleimage = null;
	this.isVideoVisible = true;
	this.target = document.getElementById(this.id);
	//this.updateTarget();
	this.root = ""
	
	this.options = new VLC_options(this);
	//this.options.VLCcontrol = this;
    
	this.loaded = false;
	this.onready = null;
	//this.libloader = new ExternalLibLoader();
	//this.libloader.addLib("VLCobject.js", VLCobject_received);
	//this.libloader.addLib("/include/SimpleSlider.js", SimpleSlider_received);
	//this.libloader.LoadLibs();
	
	this.options.set("http-caching", parseInt(VLC_controller_default_buffersize) * 1000);
	this.options.set("udp-caching", parseInt(VLC_controller_default_buffersize) * 1000);
	this.options.set("http-reconnect", "true");
  
	
	VLC_controller = this;
	
	this.dodebug = false;
	
	this.width = VLCobject.getAttribute("width");
	//this.target.width;
	this.height = VLCobject.getAttribute("height");
	if (dodebug) this.dodebug = dodebug;
	
	// detect lib path (dirty)
	var sc = document.getElementsByTagName("SCRIPT");
	for (var i=0;i<sc.length;i++) {
		if(sc[i].src.indexOf("VLCcontrols.js")>-1) {
			this.root = sc[i].src.replace("VLCcontrols.js","");
			}
	}
 
	// if(!this.target) {
		// var errorinfo = "<span class='VLC_controller_notdetected'><b>Plugin VLC non d�t�ct� !</b> --> telechargez le sur <a href='http://www.videolan.org/vlc/' target='_blank'>http://www.videolan.org/vlc/</a></span>";
		// document.body.innerHTML = errorinfo + document.body.innerHTML;
	////	return;
	// }
	
	
}

VLCcontrols.prototype.libsReady = function() {
	//alert(1);
	//alert(Slider);
	
	var bg_img = '<img style="display:" src="#" width="1" height="1" id="' + this.target.id +'_idleimage">';
 
	addHTMLtoObj(this.target, bg_img, "beforebegin");
	
	var toolbar = "";

	//toolbar += '<div style="display:block;width:'+this.width +'px" id="'+this.id+'_slider"></div>';
	toolbar += "<div id='" + this.target.id + "_toolbar' class='VLC_toolbar' style='background:#f5f5f5;width:" + this.width + "px'>";
	toolbar += "<table border=0 cellpading=0 cellspacing=0 width='100%'><tr><td >";
	//toolbar += toolbar_icon(this.root + "images/" + VLC_controller_icon_play, "Play/Pause", "VLC_controller.btn_play_clicked()", this.id + "_btn_play");
	//toolbar += toolbar_icon(this.root + "images/" + VLC_controller_icon_stop, "Stop", "VLC_controller.btn_stop_clicked()", this.id + "_btn_stop");
//	toolbar += toolbar_icon("/vlcjs/images/player_prev.png", "Prev", "", this.id + "_btn_prev");
	//toolbar += toolbar_icon("/vlcjs/images/player_next.png", "Next", "", this.id + "_btn_next");
	//toolbar += toolbar_icon("/" + VLC_controller_icon_sound, "Volume", "VLC_controller.btn_mute_clicked()", this.id + "_btn_mute");
	//toolbar += toolbar_icon("/" + VLC_controller_icon_voldown, "Volume down", "VLC_controller.btn_voldown_clicked()", this.id + "_btn_voldown");
	//toolbar += "<span style='font-size:10px'><span id='" + this.target.id + "_vollabel'>100</span>%</span>";
	
	//toolbar += toolbar_icon( "/" + VLC_controller_icon_volup, "Volume up", "VLC_controller.btn_volup_clicked()", this.id + "_btn_volup");
	
	//toolbar += toolbar_icon(this.root + "images/" + VLC_controller_icon_fullscreen, "FullScreen", "VLC_controller.btn_fullscreen_clicked()", this.id + "_btn_fullscreen");
	
	toolbar += "</td><td align=center width=60>";
	
	//toolbar += '<span style="vertical-align:middle;position:relative;" id="infosPosition">00:00/00:00</span>';
	toolbar += "</td><td align=center width=65>";
	//toolbar += '&nbsp;&nbsp;<span style="vertical-align:middle;" id="infosStatus">stopped</span>';
	toolbar += "</td><td align=center width=45>";
	//toolbar += toolbar_icon(this.root + "images/" + VLC_controller_icon_options, "Options", "VLC_controller.btn_options_clicked()", this.id + "_btn_options");
	//toolbar += toolbar_icon(this.root + "images/" + VLC_controller_icon_infos, "About", "VLC_controller.btn_infos_clicked()", this.id + "_btn_infos");
	toolbar += "</td></tr></table>";
	toolbar += '<div style="display:none" id="VLC_controller_options">';
	toolbar += '&nbsp;buffer : <input   size=1 style="vertical-align:middle;"  id="VLC_controller_options_http-caching" value="' + VLC_controller_default_buffersize + '" /> sec.';
	toolbar += '&nbsp;&nbsp;<input type="checkbox" ' + (this.dodebug && 'checked=1' || '') + '" style="vertical-align:middle;" onclick="VLC_controller.setdebug(this.checked)" id="VLC_controller_dodebugcheckbox"/><label for="VLC_controller_dodebugcheckbox">debug</label>';
//	toolbar += '<span style="display:none">&nbsp;&nbsp;<input type="checkbox" ' + (this.dodebugvlc && 'checked=1' || 'checked=1') + '" style="vertical-align:middle;" onclick="VLC_controller.setdebugvlc(this.checked)" id="VLC_controller_dodebugvlccheckbox"/><label for="VLC_controller_dodebugvlccheckbox">debug VLC</label></span>';
	toolbar += '&nbsp;&nbsp;<input type="checkbox" style="vertical-align:middle;"  id="VLC_controller_DesktopOutputcheckbox"/><label for="VLC_controller_DesktopOutputcheckbox">set as wallpaper</label>';
	toolbar += '<span style="display:none">&nbsp;&nbsp;<input type="checkbox" style="vertical-align:middle;"  id="VLC_controller_FreeplayerModecheckbox"/><label for="VLC_controller_FreeplayerModecheckbox">FreePlayer</label></span>';
	
	toolbar += '&nbsp;&nbsp;&nbsp;&nbsp;<button style="vertical-align:middle;"  onclick="VLC_controller.saveOptions()">ok</button></div>';
	
	toolbar += "<div id='VLC_controller_debug_div' style='display:block'><textarea id='VLC_controller_debug' style='display:block;width:" + this.width + "px;height:200px'></textarea>";
	toolbar += "</div>";
	
	toolbar += '<div style="display:none" id="VLC_controller_infos">';
	toolbar += '<br>This VLC widget has been created by the <a href="http://www.revolunet.com">revolunet</a> team.<br>Comments welcome on <a href="mailto:contact@revolunet.com?subject=VLCcontrols">contact@revolunet.com</a> !<br><br>';
	toolbar += "</div>";
		
	//this.target.insertAdjacentHTML("afterEnd", toolbar);
	
	addHTMLtoObj(this.target, toolbar, "afterEnd");
	
	//alert(this.width);
	this.slider = new Slider(this.id+"_slider", this.width, "10");
	this.slider.onNewPosition = this.slider_position_changed;
	
	
	//this.slider = null;
	
	// trick to load external JS file
	//injectJS(this.root + SimpleSlider_Lib_Uri);
			
	this.load();
	
	setInterval("VLC_controller.updateStatus()", 1000 );
	
	this.loaded = true;
	
	if (this.onready) this.onready();
	//this.debug("plugin loaded v." + this.target.versionInfo);
}


VLCcontrols.prototype.changeVolume = function(newVolume) {
	// prends une valeur entre 0 et 100
	document.getElementById("_vollabel").innerHTML = newVolume;
//var vlc_volume = parseInt(newVolume)
	this.target.audio.volume = newVolume;
	if (newVolume > 0) changeImageSrc("_btn_mute","/" + VLC_controller_icon_sound);
	else changeImageSrc("_btn_mute", "/" + VLC_controller_icon_soundoff);
}

VLCcontrols.prototype.btn_voldown_clicked = function() {
	if (!this.target.audio) return;
	var curvolume = this.target.audio.volume;
	curvolume -= 10;
	if (curvolume <= 0) this.changeVolume(0);
	else if (curvolume >= 200) this.changeVolume(200);
	else this.changeVolume(curvolume);
	
}

VLCcontrols.prototype.btn_fullscreen_clicked = function() {
	this.target.video.toggleFullscreen();
//	= true;
}


VLCcontrols.prototype.btn_volup_clicked = function() {
	if (!this.target.audio) return;
	var curvolume = this.target.audio.volume;
	curvolume += 10;
	if (curvolume <= 0) this.changeVolume(0);
	else if (curvolume >= 200) this.changeVolume(200);
	else this.changeVolume(curvolume);
	
}

VLCcontrols.prototype.setFreeplayerMode = function(checked) {
}

VLCcontrols.prototype.updateTarget = function() {
	
	this.target = document.getElementById(this.id);
	if (!document.all) {
		
		this.target.innerHTML += '<embed type="application/x-vlc-plugin" pluginspage="http://www.videolan.org" version="VideoLAN.VLCPlugin.2" id="' + this.id + '_moz"/>';
	
		this.target = document.getElementById(this.id + "_moz");
		
		}
 }

VLCcontrols.prototype.setIdleImage = function(imgSrc) {
	this.idleimage = imgSrc;
	document.getElementById(this.id +"_idleimage").src = imgSrc;
	this.hideVideo();
	
}

VLCcontrols.prototype.hideVideo = function() {
	if (!this.isVideoVisible) return;
	if (!this.idleimage) return;
	this.target.style.width=0;
	this.target.style.height=0;
	
	var tgt = document.getElementById(this.id +"_idleimage");
	tgt.style.width = this.width;
	tgt.style.height = this.height;
		
	this.isVideoVisible = false;
}

VLCcontrols.prototype.showVideo = function() {
	if (this.isVideoVisible) return;
	var tgt = document.getElementById(this.id +"_idleimage");
	tgt.style.width = 0;
	tgt.style.height = 0;
	this.target.style.width=this.width;
	this.target.style.height=this.height;
	this.isVideoVisible = true;
}

VLCcontrols.prototype.setdebug = function(checked) {
	this.dodebug = checked
	this.debug("debug changed");

}
 
VLCcontrols.prototype.debug = function(astr) {
	var tgt = document.getElementById("VLC_controller_debug_div");
   // alert("debug "+astr);
	if (tgt &&  this.dodebug) {
		document.getElementById("VLC_controller_debug_div").style.display="block";
		document.getElementById("VLC_controller_debug").value+=astr + "\n";
		document.getElementById("VLC_controller_debug").scrollTop=document.getElementById("VLC_controller_debug").scrollHeight;
        
		}
	else {
	 	if (tgt) tgt.style.display="none";
	}
}
 


VLCcontrols.prototype.btn_options_clicked = function() {
	var tgt = document.getElementById("VLC_controller_options");
	if (tgt.style.display=="block") {
		tgt.style.display="none";
	}
	else {
		tgt.style.display="block";
	}
}


VLCcontrols.prototype.btn_infos_clicked = function() {
	var tgt = document.getElementById("VLC_controller_infos");
	if (tgt.style.display=="block") {
		tgt.style.display="none";
	}
	else {
		tgt.style.display="block";
	}
}
 
VLCcontrols.prototype.setBufferSize = function(seconds) {
	document.getElementById("VLC_controller_options_http-caching").value = seconds;
	this.options.set("http-caching", parseInt(seconds) * 1000); 
	this.options.set("udp-caching", parseInt(seconds) * 1000); 
}
VLCcontrols.prototype.saveOptions = function() {
	this.setBufferSize(document.getElementById("VLC_controller_options_http-caching").value);

	document.getElementById("VLC_controller_options").style.display="none";
	if (this.target.playlist.isPlaying == true && this.target.input) {
		var sure = confirm("Voulez vous relancer votre flux avec ces parametres ?");
		if (sure) this.restart();
		}
	this.debug("Options saved");
	//TODO : cookie ?
}

function formatTime(timeVal)
{
    var timeHour = Math.round(timeVal / 1000);
    var timeSec = timeHour % 60;
    if( timeSec < 10 )
        timeSec = '0'+timeSec;
    timeHour = (timeHour - timeSec)/60;
    var timeMin = timeHour % 60;
    if( timeMin < 10 )
        timeMin = '0'+timeMin;
    timeHour = (timeHour - timeMin)/60;
    if( timeHour > 0 )
        return timeHour+":"+timeMin+":"+timeSec;
    else
        return timeMin+":"+timeSec;
};

function format_time2( s )
{
    var hours = Math.floor(s/3600);
    var minutes = Math.floor((s/60)%60);
    var seconds = Math.floor(s%60);
    if( hours < 10 ) hours = "0"+hours;
    if( minutes < 10 ) minutes = "0"+minutes;
    if( seconds < 10 ) seconds = "0"+seconds;
    return hours+":"+minutes+":"+seconds;
}



var inputTrackerIgnoreChange = false;
var VLC_controller_paused = false;

VLCcontrols.prototype.btn_stop_clicked = function() {
	if (!this.check_playlist()) {
				//alert("Aucune playlist !");
	//			return;
	}
	try {
		this.target.playlist.stop();
		VLC_controller_paused = false;
		changeImageSrc(this.id + "_btn_play", this.root + "images/" + VLC_controller_icon_play );
		//document.getElementById(this.id + "_btn_play").src=VLC_controller_icon_play;
		this.setSliderPos(0);
		//this.slider.setPosition(0);
		this.hideVideo();
		
		}
		catch(e) {//do noting
		}
		if (VLC_controller.onStopCallback) VLC_controller.onStopCallback();
}

var lastvolume = 0;
VLCcontrols.prototype.btn_mute_clicked = function() {
	
	var cursrc = document.getElementById("_btn_mute").src;
	cursrc = cursrc.substring(cursrc.length - VLC_controller_icon_sound.length);
	if (cursrc=="/" + VLC_controller_icon_sound) {
		lastvolume = this.target.audio.volume;
		this.changeVolume(0);
		}
	else {
		this.changeVolume(lastvolume);		
	}
}


VLCcontrols.prototype.check_playlist = function() {
	return (this.target.playlist && this.target.playlist.items.count > 0);
}

VLCcontrols.prototype.btn_play_clicked = function() {
	
	var cursrc = document.getElementById(this.id + "_btn_play").src;
	cursrc = cursrc.substring(cursrc.length - (this.root + "images/" + VLC_controller_icon_play).length);

	if (cursrc==this.root + "images/" + VLC_controller_icon_play) {
		
		// start
		if (VLC_controller_paused) {
			this.target.playlist.togglePause();
		}
		else {
			VLC_controller_paused = false;
			if (!this.check_playlist()) {
				alert("nothing in playlist !");
				return;
			}
			else {
				
				this.target.playlist.play();
				}
		}
		changeImageSrc(this.id + "_btn_play", this.root + "images/" + VLC_controller_icon_pause);
	}
	else {
		changeImageSrc(this.id + "_btn_play", this.root + "images/" + VLC_controller_icon_play);

		// pause
		this.target.playlist.togglePause();
		VLC_controller_paused = true;	
	}
}


VLCcontrols.prototype.slider_position_changed = function() {

	if (VLC_controller.target && VLC_controller.target.input ) {

		if (parseInt(VLC_controller.target.input.length) == 0) {
			// flux non seekable
			if (VLC_controller.onSliderChangedCallback) {
				VLC_controller.onSliderChangedCallback(this.position);
			}
			else {
				VLC_controller.setSliderPos(this.position);
			}
			return;
			}
		else {
			// flux seekable
			try {VLC_controller.target.input.position = this.position;}
			catch(e) {}
		}
	}	
}
 
var VLC_controller_last_status = null;

VLCcontrols.prototype.updateStatusFromExternalData = function() {
	this.debug("default updateStatusFromExternalData");
}

 
VLCcontrols.prototype.setSliderPos = function(pos) {
			if (this.slider) this.slider.setPosition(pos);
 
}

VLCcontrols.prototype.updateStatus = function() {
        var play_status = document.getElementById("play_status");
				if(this.target.playlist && this.target.playlist.isPlaying == true && this.target.input)
				{	
					try {
						var h = formatTime(this.target.input.time);
						if (parseInt(h) < 1000)  {
							changeImageSrc(this.id + "_btn_play", this.root + "images/" + VLC_controller_icon_pause);
							if (parseInt(this.target.input.length) == 0)  {
								this.updateStatusFromExternalData();
							}
							else {
								document.getElementById("infosPosition").innerHTML = h+"/"+formatTime(this.target.input.length);								
								VLC_controller.position = this.target.input.position;
								this.setSliderPos(this.target.input.position);
								}
							 }
						if (this.target.input && this.target.input.hasVout) this.showVideo();
						else  this.hideVideo();
						}
					catch(e) {}
		        }
		        else
		        {
					//document.getElementById("infosPosition").innerHTML = "00:00/00:00";
					//changeImageSrc(this.id + "_btn_play", this.root + "images/" + VLC_controller_icon_play);
					this.hideVideo();
					this.setSliderPos(0);
		        }
				this.updateStatusText();
				this.updateVlcMessages();
    }

	
VLCcontrols.prototype.updateVlcMessages = function() {
	if (!this.dodebug) {
		if (this.target.log) this.target.log.messages.clear();
		return;
		}
	//if (this.target.log && this.target.log.messages.count ) this.debug("vlc messages : " + this.target.log.messages.count);
	var msgs=this.target.log.messages;
	var iter = msgs.iterator();
		while (iter.hasNext) {
			var msg = iter.next();
			if (msg) {
				var contents = msg.message;
				if (msg.type!="private" && !(contents.substring(0,19)=="backward_pts != dts")  && !(contents.substring(0,28)=="backward_pts != standard_pts") && !(contents.substring(0,20)=="late picture skipped") && !(contents.substring(0,19)=="PTS is out of range")) {
					this.debug("VLC: " + msg.name + " " + msg.type + " : " + contents);
					}
				}
		}
		if (this.target.log) this.target.log.messages.clear();
}

VLCcontrols.prototype.updateStatusText = function() {
	var status = VLC_status[0];
	if (this.target.input) status = VLC_status[this.target.input.state];
	if (status) {
		//document.getElementById("infosStatus").innerHTML = status;
		if (VLC_controller_last_status != status) this.debug("status : " + status);
		VLC_controller_last_status = status;
		}
	if (VLC_controller.onStatusChangedCallback) VLC_controller.onStatusChangedCallback(status);
}
	
VLCcontrols.prototype.load = function() {
	this.target.width = this.width ;
	this.target.style.width = this.width ;
	this.target.height = this.height;
	this.target.style.height = this.height ;
	this.updateStatusText();
}

VLCcontrols.prototype.stop = function() {
	this.debug("stop");
	this.target.playlist.stop();
}

VLCcontrols.prototype.restart = function() {
	this.debug("restart");
	if (this.target.playlist.isPlaying) this.target.playlist.stop();
	this.target.playlist.play();
}

 

VLCcontrols.prototype.waitForPlaylistToEmpty = function() {
	this.debug("waitForPlaylistToEmpty");
 
        var options = this.options.format_for_vlc();
        this.debug("addplaylist: " +uri_to_play);
        this.debug("options passed: " +options);
		var id = this.target.playlist.add(uri_to_play, uri_to_play, options);
	    this.target.playlist.playItem(id);
 
}


var uri_to_play = "";
VLCcontrols.prototype.doPlay = function(uri) {
	// INTERNAL ONLY
		this.target.audio.volume = parseInt(document.getElementById("_vollabel").innerHTML);
        if (this.target.playlist.isPlaying) this.target.playlist.stop();
		uri_to_play = uri;
		this.waitForPlaylistToEmpty();
}

VLCcontrols.prototype.play = function(uri) {
	alert("play");
	if (this.target.log) this.target.log.verbosity = VLC_controller_log_verbosity;
	this.debug("play " + uri);
    try {this.target.playlist.stop();} catch(e) {}
	setTimeout("VLC_controller.doPlay('" + uri + "')", 250);
}




function VLC_options(VLCcontroller) {
	// better options management
	this.VLCcontroller = VLCcontroller;
	this.options = new Array();
	
	this.set = function(name, value) {
        if (this.VLCcontroller) this.VLCcontroller.debug("set option "+name+"="+value);
        //.debug("io");
		this.options[name] = value || null;
	}
	
	this.del = function(name) {
		delete this.options[name];
		 
	}
	
	this.get = function(name) {
		return this.options[name];
	}
	
	this.clear = function() {
		this.options = new Array();
	}
	
	this.format_for_vlc = function() {
		var tmp_array = new Array();
		var debug_str = "";
		var idx = 0;
		for (var i in this.options)
		{
			var option_str = ":" + i;
			if (this.options[i]) option_str += "=" + this.options[i];
			tmp_array[idx] = option_str;
			debug_str += option_str + " ";
			idx += 1;
		}
        if (this.VLCcontroller) this.VLCcontroller.debug(debug_str);
		return debug_str;
	}
}

/********************************************************
* function : play the appointed URL
* input para: targetURL, targetOptions
* output para: N/A
* return: N/A
**********************************************************/
function doGo(targetURL, targetOptions)
{
	//var vlc = document.getElementById("mymovie");
	var vlc = getVLC("mymovie");
	//alert(targetURL+"---"+targetOptions);
	targetOptions=targetOptions.toString().replace(/,/g, " ");
	//alert(targetOptions);
	if( vlc )
	{
       	vlc.playlist.items.clear();
        	while( vlc.playlist.items.count > 0 )
        	{
            		// clear() may return before the playlist has actually been cleared
            		// just wait for it to finish its job
        	}
        	var itemId = vlc.playlist.add(targetURL, "", targetOptions);
        	if( itemId != -1 )
        	{
            		vlc.playlist.playItem(itemId);
        	}
        	else
        	{
            		alert("cannot play at the moment !");
        	}
	}
}

/***************************************************************************/
var ip_addr = window.location.hostname;
var port = ":" + rtsp_port;
var stream = "media/stream1";
var  URL = "rtsp://" + ip_addr + port + "/" + stream;
var network_caching = ":network-caching=600";
var options = new Array(network_caching);
var video_size = "640";
var video_format = "mjpeg";
/**************************************************************************/

/********************************************************
* function : initialization
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
function init() 
{		
    onVLCPluginReady();
    URL = "rtsp://" + ip_addr + port + "/" + stream;
    doGo(URL, options);
}

/********************************************************
* function : VLC play initialization
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
function vlc_init() 
{		

	var value = "stream1";
	var data = {streamNum: value};
	var date  = new Date().getTime().toString();
	var data = {streamNum: value, date: date};
	$.getJSON('/cgi-bin/getstreaminfo.cgi', data, function (data, status)
	{
		stream=data.url;
		URL = "rtsp://" + ip_addr + port + "/" + stream;
		doGo(URL, options);		
	});

}
function vlc_local_play(filename)
{
	//alert(filename);
	if(filename==null || filename.length==0)
	{
		//alert("Select a video file!");
		return ;
	}
	var prefix = "file:///";
	filename=prefix +filename;		
/*	var opt = [];
	//filename="D:\vlc-record-2013-04-25-09h47m30s--.avi";
	filename=URL;
	doGo(filename, opt);*/
	if( mymovie )
    {
        mymovie.playlist.items.clear();
        while( mymovie.playlist.items.count > 0 )
        {
            // clear() may return before the playlist has actually been cleared
            // just wait for it to finish its job
        }
        itemId = mymovie.playlist.add(filename);
        if( itemId != -1 )
        {
            // play MRL
          //  setTimeout('mymovie.playlist.playItem(itemId)',250);
            mymovie.playlist.playItem(itemId);
        }
        else
        {
            alert("cannot play at the moment !");
        }
//        doItemCount();
    }
}
function vlc_stop()
{
	var vlc = getVLC("mymovie");
	vlc.playlist.stop();
}
function vlc_snapshot(filepath)
{
	if(filepath==null || filepath.length==0)
		filepath = "D:";
	if(checkPathIsWirte(filepath) == true)
		takeSnapshot(filepath);
}
function vlc_fullscreen()
{
	var vlc = getVLC("mymovie");
	vlc.video.toggleFullscreen();
}
function vlc_record(filepath)
{
	if(filepath==null || filepath.length==0)
		filepath = "D:";
	if(playing_flag)
	{
		if(checkPathIsWirte(filepath) == true)
		{
			record_change();
			mymovie.video.toggleRecord(filepath);
		}	
	}	
}

/********************************************************
* function : select video format
* input para: selected format
* output para: N/A
* return: N/A
**********************************************************/
function select_video_format(selected_format)
{
	var cmdurl;

	video_format = selected_format;
	
	if(selected_format == "mjpeg")
	{			
		if(h264_record_state == "recording")
		{
			h264_record_state = "no recording";
			document.getElementById("record").value = "Start recording";
			document.getElementById("record").className = "";
			cmdurl="/cgi-bin/autorecordtest?"+"stop_h264";	
			document.getElementById("hiddenframe_m_record").src = cmdurl;	
		}
			
		URL ="rtsp://"+ip_addr+"/media/stream-mjpeg-g711";
	}
	else if(selected_format == "h264")
	{
		if(mjpeg_record_state == "recording")
		{
			mjpeg_record_state = "no recording";
			document.getElementById("record").value = "Start recording";
			document.getElementById("record").className = "";
			cmdurl="/cgi-bin/autorecordtest?"+"stop_mjpeg";		
			document.getElementById("hiddenframe_m_record").src = cmdurl;	
		}
			
		URL ="rtsp://"+ip_addr+"/media/stream-h264-g711";
	}

	doGo(URL, options);
}

/********************************************************
* function : demultiplexer setting
* input para: n - 1, 2, 3
* output para: N/A
* return: N/A
**********************************************************/
function demultiplexer_setting(n)
{	
	options = [];
	options.push(network_caching);
	switch(n)
	{
		case '1':
			port= ":" + rtsp_port;
			break;
		case '2':
			options.push(":rtsp-tcp");
			port= ":" + rtsp_port;
			break;
		case '3':
			options.push(":rtsp-http");
			options.push(":rtsp-http-port="+http_port);
			port= ""; //Do not need port in url.
			break;
		default:
			break;
	}
	URL = "rtsp://" + ip_addr + port + "/" + stream;
	doGo(URL, options);
}

/********************************************************
* function : change buttons color
* input para: buttons number
* output para: N/A
* return: N/A
**********************************************************/
function change_color(num)
{
	for(var i=1; i<=3; i++)
	{
		var str = document.getElementById('btn_'+i);
		
		if(i == num)
		{
			str.className="btn";
		}
		else
		{
			str.className="";
		}
	}
}

/********************************************************
* function : play or pause the output.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
function play_and_pause()
{
	var flag = document.getElementById('play_and_pause').value; 
	
	if (flag == "pause")
	{
		mymovie.playlist.togglePause();
	  	document.getElementById('play_and_pause').value = "play";
	}
	else if(flag == "play")
	{
		mymovie.playlist.play();
	  	document.getElementById('play_and_pause').value = "pause";
	}
}

function playback()
{
		mymovie.playlist.playBack();
};

var itemId=0;	 
function localplay()
{
    if( mymovie )
    {
        mymovie.playlist.items.clear();
        while( mymovie.playlist.items.count > 0 )
        {
            // clear() may return before the playlist has actually been cleared
            // just wait for it to finish its job
        }
        itemId = mymovie.playlist.add(document.getElementById("restorefile").value);
        if( itemId != -1 )
        {
            // play MRL
          //  setTimeout('mymovie.playlist.playItem(itemId)',250);
            mymovie.playlist.playItem(itemId);
        }
        else
        {
            alert("cannot play at the moment !");
        }
//        doItemCount();
    }
};

var h_flag = 0;
var v_flag = 0;		
var flip = 0;

function DisableButton()
{
  	document.getElementById('HFLIP').disabled = true;
	document.getElementById('VFLIP').disabled = true;
};

function EnableButton()
{
	setTimeout("document.getElementById('HFLIP').disabled = false",200);
	setTimeout("document.getElementById('VFLIP').disabled = false",200);
};

function updateForHflip()
{
	if(h_flag==0)
		h_flag=1;
	else 
		h_flag=0;
	DisableButton();
	EnableButton();
//	mymovie.video.takeHflip(0,0);
};

function updateForVflip()
{
	if(v_flag==0)
		v_flag=1;
	else 
		v_flag=0;
	DisableButton();
	EnableButton();
//  mymovie.video.takeHflip(0,0);
};		

/********************************************************
* function : grab a picture.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
function takeSnapshot(filepath)
{
	try
	{
		mymovie.video.takeSnapshot(filepath);
	}
	catch(exception)
	{
		alert(exception.message);
	}
};

function doHflip(){

   try{
   	flip = mymovie.video.flip;
   	if(flip == 0)
   	{
   		updateForHflip();
   		mymovie.video.takeFlip(h_flag, v_flag);
   		mymovie.video.flip = 1;
   	}
  }
  catch(exception)
  {}
};
function doVflip(){

   try{
   	flip = mymovie.video.flip;
   	if(flip == 0)
   	{
   		updateForVflip();
   		mymovie.video.takeFlip(h_flag, v_flag);
   		mymovie.video.flip = 1;
   	}
  }
  catch(exception)
  {}
};
function setviewsize(size)
{
	video_size = size;
	
	if(size==320){
		mymovie.style.width="320";
		mymovie.style.height="240";
	}
	else if(size==640){
		mymovie.style.width="640";
		mymovie.style.height="480";
	}
}

/********************************************************
* function : increase audio volume.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
var curvalue=50;
function volume_up()
{
	document.getElementById("if_mute").src = "/sound.png";

	curvalue = mymovie.audio.volume;
	curvalue = curvalue + 5;

	if (curvalue <= 0) 
	{
		mymovie.audio.volume = 0;
		curvalue = 0;
	}
	else if (curvalue >= 100)
	{
		mymovie.audio.volume = 100;
		curvalue = 100;
	}
	else
	{
		mymovie.audio.volume = curvalue;
	}

	document.getElementById("vol").innerHTML = curvalue;
}
/********************************************************
* function : increase microphone volume.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/

function mic_volume_up()
{
	document.getElementById("if_mute_mic").src = "/images/mic_on.gif";
	mic_vol = mic_vol + 5;

	if (mic_vol <= 0) 
	{
		mic_vol = 0;
	}
	else if (mic_vol >= 100)
	{
		mic_vol = 100;
	}
	document.getElementById("mic_vol").innerHTML = mic_vol;
	var cmdurl = "/cgi-bin/volcontrol.cgi?"+"dev"+"="+"mic"+"&vol="+mic_vol+"&time="+new Date().getTime();
	//alert(cmdurl);
    	document.getElementById("volcontrol").src = cmdurl;
}
/********************************************************
* function : increase speaker volume.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/

function spk_volume_up()
{
	document.getElementById("if_mute_spk").src = "/images/spk_on.gif";
	spk_vol = spk_vol + 5;

	if (spk_vol <= 0) 
	{
		spk_vol = 0;
	}
	else if (spk_vol >= 100)
	{
		spk_vol = 100;
	}
	document.getElementById("spk_vol").innerHTML = spk_vol;
	var cmdurl = "/cgi-bin/volcontrol.cgi?"+"dev"+"="+"spk"+"&vol="+spk_vol+"&time="+new Date().getTime();
	//alert(cmdurl);
    	document.getElementById("volcontrol").src = cmdurl;
}
/********************************************************
* function : reduce audio volume.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
function volume_down()
{
	curvalue = mymovie.audio.volume;
	curvalue = curvalue - 5;

	if (curvalue <= 0) 
	{
		mymovie.audio.volume = 0;
		curvalue = 0;
		document.getElementById("if_mute").src = "/sound_mute.png";
	}
	else if (curvalue >= 100)
	{
		mymovie.audio.volume = 100;
		curvalue = 100;
		document.getElementById("if_mute").src = "/sound.png";
	}
	else
	{
		mymovie.audio.volume = curvalue;
	}
	
	document.getElementById("vol").innerHTML = curvalue;
}
/********************************************************
* function : reduce microphone volume.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
function mic_volume_down()
{
	mic_vol = mic_vol - 5;

	if (mic_vol <= 0) 
	{
		mic_vol = 0;
		document.getElementById("if_mute_mic").src = "/images/mic_off.gif";
	}
	else if (mic_vol >= 100)
	{
		mic_vol = 100;
		document.getElementById("if_mute_mic").src = "/images/mic_on.gif";
	}
	document.getElementById("mic_vol").innerHTML = mic_vol;
	var cmdurl = "/cgi-bin/volcontrol.cgi?"+"dev"+"="+"mic"+"&vol="+mic_vol+"&time="+new Date().getTime();
	//alert(cmdurl);
    	document.getElementById("volcontrol").src = cmdurl;
}
/********************************************************
* function : reduce speaker volume.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
function spk_volume_down()
{
	spk_vol = spk_vol - 5;

	if (spk_vol <= 0) 
	{
		spk_vol = 0;
		document.getElementById("if_mute_spk").src = "/images/spk_off.gif";
	}
	else if (spk_vol >= 100)
	{
		spk_vol = 100;
		document.getElementById("if_mute_spk").src = "/images/spk_on.gif";
	}
	document.getElementById("spk_vol").innerHTML = spk_vol;
	var cmdurl = "/cgi-bin/volcontrol.cgi?"+"dev"+"="+"spk"+"&vol="+spk_vol+"&time="+new Date().getTime();
	//alert(cmdurl);
    	document.getElementById("volcontrol").src = cmdurl;
}
/********************************************************
* function : mute switch.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
var ifmute = false;
var volume = 0;
function press_mute()
{
	if(!ifmute)
	{
		volume = mymovie.audio.volume;

		ifmute =! ifmute;
		document.getElementById("if_mute").src = "/sound_mute.png";

		mymovie.audio.volume = 0;
		document.getElementById("vol").innerHTML = 0;
	}
	else
	{		
		ifmute =!ifmute;
		document.getElementById("if_mute").src = "/sound.png";
		
		mymovie.audio.volume = volume;
		document.getElementById("vol").innerHTML = volume;
	}	
}
/********************************************************
* function : mute switch.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
function press_mic_mute()
{

	if(!ifmute_mic)
	{
		document.getElementById("if_mute_mic").src = "/images/mic_off.gif";

		document.getElementById("mic_vol").innerHTML = 0;
		var cmdurl = "/cgi-bin/volcontrol.cgi?"+"dev"+"="+"mic"+"&vol="+"0"+"&time="+new Date().getTime();
	}
	else
	{		
		document.getElementById("if_mute_mic").src = "/images/mic_on.gif";
		
		document.getElementById("mic_vol").innerHTML = mic_vol;
		var cmdurl = "/cgi-bin/volcontrol.cgi?"+"dev"+"="+"mic"+"&vol="+mic_vol+"&time="+new Date().getTime();
	}
	ifmute_mic = !ifmute_mic;
	//alert(cmdurl);
    	document.getElementById("volcontrol").src = cmdurl;
}
/********************************************************
* function : mute switch.
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
function press_spk_mute()
{
	if(!ifmute_spk)
	{
		document.getElementById("if_mute_spk").src = "/images/spk_off.gif";

		document.getElementById("spk_vol").innerHTML = 0;
		var cmdurl = "/cgi-bin/volcontrol.cgi?"+"dev"+"="+"spk"+"&vol="+"0"+"&time="+new Date().getTime();
	}
	else
	{		
		document.getElementById("if_mute_spk").src = "/images/spk_on.gif";
		
		document.getElementById("spk_vol").innerHTML = spk_vol;
		var cmdurl = "/cgi-bin/volcontrol.cgi?"+"dev"+"="+"spk"+"&vol="+spk_vol+"&time="+new Date().getTime();
	}	
	ifmute_spk = !ifmute_spk;
	//alert(cmdurl);
    	document.getElementById("volcontrol").src = cmdurl;
}
/********************************************************
* function : manual recording control
* input para: N/A
* output para: N/A
* return: N/A
**********************************************************/
/* mjpeg/h264 recording state */
var mjpeg_record_state = "no recording";
var h264_record_state = "no recording";
/********************************************************/
function m_record()
{
	var video_codec = document.getElementById("video_codec").value;
	var ipaddr = window.location.hostname;
	var cmdurl;
		
	if (document.getElementById("record").value == "Start recording")
	{
		document.getElementById("record").value = "Stop recording";
		document.getElementById("record").className = "btn";
		if(video_codec == "mjpeg")
		{
			mjpeg_record_state = "recording";
			cmdurl="http://"+ipaddr+"/cgi-bin/autorecordtest?"+"start_mjpeg";
		}
		else if(video_codec == "h264")
		{
			h264_record_state = "recording";
			cmdurl="http://"+ipaddr+"/cgi-bin/autorecordtest?"+"start_h264";
		}
	}
	else if(document.getElementById("record").value == "Stop recording")
	{
	     	document.getElementById("record").value = "Start recording";
		document.getElementById("record").className = "";
		if(video_codec == "mjpeg")
		{
			mjpeg_record_state = "no recording";
			cmdurl="http://"+ipaddr+"/cgi-bin/autorecordtest?"+"stop_mjpeg";
		}
		else if(video_codec == "h264")
		{
			h264_record_state = "no recording";
			cmdurl="http://"+ipaddr+"/cgi-bin/autorecordtest?"+"stop_h264";
		}
	}
	
	document.getElementById("hiddenframe_m_record").src = cmdurl;		
}
function control_ptz(channel,direction)
{
	var cmdurl = "/cgi-bin/controlptz?"+channel+"="+direction;
        document.getElementById("sendcom").src = cmdurl;

}

function getVLC(name)
{
    if (window.document[name])
    {
        return window.document[name];
    }
    if (navigator.appName.indexOf("Microsoft Internet")==-1)
    {
        if (document.embeds && document.embeds[name])
            return document.embeds[name];
    }
    else // if (navigator.appName.indexOf("Microsoft Internet")!=-1)
    {
        return document.getElementById(name);
    }
}
function registerVLCEvent(event, handler)
{
    var vlc = getVLC("mymovie");

    if (vlc) {
        if (vlc.attachEvent) {
            // Microsoft
            vlc.attachEvent (event, handler);
        } else if (vlc.addEventListener) {
            // Mozilla: DOM level 2
            vlc.addEventListener (event, handler, true);
        } else {
            // DOM level 0
            eval("vlc.on" + event + " = handler");
        }
    }
}
// JS VLC API callbacks

function handle_MediaPlayerOpening()
{
    document.getElementById("status_info").innerHTML = LV_Opening;
}

function handle_MediaPlayerPlaying()
{
	//alert("playing");
	document.getElementById("status_info").innerHTML = LV_Playing;
    playing_flag=true;		
}

function handle_MediaPlayerPaused()
{
    document.getElementById("status_info").innerHTML = LV_Paused;
}

function handle_MediaPlayerStopped()
{
    document.getElementById("status_info").innerHTML = LV_Stopped;
    playing_flag=false;	
}

 // VLC Plugin
function onVLCPluginReady()
{
//alert("on Vlc plugin ready");
    registerVLCEvent("MediaPlayerOpening", handle_MediaPlayerOpening);
    registerVLCEvent("MediaPlayerPlaying", handle_MediaPlayerPlaying);
    registerVLCEvent("MediaPlayerPaused", handle_MediaPlayerPaused);
    registerVLCEvent("MediaPlayerStopped", handle_MediaPlayerStopped);
}

