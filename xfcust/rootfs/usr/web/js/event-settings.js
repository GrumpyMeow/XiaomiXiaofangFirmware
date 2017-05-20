/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />


function initial_language() {
    $("#event-settings-page-title").text(ES_Event_Settings);
    $("#EventEnabled_label").text(ES_Event_enabled);
    $("#Triggered_by_text").text(ES_Triggered_by);
    $("#MotionDetection_label").text(ES_Motion_Detection);
    $("#When_Triggered_text").text(ES_When_Triggered);
    $("#UploadVideoImage_label").text(ES_Upload_video_image);
    $("#osd_detection_text").text(ES_OSD_display_for_Motion_Detection);
    $("#MotionOsdEnabled_label").text(ES_Show);
    $("#osd_recording_text").text(ES_OSD_display_for_Recording);
    $("#RecordOsdEnabled_label").text(ES_Show);

    $("#mp_left_top").text(ES_LeftTop);
    $("#mp_left_bottom").text(ES_LeftBottom);
    $("#mp_right_top").text(ES_RightTop);
    $("#mp_right_bottom").text(ES_RightBottom);
    $("#mp_center").text(ES_Center);

    $("#rp_left_top").text(ES_LeftTop);
    $("#rp_left_bottom").text(ES_LeftBottom);
    $("#rp_right_top").text(ES_RightTop);
    $("#rp_right_bottom").text(ES_RightBottom);
    $("#rp_center").text(ES_Center);

    $("#select_upload_type_text").text(ES_Select_upload_type);
    $("#ftp").text(ES_FTP);
    $("#email").text(ES_Email);
    $("#samba").text(ES_Samba);
    $("#sdcard").text(ES_SDCard);

    $("#select_media_tpye_text").text(ES_Select_video_image);
    $("#stream1video").text(ES_stream_1_video);
    $("#stream2video").text(ES_stream_2_video);
    $("#stream3video").text(ES_stream_3_video);
    $("#snapshot").text(ES_snapshot);

    $("#PreTriggerEnabled_text").text(ES_Include_pre_trigger_buffer);
    $("#PreTriggerEnabled_secends_text").text(ES_seconds);

    $("#base_file_name_text").text(ES_Base_file_name);

    $("#note_text").text(ES_Note);
    $("#note_message_text").text(ES_Note_message);

    $("#save_btn").val(ES_Save);
    if (UploadType == "FTP") {
        // "FTP server settings...";
        $("#ut_settings").val(ES_FTP_server_settings);
    }
    else if (UploadType == "Email") {
        // "SMTP server settings...";
        $("#ut_settings").val(ES_SMTP_server_settings);
    }
    else if (UploadType == "Samba") {
        // "Samba server settings...";
        $("#ut_settings").val(ES_Samba_server_settings);
    }
    else if (UploadType == "SDCard") {
        $("#ut_settings").hide();
    }
}

