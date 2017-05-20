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
var mousedown_left_flag = false;
var mousedown_right_flag = false;
var block_flag_array = new Array();
for (var i = 1; i <= 192; i++) {
    block_flag_array[i] = 0;
}
var block_flag_array_backup = new Array();
for (var i = 1; i <= 192; i++) {
    block_flag_array[i] = 0;
}
function visible(block_id) {
	//alert(block_id);
    if (mousedown_left_flag) {
        if (!block_flag_array[block_id]) {
            $("#area" + block_id).css("background-color", $("#pm_color").css("background-color")).css("opacity", "1.0");
            block_flag_array[block_id] = !block_flag_array[block_id];
        }
    }
    else if (mousedown_right_flag) {
        if (block_flag_array[block_id]) {
            $("#area" + block_id).css("background-color", $("#pm_color").css("background-color")).css("opacity", "0");
            block_flag_array[block_id] = !block_flag_array[block_id];
        }
    }

}

function submit_pm() {
    var count = "";
    var date_t = new Date().getMilliseconds();
    var i;
    var URL;
    var first = true;
    var color = $("#pm_color").css("background-color").colorHex().toString();
    for (i = 1; i <= 192; i++) {
        block_flag_array_backup[i] = block_flag_array[i];
        if (block_flag_array[i]) {
            if (first) {
                count = count + i;
                first = false;
            }
            else
                count = count + "~" + i;
        }
    }
    URL = "/cgi-bin/private_mask.cgi?date=" + date_t + "&op=action" + "&enable=" + document.getElementById("pm_enable").checked + "&color=" + "0x" + color.substring(1, color.length);
    if (!count) {
        URL += "&areas=";
    }
    else {
        URL += "&areas=" + count;
    }
    //	alert(URL);
    document.getElementById("hiddenframe_image").src = URL;
    //	pm_enable_g = document.getElementById("pm_enable").checked;
    //	pm_color_g = color.substring(1,color.length);
    pm_area_g = count;

}

