/*common function ,I will move it later*/
/*common function ,I will move it later*/
var day_color = "#66CCFF";
var night_color = "#000099";
var userdefine_color = "#FFFF00";
var day_value = is_day;
var night_value = is_night;
var userdefine_value = is_userdefine;

function rgbtohex(rgb) {
    if (rgb.search("rgb") != -1) {
        rgb = rgb.match(/^rgb\((\d+),\s*(\d+),\s*(\d+)\)$/);
        function hex(x) {
            return ("0" + parseInt(x).toString(16)).slice(-2);
        }
        rgb = "#" + hex(rgb[1]) + hex(rgb[2]) + hex(rgb[3]);
    }
    return rgb.toUpperCase();
}
function setAWB(auto, init) {
    if (auto) {
        $("#sliderR").slider("disable");
        $("#sliderG").slider("disable");
        $("#sliderB").slider("disable");
        $('.text_rgb').fadeTo('normal', 0.75).attr("disabled", "disabled");
    }
    else {
        $("#sliderR").slider("enable");
        $("#sliderG").slider("enable");
        $("#sliderB").slider("enable");
        $('.text_rgb').fadeTo('normal', 1).removeAttr("disabled", "");
    }
    if (init == false) //change must be excute.
    {
        var red = document.getElementById("r_value").value;
        var green = document.getElementById("g_value").value;
        var blue = document.getElementById("b_value").value;
        var awb = document.getElementById("awb");
        data = {
            op: "action",
            type: "awb",
            awb: awb.checked,
            red: red,
            green: green,
            blue: blue
        };
        $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
    }
}
function setAE(auto, init) {
    if (auto) {
        $("#sliderExposure").slider("disable");
        $('.text_exposure').fadeTo('normal', 0.75).attr("disabled", "disabled");
    }
    else {
        $("#sliderExposure").slider("enable");
        $('.text_exposure').fadeTo('normal', 1).removeAttr("disabled", "");
    }
    if (init == false) //change must be excute.
    {
        var ae_status = document.getElementById("ae_status");
        var exposure = $("#sliderExposure").slider("value");
        data = { op: "action", type: "ae_status", ae_status: ae_status.checked, exposure: exposure };
        $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
    }
}
function setExposureControl(value, init) {
    //alert( $("#sliderExposure").slider("value")+"/"+(parseInt($("#exposure_control").val())*2));
    $("#exposure").val($("#sliderExposure").slider("value") + "/" + (parseInt($("#exposure_control").val()) * 2));
    $("#exposure_min").text((parseInt($("#exposure_control").val()) * 2).toString());
    $("#exposure_max").text((parseInt($("#exposure_control").val()) * 2).toString());
    if (init == false) //change must be excute.
    {
        var ae_status = document.getElementById("ae_status");
        var exposure = $("#sliderExposure").slider("value");
        data = { op: "action", type: "exposure_control", exposure_control: value, ae_status: ae_status.checked, exposure: exposure };
        $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
    }
}
$(function () {
    //slider red
    $("#sliderR").slider({
        range: "min",
        value: 0,
        min: 0,
        max: 255,
        slide: function (event, ui) {
            $("#r_value").val(ui.value);
        },
        stop: function (event, ui) {
            setRed();
        }
    });
    $("#sliderR").slider("value", is_red);

    //slider green
    $("#sliderG").slider({
        range: "min",
        value: 0,
        min: 0,
        max: 255,
        slide: function (event, ui) {
            $("#g_value").val(ui.value);
        },
        stop: function (event, ui) {
            setGreen();
        }
    });
    $("#sliderG").slider("value", is_green);

    //slider blue
    $("#sliderB").slider({
        range: "min",
        value: 0,
        min: 0,
        max: 255,
        slide: function (event, ui) {
            $("#b_value").val(ui.value);
        },
        stop: function (event, ui) {
            setBlue();
        }
    });
    $("#sliderB").slider("value", is_blue);

    //slider contrast
    $("#sliderConstrast").slider({
        range: "min",
        value: 0,
        min: 0,
        max: 64,
        slide: function (event, ui) {
            $("#contrast").val(ui.value);
        },
        stop: function (event, ui) {
            setContrast();
        }
    });
    $("#sliderConstrast").slider("value", is_contrast);

    //slider sharpness
    $("#sliderSharpness").slider({
        range: "min",
        value: 0,
        min: 0,
        max: 6,
        slide: function (event, ui) {
            $("#sharpness").val(ui.value);
        },
        stop: function (event, ui) {
            setSharpness();
        }
    });
    $("#sliderSharpness").slider("value", is_sharpness);

    //slider saturation
    $("#sliderSaturation").slider({
        range: "min",
        value: 0,
        min: 0,
        max: 127,
        slide: function (event, ui) {
            $("#saturation").val(ui.value);
        },
        stop: function (event, ui) {
            setSaturation();
        }
    });
    $("#sliderSaturation").slider("value", is_saturation);

    //slider brightness	
    $("#sliderBrightness").slider({
        range: "min",
        value: 0,
        min: 0,
        max: 127,
        slide: function (event, ui) {
            $("#brightness_value").val(ui.value);
        },
        stop: function (event, ui) {
            setBrightness();
        }
    });
    $("#sliderBrightness").slider("value", is_brightness);

    //slider hue
    $("#sliderHue").slider({
        range: "min",
        value: 0,
        min: 0,
        max: 359,
        slide: function (event, ui) {
            $("#hue_value").val(ui.value);
        },
        stop: function (event, ui) {
            setHue();
        }
    });
    $("#sliderHue").slider("value", is_hue);

    //slider drc	
    $("#sliderDRC").slider({
        range: "min",
        value: 0,
        min: 1,
        max: 16,
        slide: function (event, ui) {
            $("#drc_value").val(ui.value);
        },
        stop: function (event, ui) {
            setDRCValue();
        }
    });
    $("#sliderDRC").slider("value", is_drc_value);

    //slider exposure	
    $("#sliderExposure").slider({
        range: "min",
        value: 0,
        min: 1,
        max: 16,
        slide: function (event, ui) {
            $("#exposure").val(ui.value + "/" + (parseInt($("#exposure_control").val()) * 2));
        },
        stop: function (event, ui) {
            setExposureValue();
        }
    });
    $("#sliderExposure").slider("value", is_exposure);

    $('.text_style').fadeTo('fast', 0.75).attr("disabled", "disabled");

    $(".hour").each(function () {
        $(this).click(function () {
            var id = $(this).attr("id");
            var data = { "background-color": rgbtohex($("#tip").css("background-color")) };
            $(this).css(data);
            day_value = "";
            night_value = "";
            userdefine_value = "";
            for (var i = 0; i < 24; i++) {
                if (rgbtohex($("#d" + i).css("background-color")) == day_color)
                    day_value = day_value + i.toString() + ",";
                if (rgbtohex($("#d" + i).css("background-color")) == night_color)
                    night_value = night_value + i.toString() + ",";
                if (rgbtohex($("#d" + i).css("background-color")) == userdefine_color)
                    userdefine_value = userdefine_value + i.toString() + ",";
            }
            day_value = day_value.slice(0, -1);
            night_value = night_value.slice(0, -1);
            userdefine_value = userdefine_value.slice(0, -1);
            //alert("d="+day_value+"n"+night_value+"u"+userdefine_value);
        })
    });

    /*	$(window).unload(function(){
    var data = {op:"action", type:"unload"};	
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime() , data, null);			
    });
    */
});
function setMirFlip() {
    var flip, mirror;
    mirror = document.getElementById("sensor_mirror");
    flip = document.getElementById("sensor_flip");
    data = { op: "action", type: "mirflip", mirror: mirror.checked, flip: flip.checked };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setDRC() {
    var drc_status;
    drc_status = document.getElementById("sensor_drc");
    data = { op: "action", type: "drc_status", drc_status: drc_status.checked };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setHue() {
    var hue;
    hue = document.getElementById("hue_value").value;
    data = { op: "action", type: "hue", hue: hue };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setDRCValue() {
    var drc_value;
    drc_value = document.getElementById("drc_value").value;
    data = { op: "action", type: "drc_value", drc_value: drc_value };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setBrightness() {
    var brightness;
    brightness = document.getElementById("brightness_value").value;
    data = { op: "action", type: "brightness", brightness: brightness };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setSaturation() {
    var saturation;
    saturation = document.getElementById("saturation").value;
    data = { op: "action", type: "saturation", saturation: saturation };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setSharpness() {
    var sharpness;
    sharpness = document.getElementById("sharpness").value;
    data = { op: "action", type: "sharpness", sharpness: sharpness };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setContrast() {
    var contrast;
    contrast = document.getElementById("contrast").value;
    data = { op: "action", type: "contrast", contrast: contrast };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setRed() {
    var red;
    red = document.getElementById("r_value").value;
    data = { op: "action", type: "red", red: red };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setGreen() {
    var green;
    green = document.getElementById("g_value").value;
    data = { op: "action", type: "green", green: green };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}

function setBlue() {
    var blue;
    blue = document.getElementById("b_value").value;
    data = { op: "action", type: "blue", blue: blue };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}
function setExposureValue() {
    var exposure;
    exposure = document.getElementById("exposure").value;
    data = { op: "action", type: "exposure", exposure: exposure };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, null);
}
function profile_change(value) {
    var profile_color;
    if (value == "0")
        profile_color = day_color;
    if (value == "1")
        profile_color = night_color;
    if (value == "2")
        profile_color = userdefine_color;
    var data = { "background-color": profile_color };
    $("#tip").css(data);

    var data = { op: "action", type: "profile_change", profile: value };
    $.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime(), data, processData);
    function processData(data, status) {
        is_mirror = data.mirror;
        is_flip = data.flip;
        is_contrast = data.contrast;
        is_sharpness = data.sharpness;
        is_saturation = data.saturation;
        is_drc_status = data.drc_status;
        is_drc_value = data.drc_value;
        is_hue = data.hue;
        is_brightness = data.brightness;
        is_red = data.red;
        is_green = data.green;
        is_blue = data.blue;
        is_awb = data.awb;
        is_exposure = data.exposure;
        is_ae_status = data.ae_status;
        is_exposure_control = data.exposure_control;
        //alert(is_mirror +":" +is_flip +":"+is_contrast +":"+is_sharpness +":"+is_saturation +":"+is_drc_status +":"+is_drc_value +":"+is_hue +":"+is_brightness +":"+is_red +":"+is_green +":"+is_blue +":"+is_awb);		
        below_page_init();
    }
}
function profile_init() {
    var profile_color;
    if (("," + is_day + ",").search("," + is_hour + ",") != -1) {
        profile_color = day_color;
        $("#profile_select").val("0");
    }
    if (("," + is_night + ",").search("," + is_hour + ",") != -1) {
        profile_color = night_color;
        $("#profile_select").val("1");
    }
    if (("," + is_userdefine + ",").search("," + is_hour + ",") != -1) {
        profile_color = userdefine_color;
        $("#profile_select").val("2");
    }
    var data = { "background-color": profile_color };
    $("#tip").css(data);
}
function hours_page_init() {
    var array = is_day.split(",");
    for (var i = 0; i < array.length; i++) {
        var data = { "background-color": day_color };
        $("#d" + array[i]).css(data);
    }

    var array = is_night.split(",");
    for (var i = 0; i < array.length; i++) {
        var data = { "background-color": night_color };
        $("#d" + array[i]).css(data);
    }

    var array = is_userdefine.split(",");
    for (var i = 0; i < array.length; i++) {
        var data = { "background-color": userdefine_color };
        $("#d" + array[i]).css(data);
    }
}
function below_page_init() {
    //alert("below_page_init!");
    document.getElementById("sensor_mirror").checked = is_mirror;
    document.getElementById("sensor_flip").checked = is_flip;
    document.getElementById("sensor_drc").checked = is_drc_status;
    document.getElementById("drc_value").value = is_drc_value;
    $("#sliderDRC").slider("value", is_drc_value);
    document.getElementById("contrast").value = is_contrast;
    $("#sliderConstrast").slider("value", is_contrast);
    document.getElementById("sharpness").value = is_sharpness;
    $("#sliderSharpness").slider("value", is_sharpness);
    document.getElementById("saturation").value = is_saturation;
    $("#sliderSaturation").slider("value", is_saturation);
    document.getElementById("brightness_value").value = is_brightness;
    $("#sliderBrightness").slider("value", is_brightness);
    document.getElementById("hue_value").value = is_hue;
    $("#sliderHue").slider("value", is_hue);
    document.getElementById("awb").checked = is_awb;
    setAWB(is_awb, true);
    document.getElementById("r_value").value = is_red;
    $("#sliderR").slider("value", is_red);
    document.getElementById("g_value").value = is_green;
    $("#sliderG").slider("value", is_green);
    document.getElementById("b_value").value = is_blue;
    $("#sliderB").slider("value", is_blue);
    document.getElementById("ae_status").checked = is_ae_status;
    setAE(is_ae_status, true);
    document.getElementById("exposure").value = is_exposure;
    $("#sliderExposure").slider("value", is_exposure);
    document.getElementById("exposure_control").value = is_exposure_control;
    //alert("function setexposurecontrol will be execute!" + is_exposure_control);
    setExposureControl(is_exposure_control, true);
}
function image_init() {
    vlc_init();
    profile_init();
    hours_page_init();
    below_page_init();
}
function update_value() {
    is_day = day_value;
    is_night = night_value;
    is_userdefine = userdefine_value;
    is_mirror = document.getElementById("sensor_mirror").checked;
    is_flip = document.getElementById("sensor_flip").checked;
    is_contrast = document.getElementById("contrast").value;
    is_sharpness = document.getElementById("sharpness").value;
    is_saturation = document.getElementById("saturation").value;
    is_drc_status = document.getElementById("sensor_drc").checked;
    is_drc_value = document.getElementById("drc_value").value;
    is_hue = document.getElementById("hue_value").value;
    is_brightness = document.getElementById("brightness_value").value;
    is_red = document.getElementById("r_value").value;
    is_green = document.getElementById("g_value").value;
    is_blue = document.getElementById("b_value").value;
    is_awb = document.getElementById("awb").checked;
    is_exposure = $("#sliderExposure").slider("value");
    is_ae_status = document.getElementById("ae_status").checked;
    is_exposure_control = document.getElementById("exposure_control").value;
}
function image_save() {
    var cmdurl, flip, mirror, contrast, sharpness, saturation, red, green, blue, awb, drc_status, drc_value, hue, brightness, ae_status, exposure, exposure_control;
    var profile;

    profile = document.getElementById("profile_select").value;
    hue = document.getElementById("hue_value").value;
    brightness = document.getElementById("brightness_value").value;
    drc_status = document.getElementById("sensor_drc")
    drc_value = document.getElementById("drc_value").value;
    mirror = document.getElementById("sensor_mirror");
    flip = document.getElementById("sensor_flip");
    contrast = document.getElementById('contrast').value;
    sharpness = document.getElementById('sharpness').value;
    saturation = document.getElementById('saturation').value;
    red = document.getElementById("r_value").value;
    green = document.getElementById("g_value").value;
    blue = document.getElementById("b_value").value;
    awb = document.getElementById("awb");
    ae_status = document.getElementById("ae_status");
    exposure = $("#sliderExposure").slider("value");
    exposure_control = document.getElementById("exposure_control").value;
    cmdurl = "/cgi-bin/imagesetting.cgi?op=action" + "&type=" + "save" + "&profile=" + profile + "&day=" + day_value + "&night=" + night_value + "&userdefine=" + userdefine_value + "&mirror=" + mirror.checked + "&flip=" + flip.checked + "&contrast=" + contrast + "&sharpness=" + sharpness + "&saturation=" + saturation +
	"&drc_status=" + drc_status.checked + "&drc_value=" + drc_value + "&hue=" + hue + "&brightness=" + brightness + "&red=" + red + "&green=" + green + "&blue=" + blue + "&awb=" + awb.checked + "&exposure=" + exposure + "&ae_status=" + ae_status.checked + "&exposure_control=" + exposure_control + "&time=" + new Date().getTime().toString();
    //alert(cmdurl);
    document.getElementById("hiddenframe_image").src = cmdurl;
    update_value();
}
function rst() {
    hours_page_init();
    below_page_init();
    image_save();
}
function call_img_cgi() {
    //	var data = {op:"action", type:"unload"};	
    //	$.getJSON('/cgi-bin/imagesetting.cgi?t=' + new Date().getTime() , data, null);	
    //alert("unload");	
    cmdurl = "/cgi-bin/imagesetting.cgi?op=action" + "&type=" + "unload" + "&time=" + new Date().getTime().toString();
    document.getElementById("hiddenframe_image").src = cmdurl;
}
$(window).unload(function (){
	call_img_cgi();
});
function initial_language() {
    $("#header").text(IS_IMAGE_SETTING);
    $(".mirror_text").text(IS_MIRROR);
    $(".flip_text").text(IS_FLIP);
    $(".drc_text").text(IS_DRC);
    $(".drc_value_text").text(IS_DRC_VALUE);
    $(".contrast_text").text(IS_CONTRAST);
    $(".sharpness_text").text(IS_SHARPNESS);
    $(".saturation_text").text(IS_SATURATION);
    $(".brightness_text").text(IS_BRIGHTNESS);
    $(".hue_text").text(IS_HUE_VALUE);
    $(".awb_text").text(IS_AWB);
    $("#red_text").text(IS_R_VALUE);
    $("#green_text").text(IS_G_VALUE);
    $("#blue_text").text(IS_B_VALUE);
    $(".ae_status_text").text(IS_AE_STATUS);
    $(".exposure_text").text(IS_EXPOSURE);
    $(".exposure_unit_text").text(IS_EXPOSURE_TIME_UNIT);
    $(".exposure_control_text").text(IS_EXPOSURE_CONTROL);
    $("#save").val(OS_SAVE);
    $("#reset").val(OS_RESET);
}
function initial_vlc() {
    WidthHeight = ' width="400" height="300" ';
    AxvlcObject = ObjectBegin + AxvlcURL + AxvlcCab + WidthHeight + CloseAngle + EmbedBegin + WidthHeight + EmbedEnd + ObjectEnd;
    //alert(AxvlcObject);
    //$("#player").html(AxvlcObject);
}
function initial_window() {
    var win_width = $(window.top).width();
	if (parseInt(win_width) < 1200) {
		$("#tip").css("width", "20px").css("height", "20px");
		$("#d0.hour").css("width", "20px").css("height", "20px");
		$(".hour").css("width", "20px").css("height", "20px");	
		$("#left.time").css("width", "160px").css("height", "20px");
		$("#center.time").css("width", "160px").css("height", "20px");
		$("#right.time").css("width", "160px").css("height", "20px");
	}else
	{
		$("#tip").css("width", "22px").css("height", "22px");
		$("#d0.hour").css("width", "22px").css("height", "22px");
		$(".hour").css("width", "22px").css("height", "22px");	
		$("#left.time").css("width", "176px").css("height", "22px");
		$("#center.time").css("width", "176px").css("height", "22px");
		$("#right.time").css("width", "176px").css("height", "22px");		
	}
}
function initial_events() {
    $("#profile_select").change(function () {
        profile_change($(this).val());
    });
    $("#sensor_mirror").click(function () {
        setMirFlip();
    });
    $("#sensor_flip").click(function () {
        setMirFlip();
    });
    $("#sensor_drc").click(function () {
        setDRC();
    });
    $("#awb").click(function () {
        setAWB($(this).is(':checked'), false);
    });
    $("#ae_status").click(function () {
        setAE($(this).is(':checked'), false);
    });
    $("#exposure_control").click(function () {
        setExposureControl($(this).val(), false);
    });
    $(window).resize(function () {
        initial_window();
    });	
    $("#save").click(function () {
        image_save();
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
    image_init();
    initial_window();	
});
