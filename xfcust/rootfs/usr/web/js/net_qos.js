/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />


function initial_language() {
    $("#qos-page-title").text(QS_QoS_Settings);
    $("#liveview_text").text(QS_Live_View_DSCP);
    $("#http_text").text(QS_HTTP_DSCP);
    $("#ftp_text").text(QS_FTP_DSCP);

    $("#btnSave").val(QS_Save);
}

function initial_elements() {
    $("#liveview_dscp").val(liveview_dscp);
    $("#http_dscp").val(http_dscp);
    $("#ftp_dscp").val(ftp_dscp);
}
function initial_events() {
    $("form").submit(function () {
        if ($("#liveview_dscp").val().replace(/(^\s*)|(\s*$)/g, "") == "" || parseInt($("#liveview_dscp").val()) < 0 || parseInt($("#liveview_dscp").val()) > 63) {
            alert(QS_The_DSCP_value_must_be_between_0_and_63);
            $("#liveview_dscp").focus().select();
            return false;
        }
        else if ($("#http_dscp").val().replace(/(^\s*)|(\s*$)/g, "") == "" || parseInt($("#http_dscp").val()) < 0 || parseInt($("#http_dscp").val()) > 63) {
            alert(QS_The_DSCP_value_must_be_between_0_and_63);
            $("#http_dscp").focus().select();
            return false;
        }
        else if ($("#ftp_dscp").val().replace(/(^\s*)|(\s*$)/g, "") == "" || parseInt($("#ftp_dscp").val()) < 0 || parseInt($("#ftp_dscp").val()) > 63) {
            alert(QS_The_DSCP_value_must_be_between_0_and_63);
            $("#ftp_dscp").focus().select();
            return false;
        }

    });
}
$(function () {
    initial_language();
    initial_elements();
    initial_events();
});