function show_areas_pm(pm_areas) {
    for (var i = 1; i <= 192; i++) {
        $("#area" + i).css("background-color", $("#pm_color").css("background-color")).css("opacity", "0");
    }	
    var array = pm_areas.split("~");
    //alert(color+"=" + array.length);
    for (var i = 0; i < array.length; i++) {
        if (!array[i])
            break;
        if (!block_flag_array[array[i]]) {
            //document.getElementById(array[i]).style.backgroundColor=pm_color_g;
            //document.getElementById(array[i]).style.filter="alpha(opacity=90)";
            $("#area" + array[i]).css("background-color", "#" + pm_color_g).css("opacity", "1.0");
            block_flag_array[array[i]] = !block_flag_array[array[i]];
            block_flag_array_backup[array[i]] = block_flag_array[array[i]];
        }
    }

}
function change_color(color) {
    for (var i = 0; i < block_flag_array.length; i++) {
        if (block_flag_array[i]) {
            //document.getElementById(i).style.backgroundColor=color;
            //document.getElementById(i).style.filter="alpha(opacity=90)";
            $("#area" + i).css("background-color", color).css("opacity", "1.0");
        }
    }
}
function selectAll() {
    for (var i = 1; i <= 192; i++) {
        block_flag_array[i] = 1;
        //document.getElementById(i.toString()).style.backgroundColor=document.getElementById('pm_color').style.backgroundColor;
        //document.getElementById(i.toString()).style.filter="alpha(opacity=90)";
        $("#area" + i).css("background-color", $("#pm_color").css("background-color")).css("opacity", "1.0");
    }
}
function selectNone() {
    for (var i = 1; i <= 192; i++) {
        block_flag_array[i] = 0;
        //document.getElementById(i.toString()).style.backgroundColor=document.getElementById('pm_color').style.backgroundColor;
        //document.getElementById(i.toString()).style.filter="alpha(opacity=0)";
        $("#area" + i).css("background-color", $("#pm_color").css("background-color")).css("opacity", "0");
    }
}
function reset() {
    for (var i = 1; i <= 192; i++) {
        block_flag_array[i] = block_flag_array_backup[i];
        if (!block_flag_array_backup[i]) {
            //document.getElementById(i.toString()).style.backgroundColor=document.getElementById('pm_color').style.backgroundColor;
            //document.getElementById(i.toString()).style.filter="alpha(opacity=0)";
            $("#area" + i).css("background-color", $("#pm_color").css("background-color")).css("opacity", "0");
        }
        else {
            //document.getElementById(i.toString()).style.backgroundColor=document.getElementById('pm_color').style.backgroundColor;
            //document.getElementById(i.toString()).style.filter="alpha(opacity=90)";
            $("#area" + i).css("background-color", $("#pm_color").css("background-color")).css("opacity", "1.0");
        }
    }

    //	document.getElementById('pm_enable').checked=pm_enable_g;
    //	document.getElementById('pm_color').style.backgroundColor=pm_color_g;
    //	change_color(pm_color_g);

}
function pm_init() {
	get_background();	
	show_areas_pm(pm_area_g);
    	image_init_pm();
	
}
function callColorDlg(sInitColor) {
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
function color(initcolor) {
    var cmdurl;
    var date = new Date().getMilliseconds();
    //alert(initcolor);
    //	if(navigator.appName.indexOf("Microsoft Internet Explorer") != -1)
    //	{
    //		var ret  =  callColorDlg(initcolor);
    //		document.getElementById('pm_color').style.backgroundColor=ret;	
    //		change_color(ret);
    //	}
    //	else
    //	{
    $('.color-box').click();

    //	}
    //alert(cmdurl);
}
function image_init_pm() {
    document.getElementById('pm_enable').checked = pm_enable_g;
    //document.getElementById('pm_color').style.backgroundColor=pm_color_g;
    $("#pm_color").css("background-color", "#" + pm_color_g);
}
function get_background() {
    var url = "/back_pic.jpg?" + "time=" + new Date().getTime().toString();
    $("#areas").append(function (){
		return "<img id='back_pic' src='"+url+"'/>"; 
		});
    $("#back_pic").css({
		"position":"absolute",
		"left":"0px",
		"top":"0px",
		"width":"400px",
		"height":"300px",
		});	
}
$(function () {
    $('.color-box').colpick({
        colorScheme: 'dark',
        layout: 'rgbhex',
        color: pm_color_g,
        onSubmit: function (hsb, hex, rgb, el) {
            $('#pm_color').css('background-color', '#' + hex);
            //alert($('#pm_color').css('background-color'));
            $(el).colpickHide();
            var ret = $('#pm_color').css('background-color').colorHex().toString();
			//var ret = $('#pm_color').css('background-color');			
            //alert("ret="+ret);	
            change_color(ret);
        }
    });
});
function initial_language() {
    $("#header").text(PM_TITLE);
    $("#btn_select_all").val(PM_Select_All);
    $("#btn_clean_all").val(PM_Clean_All);
    $("#btn_reset").val(PM_Reset);
    $("#note").text(PM_Note);
    $("#message").text(PM_Note_message);
    $(".enable_text").text(PM_Enable);
    $(".color_text").text(PM_COLOR);
    $("#btn_save").val(PM_Save);
}
function initial_events() {
    $("#profile_select").change(function () {
        profile_change($(this).val());
    });
    $("#btn_select_all").click(function () {
        selectAll();
    });
    $("#btn_clean_all").click(function () {
        selectNone();
    });
    $("#btn_reset").click(function () {
        reset();
    });
    $("#pm_color").click(function () {
        color($('#pm_color').css('background-color').colorHex());
    });
    $("#btn_save").click(function () {
        submit_pm();
    });
    $(document).mousemove(function (e) {
		e.preventDefault();
		e.stopPropagation();
		return false;

    }).mouseup(function (e) {
    	e.preventDefault();
	e.stopPropagation();	
       mousedown_left_flag = mousedown_right_flag = false;
	return false;		
    });
    $(".area").mousedown(function (e) {
	e.preventDefault();
	e.stopPropagation();	
        switch (e.which) //Determine the button of mouse which is pressed by jQuery . 1 left , 2 middle , 3 right . Modify by xyd
        {
            case 1:
                mousedown_left_flag = true;
                break;
            case 3:
                mousedown_right_flag = true;
                break;
            default:
                break;
        }
	$(this).mouseenter();	
	return false;	
    }).contextmenu(function (e) {
   	e.preventDefault();
	e.stopPropagation();	 
       mousedown_left_flag = mousedown_right_flag = false;
        return false;
    }).mouseenter(function (e) {
		//alert("mouseover");
	e.preventDefault();
	e.stopPropagation();			
//alert($(this).attr("id").substr(4));
		visible($(this).attr("id").substr(4));
        //$(this).css("background-color","transparent");
        
    });	
}
//document ready
$(function () {
    initial_language();
    initial_events();
    pm_init();
});