function initial_elements() {
    sdcard_support ? sdcard_support : $("#sdcard").remove();
    stream1_flag ? stream1_flag : $("#stream1video").remove();
    stream2_flag ? stream2_flag : ($("#stream2video").remove(), UploadFormat == "stream2video" ? UploadFormat = "stream1video" : stream2_flag);
    stream3_flag ? stream3_flag : ($("#stream3video").remove(), UploadFormat == "stream3video" ? UploadFormat = "stream1video" : stream3_flag);
    //TODO
    document.oncontextmenu = function () { };
    EventEnabled ? $("#EventEnabled").val("enable").prop("checked", true) : $("#EventEnabled").val("disable").prop("checked", false);
    MotionDetection ? $("#MotionDetection").val("enable").prop("checked", true) : $("#MotionDetection").val("disable").prop("checked", false);
    UploadVideoImage ? $("#UploadVideoImage").val("enable").prop("checked", true) : $("#UploadVideoImage").val("disable").prop("checked", false);
    $("#UploadType").val(UploadType);
    $("#UploadFormat").val(UploadFormat);
    PreTriggerEnabled ? $("#PreTriggerEnabled").val("enable").prop("checked", true) : $("#PreTriggerEnabled").val("disable").prop("checked", false);
    //TODO add option
    for (var i = 1; i <= PreTriggerSeconds; i++) {
        $("#PreTriggerSeconds").append("<option value='" + i + "'>" + i + "</option>");
    }
    $("#PreTriggerSeconds").val(include_pre_seconds);
    $("#BaseFilename").val(BaseFilename);
    MotionOsdEnabled ? $("#MotionOsdEnabled").val("enable").prop("checked", true) : $("#MotionOsdEnabled").val("disable").prop("checked", false);
    //$("#MotionOsdPicture").attr("src", "/" + MotionOsdPicture);
    $("#MotionOsdPosition").val(MotionOsdPosition);
    RecordOsdEnabled ? $("#RecordOsdEnabled").val("enable").prop("checked", true) : $("#RecordOsdEnabled").val("disable").prop("checked", false);
    //$("#RecordOsdPicture").attr("src", "/" + RecordOsdPicture);
    $("#RecordOsdPosition").val(RecordOsdPosition);
    error_number != 0 ? alert("ERROR : " + error_number) : "";
    
    UploadVideoImage ? $(".upload").show() : $(".upload").hide();
    UploadVideoImage && (UploadFormat != "snapshot") ? $(".upload_video").show() : $(".upload_video").hide();

}
function initial_events() {
    $("form").submit(function () {


    });
    $("#UploadVideoImage").click(function () {
        if ($(this).prop("checked")) {
            $(".upload").show();
            $("#UploadFormat").val() != "snapshot" ? $(".upload_video").show() : $(".upload_video").hide();
        }
        else {
            $(".upload").hide();
        }
    });

    $("#UploadFormat").change(function () {
        $(this).val() != "snapshot" ? $(".upload_video").show() : $(".upload_video").hide();
    });

    $("#UploadType").change(function () {
        if ($(this).val() == "FTP") {
            // "FTP server settings...";
            $("#ut_settings").show().val(ES_FTP_server_settings);
        }
        else if ($(this).val() == "Email") {
            // "SMTP server settings...";
            $("#ut_settings").show().val(ES_SMTP_server_settings);
        }
        else if ($(this).val() == "Samba") {
            // "Samba server settings...";
            $("#ut_settings").show().val(ES_Samba_server_settings);
        }
        else if ($(this).val() == "SDCard") {
            $("#ut_settings").hide();
        }
    });

    $("#ut_settings").click(function () {
        var URL = "";
        if ($(this).val() == ES_FTP_server_settings) {
            URL = "/cgi-bin/ftp_settings.cgi?date=" + new Date().getTime();
            //URL = "ftp_settings.htm?date=" + new Date().getTime();
            window.open(URL, "newwindow", "width=600, height=300, left=180, top=100, status=yes");
        }
        else if ($(this).val() == ES_SMTP_server_settings) {
            URL = "/cgi-bin/smtp_settings.cgi?date=" + new Date().getTime();
            //URL = "smtp_settings.htm?date=" + new Date().getTime();
            window.open(URL, "newwindow", "width=600, height=450, left=180, top=100, status=yes");
        }
        else if ($(this).val() == ES_Samba_server_settings) {
            URL = "/cgi-bin/samba_settings.cgi?date=" + new Date().getTime();
            //URL = "samba_settings.htm?date=" + new Date().getTime();
            window.open(URL, "newwindow", "width=600, height=350, left=180, top=100, status=yes");
        }
    });

    $("#save_btn").click(function () {
        var ipaddr = window.location.host;
        var URL;
        var str, arr;
        var date = new Date().getMilliseconds();
        var if_sd = sdcard_support ? 1 : 0;
        var event_enabled;
        if (document.getElementById("EventEnabled").checked) {
            //if(!document.getElementById("MotionDetection").checked)
            //{
            //	alert("You must select a trigger in the \"Trigger by...\" \nif you want to enable the event.");
            //	return false;
            //}
            event_enabled = 1;
        }
        else {
            event_enabled = 0;
        }

        var motion_detection;
        if (document.getElementById("MotionDetection").checked) {
            motion_detection = 1;
        }
        else {
            motion_detection = 0;
        }


        var upload_video_image;
        if (document.getElementById("UploadVideoImage").checked) {
            upload_video_image = 1;
        }
        else {
            upload_video_image = 0;
        }

        var upload_type = document.getElementById("UploadType").value;
        var upload_format = document.getElementById("UploadFormat").value;
        var pre_trigger_enabled;
        if (document.getElementById("PreTriggerEnabled").checked) {
            pre_trigger_enabled = 1;
        }
        else {
            pre_trigger_enabled = 0;
        }

        var pre_trigger_seconds = document.getElementById("PreTriggerSeconds").value;
        var base_file_name = document.getElementById("BaseFilename").value;

        var motion_osd_enabled;
        if (document.getElementById("MotionOsdEnabled").checked) {
            motion_osd_enabled = 1;
        }
        else {
            motion_osd_enabled = 0;
        }
        str = document.getElementById("MotionOsdPicture").src;
        arr = str.split('/');
        var motion_osd_picture = arr[arr.length - 1];
        var motion_osd_position = document.getElementById("MotionOsdPosition").value;

        if (if_sd == 1) {
            var record_osd_enabled;
            if (document.getElementById("RecordOsdEnabled").checked) {
                record_osd_enabled = 1;
            }
            else {
                record_osd_enabled = 0;
            }
            str = document.getElementById("RecordOsdPicture").src;
            arr = str.split('/');
            var record_osd_picture = arr[arr.length - 1];
            var record_osd_position = document.getElementById("RecordOsdPosition").value;

            URL = "http://" + ipaddr + "/cgi-bin/event_settings.cgi?action=event_save" + "&date=" + date +
			 "&EventEnabled=" + event_enabled + "&MotionDetection=" + motion_detection +
			 "&UploadVideoImage=" + upload_video_image + "&UploadType=" + upload_type +
			 "&UploadFormat=" + upload_format + "&PreTriggerEnabled=" + pre_trigger_enabled +
			 "&PreTriggerSeconds=" + pre_trigger_seconds + "&BaseFilename=" + base_file_name +
			 "&MotionOsdEnabled=" + motion_osd_enabled + "&MotionOsdPicture=" + motion_osd_picture +
			 "&MotionOsdPosition=" + motion_osd_position + "&RecordOsdEnabled=" + record_osd_enabled +
			 "&RecordOsdPicture=" + record_osd_picture + "&RecordOsdPosition=" + record_osd_position;
        }
        else {
            URL = "http://" + ipaddr + "/cgi-bin/event_settings.cgi?action=event_save" + "&date=" + date +
			 "&EventEnabled=" + event_enabled + "&MotionDetection=" + motion_detection +
			 "&UploadVideoImage=" + upload_video_image + "&UploadType=" + upload_type +
			 "&UploadFormat=" + upload_format + "&PreTriggerEnabled=" + pre_trigger_enabled +
			 "&PreTriggerSeconds=" + pre_trigger_seconds + "&BaseFilename=" + base_file_name +
			 "&MotionOsdEnabled=" + motion_osd_enabled + "&MotionOsdPicture=" + motion_osd_picture +
			 "&MotionOsdPosition=" + motion_osd_position;
        }
        if (document.getElementById("MotionOsdEnabled").checked && document.getElementById("RecordOsdEnabled").checked) {
            if (!confirm(ES_OSD_show_warning)) {
                return;
            }
        }
        document.getElementById("event_hiddenframe").src = URL;
    });
}
$(function () {
    initial_language();
    initial_elements();
    initial_events();
});