/*common function ,I will move it later*/

/*common function ,I will move it later*/
function page_init() {
    $("select").change();     
    document.getElementById("enable1").checked = stream1_enable;
    document.getElementById("enable1").value = stream1_enable_value;
    if (stream1_enable) {
        document.getElementById("codec1").value = stream1_codec;
        //document.getElementById("samplerate1").value = stream1_samplerate;
        changecodec(stream1_codec, 1); document.getElementById("bitrate1").value = stream1_bitrate;
    }
    document.getElementById("enable2").checked = stream2_enable;
    document.getElementById("enable2").value = stream2_enable_value;
    if (stream2_enable) {
        document.getElementById("codec2").value = stream2_codec;
        //document.getElementById("samplerate1").value = stream2_samplerate;
        changecodec(stream2_codec, 2); document.getElementById("bitrate2").value = stream2_bitrate;
    }
    document.getElementById("enable3").checked = stream3_enable;
    document.getElementById("enable3").value = stream3_enable_value;
    if (stream3_enable) {
        document.getElementById("codec3").value = stream3_codec;
        //document.getElementById("samplerate3").value = stream3_samplerate;
        changecodec(stream3_codec, 3); document.getElementById("bitrate3").value = stream3_bitrate;
    }
}
function audioset_init() {
    page_init();
}  	
function validate() {
    document.getElementById('submit').disabled = "disabled";
    document.getElementById('reset').disabled = "disabled";
    return true;
}
function changecodec(value, id) {
    var audiocodec;
    var audiobitrate;
    var newOption;
    if (id == 1) {
        var audiocodec = document.getElementById('codec1');
        var audiobitrate = document.getElementById('bitrate1');
    }
    else if (id == 2) {
        var audiocodec = document.getElementById('codec2');
        var audiobitrate = document.getElementById('bitrate2');
    }
    else if (id == 3) {
        var audiocodec = document.getElementById('codec3');
        var audiobitrate = document.getElementById('bitrate3');
    }
    audiobitrate.options.length = 0;
    if (value == "g726") {
        newOption = new Option("16", "16000", false, true);
        audiobitrate.add(newOption);
        newOption = new Option("24", "24000", false, false);
        audiobitrate.add(newOption);
        newOption = new Option("32", "32000", false, false);
        audiobitrate.add(newOption);
        newOption = new Option("40", "40000", false, false);
        audiobitrate.add(newOption);
    }
    else {
        newOption = new Option("64", "64000", false, true);
        audiobitrate.add(newOption);
    }
}

function initial_language() {
    $("#header").text(AS_AudioSetting);
    $("#stream1").text(AS_Stream1);
    $("#stream2").text(AS_Stream2);
    $("#stream3").text(AS_Stream3);
    $(".stream_enable_text").text(AS_EnableAudio);
    $(".codec_text").text(AS_Encoding);
    $(".samplerate_text").text(AS_SampleRate);
    $(".samplerate_unit_text").text(AS_SampleRateUnit);
    $(".bitrate_text").text(AS_Bitrate);
    $(".bitrate_unit_text").text(AS_BitrateUnit);
    $("#submit").val(AS_Save);
    $("#reset").val(AS_Reset);
}
function initial_events() {
    $("#enable1").change(function () {
        $(this).is(":checked") ? $(this).val("enable") : $(this).val("disable");
    });
    $("#codec1").change(function () {
        changecodec($(this).val(), 1)
    });
    $("#enable2").change(function () {
        $(this).is(":checked") ? $(this).val("enable") : $(this).val("disable");
    });
    $("#codec2").change(function () {
        changecodec($(this).val(), 2)
    });
    $("#enable3").change(function () {
        $(this).is(":checked") ? $(this).val("enable") : $(this).val("disable");
    });
    $("#codec3").change(function () {
        changecodec($(this).val(), 3)
    });
    $("#reset").click(function () {
        page_init();
    });

}
//document ready
$(function () {
    initial_language();
    initial_events();
    audioset_init();
});
