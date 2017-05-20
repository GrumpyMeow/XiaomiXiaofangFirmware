/*common function ,I will move it later*/
String.prototype.colorHex = function () {
    var reg = /^#([0-9a-fA-f]{3}|[0-9a-fA-f]{6})$/;
    var that = this;
    if (/^(rgb|RGB)/.test(that)) {
        var aColor = that.replace(/(?:\(|\)|rgb|RGB)*/g, "").split(",");
        var strHex = "#";
        for (var i = 0; i < aColor.length; i++) {
            var hex = Number(aColor[i]).toString(16);
            /*if(hex === "0"){
            hex += hex;	
            }
            */
            if (hex.length == 1) {
                hex = "0" + hex;
            }
            strHex += hex;
        }
        if (strHex.length !== 7) {
            strHex = that;
        }
        return strHex;
    } else if (reg.test(that)) {
        var aNum = that.replace(/#/, "").split("");
        if (aNum.length === 6) {
            return that;
        } else if (aNum.length === 3) {
            var numHex = "#";
            for (var i = 0; i < aNum.length; i += 1) {
                numHex += (aNum[i] + aNum[i]);
            }
            return numHex;
        }
    } else {
        return that;
    }
};
/*common function ,I will move it later*/
function page_init() {
    document.getElementById("enable").checked = osd_enable;
    document.getElementById("text").value = osd_text;
    document.getElementById("timestamp").checked = osd_timestamp;
    $('#txt_color').css('background-color', "#" + osd_txt_color);
    $('#bg_color').css('background-color', "#" + osd_bg_color);
    document.getElementById('txt_transp').checked = osd_txt_transp;
    document.getElementById('bg_transp').checked = osd_bg_transp;
    document.getElementById('gain').value = osd_gain;
    $("#startX").text(osd_offx);
    $("#startY").text(osd_offy);	
	//DI('startX', osd_offx);
    //DI('startY', osd_offy);
    offx = osd_offx;
    offy = osd_offy;
    $("#location").val(osd_location);
    $("#gain").val(osd_gain);
}
function osd_init() {
    vlc_init(); page_init();
}
var offx = osd_offx;
var offy = osd_offy;
var needUpdate = false;
var RECT_WIDTH = 1280;
var RECT_HEIGHT = 720;
var X_UNIT = 16;                    //units are 16 pixes in x direction.
var Y_UNIT = 8;                      //units is 8 pixes in y direction.
function callColorDlg(sInitColor) {
    //alert(sInitColor);
    if (sInitColor == null)
        var sColor = dlgHelper.ChooseColorDlg();
    else
        var sColor = dlgHelper.ChooseColorDlg(sInitColor);
    sColor = sColor.toString(16);
    if (sColor.length < 6) {
        var sTempString = "000000".substring(0, 6 - sColor.length);
        sColor = sTempString.concat(sColor);
    }
    sColor = "#".concat(sColor).toUpperCase();
    return sColor;
}
function txt_color(initcolor) {
    //	if(navigator.appName.indexOf("Microsoft Internet Explorer") != -1){
    //		var ret  =  callColorDlg(initcolor);
    //		document.getElementById('txt_color').style.backgroundColor=ret;
    //		var txt_color=document.getElementById('txt_color').style.backgroundColor;	
    //		var data = {op:"action", type:"change_txt_color", txt_color:"0x"+txt_color.substring(1,txt_color.length)};
    //		$.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime() , data, null);			
    //	}else{
    $('.color-box-txt').click();
    //	}

}
function bg_color(initcolor) {
    //	if(navigator.appName.indexOf("Microsoft Internet Explorer") != -1){
    //		var ret  =  callColorDlg(initcolor);
    //		document.getElementById('bg_color').style.backgroundColor=ret;
    //		var bg_color=document.getElementById('bg_color').style.backgroundColor;
    //		var data = {op:"action", type:"change_bg_color", bg_color:"0x"+bg_color.substring(1,bg_color.length)};
    //		$.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime() , data, null);		
    //	}else{
    $('.color-box-bg').click();
    //	}

}
$(function () {
    $('.color-box-txt').colpick({
        colorScheme: 'dark',
        layout: 'rgbhex',
        color: osd_txt_color,
        onSubmit: function (hsb, hex, rgb, el) {
            $('#txt_color').css('background-color', '#' + hex);
            $(el).colpickHide();
            var txt_color = $('#txt_color').css('background-color').colorHex().toString();
            var data = { op: "action", type: "change_txt_color", txt_color: "0x" + txt_color.substring(1, txt_color.length) };
            $.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime(), data, null);
        }
    });
    $('.color-box-bg').colpick({
        colorScheme: 'dark',
        layout: 'rgbhex',
        color: osd_bg_color,
        onSubmit: function (hsb, hex, rgb, el) {
            $('#bg_color').css('background-color', '#' + hex);
            $(el).colpickHide();
            var bg_color = $('#bg_color').css('background-color').colorHex().toString();
            var data = { op: "action", type: "change_bg_color", bg_color: "0x" + bg_color.substring(1, bg_color.length) };
            $.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime(), data, null);
        }
    });
});
function changeTxtTransp() {
    var txt_transp = document.getElementById("txt_transp");
    var data = { op: "action", type: "change_txt_transp", txt_transp: txt_transp.checked };
    $.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime(), data, null);
}
function changeBgTransp() {
    var bg_transp = document.getElementById("bg_transp");
    var data = { op: "action", type: "change_bg_transp", bg_transp: bg_transp.checked };
    $.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime(), data, null);
}
function location_change(value) {
    data = { op: "action", type: "change_location", location: value };
    $.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime(), data, processData);
    function processData(data, status) {
    	$("#startX").text(data.x);
    	$("#startY").text(data.y);		
        //DI('startX', data.x);
        //DI('startY', data.y);
        offx = data.x;
        offy = data.y;
    }
}
function finetune_change(direction, valuex, valuey) {
    var location = document.getElementById("location").value;
    valuex = valuex * X_UNIT;
    valuey = valuey * Y_UNIT;
    var data = { op: "action", type: "finetune_change", location: location, offx: offx, offy: offy, direction: direction, x: valuex, y: valuey };
    $.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime(), data, processData);
    function processData(data, status) {
    	$("#startX").text(data.x);
    	$("#startY").text(data.y);		
        //DI('startX', data.x);
        //DI('startY', data.y);
        offx = data.x;
        offy = data.y;
    }
}
function gainChange(value) {
    var location = document.getElementById("location").value;
    var data = { op: "action", type: "change_gain", location: location, offx: offx, offy: offy, osd_gain: value };
    $.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime(), data, null);
   /* function processData(data, status) {
    	$("#startX").text(data.x);
    	$("#startY").text(data.y);		
        //DI('startX', data.x);
        //DI('startY', data.y);
        offx = data.x;
        offy = data.y;
    }	*/
}
function changeOsd() {
    var enable = document.getElementById("enable");
    var text = document.getElementById("text");
    var timestamp = document.getElementById("timestamp");
    var location = document.getElementById("location").value;
    var data = { op: "action", type: "change_osd_display", enable: enable.checked, text: text.value, timestamp: timestamp.checked, location: location};
    $.getJSON('/cgi-bin/osd_setting.cgi?t=' + new Date().getTime(), data, null);
   /* function processData(data, status) {
    	$("#startX").text(data.x);
    	$("#startY").text(data.y);		
        //DI('startX', data.x);
        //DI('startY', data.y);
        offx = data.x;
        offy = data.y;
    }	*/
}
function update_value() {
    osd_enable = document.getElementById("enable").checked;
    osd_text = document.getElementById("text").value;
    osd_timestamp = document.getElementById("timestamp").checked;
    osd_txt_color = document.getElementById('txt_color').style.backgroundColor;
    osd_bg_color = document.getElementById('bg_color').style.backgroundColor;
    osd_txt_transp = document.getElementById('txt_transp').checked;
    osd_bg_transp = document.getElementById('bg_transp').checked;
    osd_gain = document.getElementById('gain').value;
    osd_location = document.getElementById('location').value;
    osd_offx = offx;
    osd_offy = offy;
}
function saveOsd() {
    var cmdurl;
    var enable = document.getElementById("enable");
    var text = document.getElementById("text");
    var timestamp = document.getElementById("timestamp");
//    var txt_color = document.getElementById('txt_color').style.backgroundColor;
//    var bg_color = document.getElementById('bg_color').style.backgroundColor;
    var txt_color = $("#txt_color").css('background-color').colorHex().toString();
    var bg_color = $("#bg_color").css('background-color').colorHex().toString();
    var txt_transp = document.getElementById("txt_transp");
    var bg_transp = document.getElementById("bg_transp");
    var gain = document.getElementById('gain');
    var location = document.getElementById('location');
    //alert(offx +" "+ offy);
    cmdurl = "/cgi-bin/osd_setting.cgi?op=action" + "&type=" + "osd" + "&enable=" + enable.checked + "&text=" + text.value + "&timestamp=" + timestamp.checked + "&txt_color=" + "0x" + txt_color.substring(1, txt_color.length) + "&bg_color=" + "0x" + bg_color.substring(1, bg_color.length) + "&txt_transp=" + txt_transp.checked + "&bg_transp=" + bg_transp.checked + "&osd_gain=" + gain.value + "&offx=" + offx + "&offy=" + offy + "&location=" + location.value + "&time=" + new Date().getTime().toString();
    //alert(cmdurl);
    document.getElementById("hiddenframe_image").src = cmdurl;
    update_value();
}
function rst() {
    //alert("resett");
    page_init();
    saveOsd();
}
$(window).unload(function (){
	rst();
});
function initial_language() {
    $("#header").text(OS_TITLE);
    $(".enable_text").text(OS_ENABLE);

    $(".text_text").text(OS_TEXT);
    $(".timestamp_text").text(OS_TIMESTAMP);
    $(".textcolor_text").text(OS_TEXTCOLOR);
    $(".transp_text").text(OS_TRANSP);
    $(".bg_color_text").text(OS_BACKCOLOR);
    $(".location_text").text(OS_LOCATION);
    $(".lefttop").text(OS_LEFTTOP);
    $(".righttop").text(OS_RIGHTTOP);
    $(".leftbottom").text(OS_LEFTBOTTOM);
    $(".rightbottom").text(OS_RIGHTBOTTOM);
    $(".gain_text").text(OS_GAIN);
    $(".big").text(OS_BIG);
    $(".small").text(OS_SMALL);
	$(".finetune_text").text(OS_FINETUNE);
    $("#submit").val(OS_SAVE);
    $("#reset").val(OS_RESET);

}
function initial_vlc() {
    WidthHeight = ' width="400" height="300" ';
    AxvlcObject = ObjectBegin + AxvlcURL + AxvlcCab + WidthHeight + CloseAngle + EmbedBegin + WidthHeight + EmbedEnd + ObjectEnd;
    //alert(AxvlcObject);
    //$("#player").html(AxvlcObject);
}
function initial_events() {
    $("#enable").click(function () {
        changeOsd();
    });
    $("#text").keyup(function () {
        changeOsd();
    });
    $("#timestamp").click(function () {
        changeOsd();
    });
    $("#txt_color").click(function () {
        txt_color($('#txt_color').css('background-color').colorHex());
    });
    $("#txt_transp").click(function () {
        changeTxtTransp();
    });
    $("#bg_color").click(function () {
        bg_color($('#bg_color').css('background-color').colorHex());
    });
    $("#bg_transp").click(function () {
        changeBgTransp();
    });
    $("#location").change(function () {
        location_change($(this).val());
    });
    $("#gain").change(function () {
        gainChange($(this).val());
    });
    $("#submit").click(function () {
        saveOsd();
    });
    $("#reset").click(function () {
        rst();
    });
}
//document ready
$(function () {
    initial_language();
    initial_vlc();
    initial_events();
    osd_init();
});
