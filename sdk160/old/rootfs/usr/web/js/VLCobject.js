/**
 * VLCObject v1.0.0: VLC Plugin detection and embed - http://code.revolunet.com/VLCobject/
 *
 * Based on VLCObject by Geoff Stearns 
  * VLCObject is (c) 2008 Julien Bouquillon - revolunet and is released under the MIT License:
 * http://www.opensource.org/licenses/mit-license.php
 *

 */
 
if(typeof revolunet == "undefined") var revolunet = {};
if(typeof revolunet.util == "undefined") revolunet.util = {};
if(typeof revolunet.VLCObjectUtil == "undefined") revolunet.VLCObjectUtil = {};
revolunet.VLCObject = function(id, w, h, ver) {
	if (!document.getElementById) { return; }
	this.params = {};
	this.variables = {};
	this.attributes = [];
	if(id) { this.setAttribute('id', id); }
	if(w) { this.setAttribute('width', w); }
	if(h) { this.setAttribute('height', h); }
	if(ver) { this.setAttribute('version', new revolunet.PlayerVersion(ver.toString().split("."))); }
	this.installedVer = revolunet.VLCObjectUtil.getPlayerVersion();
	if (!window.opera && document.all ) {
		if (!revolunet.unloadSet) {
			revolunet.VLCObjectUtil.prepUnload = function() {
				__vlc_unloadHandler = function(){};
				__vlc_savedUnloadHandler = function(){};
				window.attachEvent("onunload", revolunet.VLCObjectUtil.cleanupVLCs);
			}
			window.attachEvent("onbeforeunload", revolunet.VLCObjectUtil.prepUnload);
			revolunet.unloadSet = true;
		}
	}
}
revolunet.VLCObject.prototype = {
	setAttribute: function(name, value){
		this.attributes[name] = value;
	},
	getAttribute: function(name){
		return this.attributes[name] || "";
	},
	addParam: function(name, value){
		this.params[name] = value;
	},
	getParams: function(){
		return this.params;
	},
	addVariable: function(name, value){
		this.variables[name] = value;
	},
	getVariable: function(name){
		return this.variables[name] || "";
	},
	getVariables: function(){
		return this.variables;
	},
	getVariablePairs: function(){
		var variablePairs = [];
		var key;
		var variables = this.getVariables();
		for(key in variables){
			variablePairs[variablePairs.length] = key +"="+ variables[key];
		}
		return variablePairs;
	},
	getVLCHTML: function() {
		var vlcNode = "";
		if (navigator.plugins && navigator.mimeTypes && navigator.mimeTypes.length) { // netscape plugin architecture

			vlcNode = '<embed type="application/x-vlc-plugin" " pluginspage="http://www.videolan.org" version="VideoLAN.VLCPlugin.2" width="'+ this.getAttribute('width') +'" height="'+ this.getAttribute('height') +'" style="'+ (this.getAttribute('style') || "") +'"';
			vlcNode += ' id="'+ this.getAttribute('id') +'" name="'+ this.getAttribute('id') +'" ';
			var params = this.getParams();
			 for(var key in params){ vlcNode += [key] +'="'+ params[key] +'" '; }
			var pairs = this.getVariablePairs().join("&");
			vlcNode += '/>';
		} else { // PC IE
			vlcNode = '<object id="'+ this.getAttribute('id') +'" codebase="http://172.21.2.132/axvlc.cab"  classid="clsid:9BE31822-FDAD-461B-AD51-BE1D1C159921" width="'+ this.getAttribute('width') +'" height="'+ this.getAttribute('height') +'" style="'+ (this.getAttribute('style') || "") +'">';
			var params = this.getParams();
			for(var key in params) {
			 vlcNode += '<param name="'+ key +'" value="'+ params[key] +'" />';
			}
			vlcNode += "</object>";
		}
		alert(vlcNode);
		return vlcNode;
	},
	write: function(elementId){

		if(this.installedVer.versionIsValid(this.getAttribute('version'))){
			var n = (typeof elementId == 'string') ? document.getElementById(elementId) : elementId;
			n.innerHTML = this.getVLCHTML();
			//trick for IE activex
			if (document.all) {
				var vlc = n.firstChild;
				vlc.style.width = this.attributes["width"]+"px";
				vlc.style.height= this.attributes["height"]+"px";
				}
				
			return true;
		}else{
			var n = (typeof elementId == 'string') ? document.getElementById(elementId) : elementId;
			n.innerHTML = "<div style='width:400px;border:2px solid red;padding:10px'>Your VLC plugin has not been detected !<br><br>please go to <a href='http://www.videolan.org' target='_blank'>http://www.videolan.org</a> to download your plugin.</div>";
			
		}
		return false;
	}
	 
}

