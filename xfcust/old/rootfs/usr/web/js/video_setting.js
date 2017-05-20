/*common function ,I will move it later*/
function setRadioBox(radioName, radiovalue) {
    var obj = document.getElementsByName(radioName);
    for (i = 0; i < obj.length; i++) {

        if (obj[i].value == radiovalue) {
            obj[i].checked = true;
        }
    }

    return true;
}
function getRadioBoxValue(radioName) {
    var obj = document.getElementsByName(radioName);
    for (i = 0; i < obj.length; i++) {

        if (obj[i].checked == true) {
            return obj[i].value;
        }
    }

    return false;
}
/*common function ,I will move it later*/

var videoFormat1preValue = null;
var videoFormat2preValue = null;
var videoFormat3preValue = null;
function page_init() {
    document.getElementById("videoformat1").value = stream1_videoformat;
    document.getElementById("framerate1").value = stream1_fps;
    document.getElementById("value_bitrate1").value = stream1_bitrate;
    document.getElementById("value_quality1").value = stream1h264_quality;
    document.getElementById("mjpeg_quality1").value = stream1mjpeg_quality;
    setRadioBox('qua_bit1', stream1_bit_or_qua)
    document.getElementById("gop1").value = stream1_gop;
    changeQua_Bit(1);
    changeVideoFormat1(videoFormat1preValue);
    document.getElementById("stream3_enable").checked = stream3_enable;
    document.getElementById("stream3_enable").value = stream3_enable_value;
    document.getElementById("videoformat3").value = stream3_videoformat;
    document.getElementById("framerate3").value = stream3_fps;
    document.getElementById("value_bitrate3").value = stream3_bitrate;
    document.getElementById("value_quality3").value = stream3h264_quality;
    document.getElementById("mjpeg_quality3").value = stream3mjpeg_quality;
    setRadioBox('qua_bit3', stream3_bit_or_qua)
    document.getElementById("gop3").value = stream3_gop;
    changeQua_Bit(3);
    changeVideoFormat2(3);
    document.getElementById("stream2_enable").checked = stream2_enable;
    document.getElementById("stream2_enable").value = stream2_enable_value;
    document.getElementById("videoformat2").value = stream2_videoformat;
    document.getElementById("framerate2").value = stream2_fps;
    document.getElementById("value_bitrate2").value = stream2_bitrate;
    document.getElementById("value_quality2").value = stream2h264_quality;
    document.getElementById("mjpeg_quality2").value = stream2mjpeg_quality;
    setRadioBox('qua_bit2', stream2_bit_or_qua)
    document.getElementById("gop2").value = stream2_gop;
    changeQua_Bit(2);
    changeVideoFormat2(2);
}
function video_setting_init() {
    init_videoFormat(1);
    page_init();
}
function validate() {
    var videoFormat1 = document.getElementById('videoformat1');
    var videoFormat2 = document.getElementById('videoformat2');
    var videoFormat3 = document.getElementById('videoformat3');
    if (videoFormat1.value.search(/h.264/i) != -1) {
        if (getRadioBoxValue("qua_bit1") == "bitrate") {
            var bitrate = document.getElementById('value_bitrate1').value;
            if (parseInt(bitrate) < 64 || parseInt(bitrate) > 12000) {
                alert(VS_BITRATE_ERROR);
                return false;
            }
        }
    }
    if (videoFormat2.value.search(/h.264/i) != -1) {
        if (getRadioBoxValue("qua_bit2") == "bitrate") {
            var bitrate = document.getElementById('value_bitrate2').value;
            if (parseInt(bitrate) < 64 || parseInt(bitrate) > 12000) {
                alert(VS_BITRATE_ERROR);
                return false;
            }
        }
    }
    if (videoFormat3.value.search(/h.264/i) != -1) {
        if (getRadioBoxValue("qua_bit3") == "bitrate") {
            var bitrate = document.getElementById('value_bitrate3').value;
            if (parseInt(bitrate) < 64 || parseInt(bitrate) > 12000) {
                alert(VS_BITRATE_ERROR);
                return false;
            }
        }
    }
    if (videoFormat1.value.search(/fhd/i) != -1) {
        document.getElementById('stream3_enable').value = "disabled";

        document.getElementById('stream4_enable').value = document.getElementById('stream3_enable').value;
        document.getElementById('videoformat4').value = document.getElementById('videoformat3').value;
        document.getElementById('framerate4').value = document.getElementById('framerate3').value;
        document.getElementById('mjpeg_quality4').value = document.getElementById('mjpeg_quality3').value;
        document.getElementById('qua_bit4').value = document.getElementById('qua_bit3').value;
        document.getElementById('value_quality4').value = document.getElementById('value_quality3').value;
        document.getElementById('value_bitrate4').value = document.getElementById('value_bitrate3').value;
        document.getElementById('gop4').value = document.getElementById('gop3').value;
    }
    else if (document.getElementById("stream2_enable").checked && document.getElementById("stream3_enable").checked) {
        if (parseInt(document.getElementById("framerate3").value) > parseInt(document.getElementById("framerate2").value)) {
            alert(VS_FRAME_ERROR);
            return false;
        }
    }
    if (document.getElementById("videoformat1").value == stream1_videoformat &&
		document.getElementById("framerate1").value == stream1_fps &&
		document.getElementById("stream3_enable").checked == stream3_enable &&
		document.getElementById("videoformat3").value == stream3_videoformat &&
		document.getElementById("framerate3").value == stream3_fps &&
		document.getElementById("stream2_enable").checked == stream2_enable &&
		document.getElementById("videoformat2").value == stream2_videoformat &&
		document.getElementById("framerate2").value == stream2_fps) {
        document.getElementById('restart_server').value = "false";
    }
    document.getElementById('submit').disabled = "disabled";
    document.getElementById('reset').disabled = "disabled";
    return true;
}
function changeQua_Bit(id) {
    if (id == 1) {
        if (document.getElementById('quality1').checked) {
            /*document.getElementById('span_quality1').setAttribute("disabled", "");
            document.getElementById('span_bitrate1').setAttribute("disabled", "disabled");
            document.getElementById('value_quality1').disabled = false;
            document.getElementById('value_bitrate1').disabled = true;*/
			$("#span_quality1").prop("disabled",false);
			$("#value_quality1").prop("disabled",false);			
			$("#span_bitrate1").prop("disabled",true);
			$("#value_bitrate1").prop("disabled",true);
        }
        else {
            /*document.getElementById('span_quality1').setAttribute("disabled", "disabled");
            document.getElementById('span_bitrate1').setAttribute("disabled", "");
            document.getElementById('value_quality1').disabled = true;
            document.getElementById('value_bitrate1').disabled = false;*/
			$("#span_quality1").prop("disabled",true);
			$("#value_quality1").prop("disabled",true);
			$("#span_bitrate1").prop("disabled",false);
			$("#value_bitrate1").prop("disabled",false);
        }
    }
    if (id == 2) {
        if (document.getElementById('quality2').checked) {
            /*document.getElementById('span_quality2').setAttribute("disabled", "");
            document.getElementById('span_bitrate2').setAttribute("disabled", "disabled");
            document.getElementById('value_quality2').disabled = false;
            document.getElementById('value_bitrate2').disabled = true;*/
			$("#span_quality2").prop("disabled",false);
			$("#value_quality2").prop("disabled",false);			
			$("#span_bitrate2").prop("disabled",true);
			$("#value_bitrate2").prop("disabled",true);		
        }
        else {
            /*document.getElementById('span_quality2').setAttribute("disabled", "disabled");
            document.getElementById('span_bitrate2').setAttribute("disabled", "");
            document.getElementById('value_quality2').disabled = true;
            document.getElementById('value_bitrate2').disabled = false;*/
			$("#span_quality2").prop("disabled",true);
			$("#value_quality2").prop("disabled",true);
			$("#span_bitrate2").prop("disabled",false);
			$("#value_bitrate2").prop("disabled",false);			
        }
    }
    if (id == 3) {
        if (document.getElementById('quality3').checked) {
            /*document.getElementById('span_quality3').setAttribute("disabled", "");
            document.getElementById('span_bitrate3').setAttribute("disabled", "disabled");
            document.getElementById('value_quality3').disabled = false;
            document.getElementById('value_bitrate3').disabled = true;*/
			$("#span_quality3").prop("disabled",false);
			$("#value_quality3").prop("disabled",false);			
			$("#span_bitrate3").prop("disabled",true);
			$("#value_bitrate3").prop("disabled",true);				
        }
        else {
            /*document.getElementById('span_quality3').setAttribute("disabled", "disabled");
            document.getElementById('span_bitrate3').setAttribute("disabled", "");
            document.getElementById('value_quality3').disabled = true;
            document.getElementById('value_bitrate3').disabled = false;*/
			$("#span_quality3").prop("disabled",true);
			$("#value_quality3").prop("disabled",true);
			$("#span_bitrate3").prop("disabled",false);
			$("#value_bitrate3").prop("disabled",false);
        }
    }
}
function changevideotype(id) {
    var videoFormat1 = document.getElementById('videoformat1');
    var videoFormat2 = document.getElementById('videoformat2');
    var videoFormat3 = document.getElementById('videoformat3');
    if (id == 1) {
        //alert("changevideotype:"+videoFormat1.value);
        if (videoFormat1.value.search(/mjpeg/i) != -1) {
            //alert("mjpeg");
            document.getElementById("stream1mjpeg_para").style.display = "";
            document.getElementById("stream1h.264_para1").style.display = "none";
            document.getElementById("stream1h.264_para2").style.display = "none";
            document.getElementById("stream1h.264_para3").style.display = "none";
        }
        else {
            //alert("h264");
            document.getElementById("stream1mjpeg_para").style.display = "none";
            document.getElementById("stream1h.264_para1").style.display = "";
            document.getElementById("stream1h.264_para2").style.display = "";
            document.getElementById("stream1h.264_para3").style.display = "";
        }

    }
    if (id == 2) {
        if (videoFormat2.value.search(/mjpeg/i) != -1) {
            document.getElementById("stream2mjpeg_para").style.display = "";
            document.getElementById("stream2h.264_para1").style.display = "none";
            document.getElementById("stream2h.264_para2").style.display = "none";
            document.getElementById("stream2h.264_para3").style.display = "none";
        }
        else {
            document.getElementById("stream2mjpeg_para").style.display = "none";
            document.getElementById("stream2h.264_para1").style.display = "";
            document.getElementById("stream2h.264_para2").style.display = "";
            document.getElementById("stream2h.264_para3").style.display = "";
        }
    }
    if (id == 3) {
        if (videoFormat3.value.search(/mjpeg/i) != -1) {
            document.getElementById("stream3mjpeg_para").style.display = "";
            document.getElementById("stream3h.264_para1").style.display = "none";
            document.getElementById("stream3h.264_para2").style.display = "none";
            document.getElementById("stream3h.264_para3").style.display = "none";
        }
        else {
            document.getElementById("stream3mjpeg_para").style.display = "none";
            document.getElementById("stream3h.264_para1").style.display = "";
            document.getElementById("stream3h.264_para2").style.display = "";
            document.getElementById("stream3h.264_para3").style.display = "";
        }
    }
}
function changeVideoFormat2(id) {
    var videoFormat1 = document.getElementById('videoformat1');
    var videoFormat2 = document.getElementById('videoformat2');
    var videoFormat3 = document.getElementById('videoformat3');

    if (id == 2) {
        var newOption = true;
        var optionChange = true;
        //alert(prevalue);
        prevalue = videoFormat2preValue;
        if (prevalue != null) {
            if ((prevalue.search(/d1/i) != -1) && (videoFormat2.value.search(/d1/i) != -1))
                optionChange = false;
            if ((prevalue.search(/d1/i) == -1) && (videoFormat2.value.search(/d1/i) == -1))
                optionChange = false;
        }

        if (optionChange) {
            if (videoFormat2.value.search(/d1/i) != -1) {
                if (videoFormat2.value.search(/mjpegd1/i) != -1)
                    videoFormat3.value = "h.264d1";
                if (videoFormat2.value.search(/h.264d1/i) != -1)
                    videoFormat3.value = "mjpegd1";
            }
            if (videoFormat2.value.search(/vga/i) != -1) {
                if (videoFormat2.value.search(/mjpegvga/i) != -1)
                    videoFormat3.value = "h.264vga";
                if (videoFormat2.value.search(/h.264vga/i) != -1)
                    videoFormat3.value = "mjpegvga";
                if (videoFormat2.value.search(/mjpegqvga/i) != -1)
                    videoFormat3.value = "h.264qvga";
                if (videoFormat2.value.search(/h.264qvga/i) != -1)
                    videoFormat3.value = "mjpegqvga";
            }

            for (var i = 0; i < videoFormat2.length; i++) {
                if (videoFormat2.options[i].value == videoFormat3preValue) {
                    videoFormat2.options[i].disabled = false;
                    break;
                }
            }
            for (var i = 0; i < videoFormat2.length; i++) {
                if (videoFormat2.options[i].value == videoFormat3.value) {
                    videoFormat2.options[i].disabled = true;
                    break;
                }
            }
        }
        for (var i = 0; i < videoFormat3.length; i++) {
            if (videoFormat3.options[i].value == videoFormat2preValue) {
                videoFormat3.options[i].disabled = false;
                break;
            }
        }
        for (var i = 0; i < videoFormat3.length; i++) {
            if (videoFormat3.options[i].value == videoFormat2.value) {
                videoFormat3.options[i].disabled = true;
                break;
            }
        }
        videoFormat2preValue = videoFormat2.value;
        changevideotype(2);
        if (optionChange) {
            videoFormat3preValue = videoFormat3.value;
            changevideotype(3);
        }
    }
    if (id == 3) {
        var newOption = true;
        var optionChange = true;
        //alert(prevalue);
        prevalue = videoFormat3preValue;
        if (prevalue != null) {
            if ((prevalue.search(/d1/i) != -1) && (videoFormat3.value.search(/d1/i) != -1))
                optionChange = false;
            if ((prevalue.search(/d1/i) == -1) && (videoFormat3.value.search(/d1/i) == -1))
                optionChange = false;
        }

        if (optionChange) {
            if (videoFormat3.value.search(/d1/i) != -1) {
                if (videoFormat3.value.search(/mjpegd1/i) != -1)
                    videoFormat2.value = "h.264d1";
                if (videoFormat3.value.search(/h.264d1/i) != -1)
                    videoFormat2.value = "mjpegd1";
            }
            if (videoFormat3.value.search(/vga/i) != -1) {
                if (videoFormat3.value.search(/mjpegvga/i) != -1)
                    videoFormat2.value = "h.264vga";
                if (videoFormat3.value.search(/h.264vga/i) != -1)
                    videoFormat2.value = "mjpegvga";
                if (videoFormat3.value.search(/mjpegqvga/i) != -1)
                    videoFormat2.value = "h.264qvga";
                if (videoFormat3.value.search(/h.264qvga/i) != -1)
                    videoFormat2.value = "mjpegqvga";
            }

            for (var i = 0; i < videoFormat3.length; i++) {
                if (videoFormat3.options[i].value == videoFormat2preValue) {
                    videoFormat3.options[i].disabled = false;
                    break;
                }
            }
            for (var i = 0; i < videoFormat3.length; i++) {
                if (videoFormat3.options[i].value == videoFormat2.value) {
                    videoFormat3.options[i].disabled = true;
                    break;
                }
            }
        }
        for (var i = 0; i < videoFormat2.length; i++) {
            if (videoFormat2.options[i].value == videoFormat3preValue) {
                videoFormat2.options[i].disabled = false;
                break;
            }
        }
        for (var i = 0; i < videoFormat2.length; i++) {
            if (videoFormat2.options[i].value == videoFormat3.value) {
                videoFormat2.options[i].disabled = true;
                break;
            }
        }
        videoFormat3preValue = videoFormat3.value;
        changevideotype(3);
        if (optionChange) {
            videoFormat2preValue = videoFormat2.value;
            changevideotype(2);
        }
    }
    ShowStream3();
}
function ShowStream3() {
    var videoFormat1 = document.getElementById('videoformat1');
   // var stream3 = document.getElementById("stream3div");
    if (videoFormat1.value.search(/fhd/i) != -1) {
		$("#stream3div").attr("disabled", "disabled");
    }
    else {
		$("#stream3div").removeAttr("disabled");
    }
}
function changeVideoFormat1(prevalue) {
    var videoFormat1 = document.getElementById('videoformat1');
    videoFormat1preValue = videoFormat1.value;
    ShowStream3();
    changevideotype(1);
}
function init_videoFormat(id) {
    var videoFormat1 = document.getElementById('videoformat1');
    if (id == 1) {
        if (sensorName.search(/ov2715/i) != -1) {
            videoFormat1.options.length = 0;
            newOption = new Option("H.264 FHD(1920x1080)", "h.264fhd", false, false);
            videoFormat1.add(newOption);
            newOption = new Option("H.264 HD(1280x720)", "h.264hd", false, false);
            videoFormat1.add(newOption);
        }
        else {
            videoFormat1.options.length = 0;
            newOption = new Option("H.264 HD(1280x720)", "h.264hd", false, false);
            videoFormat1.add(newOption);
        }
    }
}
function initial_language() {
    $("#header").text(VS_VideoSetting);
    $("#stream1").text(VS_Stream1);
    $("#stream2").text(VS_Stream2);
    $("#stream3").text(VS_Stream3);
    $(".videoformat_text").text(VS_VideoFormat);
    $(".framerate_text").text(VS_FrameRate);
    $(".quality_text").text(VS_Quality);
    $(".bitrate_text").text(VS_BitRate);
    $(".bitrate_range_text").text(VS_BitRateRange);
    $(".gop_text").text(VS_GOP);
    $(".gop_range_text").text(VS_GOPRange);
    $("#submit").val(VS_Save);
    $("#reset").val(VS_Reset);
}
function initial_events() {

    $("#videoformat1").change(function () {
        changeVideoFormat1(videoFormat1preValue);
    });
    $("[name=qua_bit1]").click(function () {
        changeQua_Bit(1);
    });
    $("#stream2_enable").change(function () {
        $(this).is(":checked") ? $(this).val("enable") : $(this).val("disable");
    });
    $("#videoformat2").change(function () {
        changeVideoFormat2(2);
    });
    $("[name=qua_bit2]").click(function () {
        changeQua_Bit(2);
    });
    $("#stream3_enable").change(function () {
        $(this).is(":checked") ? $(this).val("enable") : $(this).val("disable");
    });
    $("#videoformat3").change(function () {
        changeVideoFormat2(3);
    });
    $("[name=qua_bit3]").click(function () {
        changeQua_Bit(3);
    });
    $("#reset").click(function () {
        page_init();
    });
}
//document ready
$(function () {
    initial_language();
    initial_events();
    video_setting_init();
});