/* ---- detection functions ---- */
revolunet.VLCObjectUtil.getPlayerVersion = function(){
	var PlayerVersion = new revolunet.PlayerVersion([0,0,0]);
	if(navigator.plugins && navigator.mimeTypes.length){
		var x = navigator.plugins["VLC Multimedia Plug-in"];
		if(!x) {
		// test with "old" plugin name
		x = navigator.plugins["VLC Multimedia Plugin"];
		}
        if(!x) {
        // 0.8.6a at least
        x = navigator.plugins["VLC multimedia plugin"];
        }

		if(x && x.description) {			
			PlayerVersion = x.description.substring(0, x.description.indexOf(","));
			PlayerVersion = PlayerVersion.replace("Version ", "");
			PlayerVersion = new revolunet.PlayerVersion(PlayerVersion.split("."));
		}
 
	
	} else { // Win IE 
	
		try{
			var axo = new ActiveXObject("VideoLAN.VLCPlugin.2");
			PlayerVersion = new revolunet.PlayerVersion([0,8,6]);
		}catch(e){
			try {
				var axo = new ActiveXObject("VideoLAN.VLCPlugin.1");
				PlayerVersion = new revolunet.PlayerVersion([0,8,5]);
			} catch(e) {
			
			}
			
		}
		if (axo != null) {
			//PlayerVersion = axo.VersionInfo;
		}
	}
 
	return PlayerVersion;
}
revolunet.PlayerVersion = function(arrVersion){
	this.major = arrVersion[0] != null ? parseInt(arrVersion[0]) : 0;
	this.minor = arrVersion[1] != null ? parseInt(arrVersion[1]) : 0;
	this.rev = arrVersion[2] != null ? parseInt(arrVersion[2]) : 0;
	}
revolunet.PlayerVersion.prototype.versionIsValid = function(fv){
	if(this.major < fv.major) return false;
	if(this.major > fv.major) return true;
	if(this.minor < fv.minor) return false;
	if(this.minor > fv.minor) return true;
	if(this.rev < fv.rev) return false;
	return true;
}
/* ---- get value of query string param ---- */
revolunet.util = {
	getRequestParameter: function(param) {
		var q = document.location.search || document.location.hash;
		if (param == null) { return q; }
		if(q) {
			var pairs = q.substring(1).split("&");
			for (var i=0; i < pairs.length; i++) {
				if (pairs[i].substring(0, pairs[i].indexOf("=")) == param) {
					return pairs[i].substring((pairs[i].indexOf("=")+1));
				}
			}
		}
		return "";
	}
}

revolunet.VLCObjectUtil.cleanupVLCs = function() {
	var objects = document.getElementsByTagName("OBJECT");
	for (var i = objects.length - 1; i >= 0; i--) {
		objects[i].style.display = 'none';
		for (var x in objects[i]) {
			if (typeof objects[i][x] == 'function') {
				objects[i][x] = function(){};
			}
		}
	}
}
/* add document.getElementById if needed (mobile IE < 5) */
if (!document.getElementById && document.all) { document.getElementById = function(id) { return document.all[id]; }}

/* add some aliases for ease of use/backwards compatibility */
var getQueryParamValue = revolunet.util.getRequestParameter;
var VLCObject = revolunet.VLCObject;
