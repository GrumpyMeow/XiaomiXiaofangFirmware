/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />

function initial_language() {
    $("#port-settings-page-title").text(PS_Port_Settings);
    $("#http_text").text(PS_Http_port);
    $("#https_text").text(PS_Https_port);
    $("#rtsp_text").text(PS_Rtsp_port);
    $("#listen_text").text(PS_Two_way_audio_port);

    $("#btnSave").val(PS_Save);
}

function initial_elements() {
 
    if (http_port_flag == 0) {
        $("#http_port").val(http_port_str);
    }
    else {
        $("#http_port").val(http_port);
        window.alert(PS_The_http_port_is_used_by_other_application);
        $("#http_port").select().focus();
    }
    if (https_port_flag == 0) {
        $("#SSLPort").val(https_port_str);
    }
    else {
        $("#SSLPort").val(https_port);
        window.alert(PS_The_https_port_is_used_by_other_application);
        $("#SSLPort").select().focus();
    }
    if (rtsp_port_flag == 0) {
        $("#rtsp_port").val(rtsp_port_str);
    }
    else {
        $("#rtsp_port").val(rtsp_port);
        window.alert(PS_The_rtsp_port_is_used_by_other_application);
        $("#rtsp_port").select().focus();
    }
    if (two_way_audio_flag == 0) {
        $("#listen_port").val(two_way_audio_port_str);
    }
    else {
        $("#listen_port").val(two_way_audio_port);
        window.alert(PS_The_two_way_audio_port_is_used_by_other_application);
        $("#listen_port").select().focus();
    }
}
function check_input() {
    var http_port = $("#http_port").val().replace(/(^\s*)|(\s*$)/g, "");
    var https_port = $("#SSLPort").val().replace(/(^\s*)|(\s*$)/g, "");
    var rtsp_port = $("#rtsp_port").val().replace(/(^\s*)|(\s*$)/g, "");
    var two_way_audio_port = $("#listen_port").val().replace(/(^\s*)|(\s*$)/g, "");
    var min_port = 1;
    var max_port = 65535;
    var min_user_port = 1024;
    var http_normal = 80;
    var https_normal = 443;
    var rtsp_normal = 554;

    /* Port can not be null */

    if (isNaN(http_port) || http_port < min_port || http_port > max_port) {
        alert(PS_The_http_port_must_be_between_1_and_65535);
        $("#http_port").select().focus();
        return false;
    }

    if (isNaN(https_port) || https_port < min_port || https_port > max_port) {
        alert(PS_The_https_port_must_be_between_1_and_65535);
        $("#SSLPort").select().focus();
        return false;
    }

    if (isNaN(rtsp_port) || rtsp_port < min_port || rtsp_port > max_port) {
        alert(PS_The_rtsp_port_must_be_between_1_and_65535);
        $("#rtsp_port").select().focus();
        return false;
    }

    if (isNaN(two_way_audio_port) || two_way_audio_port < min_port || two_way_audio_port > max_port) {
        alert(PS_The_two_way_audio_port_must_be_between_1_and_65535);
        $("#listen_port").select().focus();
        return false;
    }

    /* Port can not be equal */
    if ((http_port == https_port) || (http_port == rtsp_port) || (http_port == two_way_audio_port)
		|| (https_port == rtsp_port) || (https_port == two_way_audio_port) || (rtsp_port == two_way_audio_port)) {
        alert(PS_The_port_can_not_be_equal);
        return false;
    }
    else if (http_port != http_normal && http_port < min_user_port) {
        if (!confirm(PS_The_port_warning_too_small)) {
            $("#http_port").select().focus();
            return false;
        }
    }
    else if (https_port != https_normal && https_port < min_user_port) {
        if (!confirm(PS_The_port_warning_too_small)) {
            $("#SSLPort").select().focus();
            return false;
        }
    }
    else if (rtsp_port != rtsp_normal && rtsp_port < min_user_port) {
        if (!confirm(PS_The_port_warning_too_small)) {
            $("#rtsp_port").select().focus();
            return false;
        }
    }
    else if (two_way_audio_port < min_user_port) {
        if (!confirm(PS_The_port_warning_too_small)) {
            $("#listen_port").select().focus();
            return false;
        }
    }
    return true;
}
function initial_events() {
    $("#btnSave").click(function () {
        var refresh_delay = 6000; //6s
        if (!check_input())
            return;
        if ($("#http_port").val().replace(/(^\s*)|(\s*$)/g, "") == http_port_str
        && $("#SSLPort").val().replace(/(^\s*)|(\s*$)/g, "") == https_port_str) {
            $("form").submit();
            return;
        }
        if (window.location.protocol == "http:") {
            if ($("#http_port").val().replace(/(^\s*)|(\s*$)/g, "") == http_port_str)
                setTimeout("window.location.port = " + $("#http_port").val().replace(/(^\s*)|(\s*$)/g, ""), refresh_delay);
            else
                setTimeout("window.parent.location.port = " + $("#http_port").val().replace(/(^\s*)|(\s*$)/g, ""), refresh_delay);
        }
        else {
            if ($("#SSLPort").val().replace(/(^\s*)|(\s*$)/g, "") == https_port_str)
                setTimeout("window.location.port = " + $("#SSLPort").val().replace(/(^\s*)|(\s*$)/g, ""), refresh_delay);
            else
                setTimeout("window.parent.location.port = " + $("#SSLPort").val().replace(/(^\s*)|(\s*$)/g, ""), refresh_delay);
        }
        $.get(window.location.href.replace(/\?.*$/, ""),
            { "http_port": $("#http_port").val().replace(/(^\s*)|(\s*$)/g, ""),
                "SSLPort": $("#SSLPort").val().replace(/(^\s*)|(\s*$)/g, ""),
                "rtsp_port": $("#rtsp_port").val().replace(/(^\s*)|(\s*$)/g, ""),
                "listen_port": $("#listen_port").val().replace(/(^\s*)|(\s*$)/g, ""),
                "action": "Activate",
                "t": new Date().getTime()
            });
    });
    
}
$(function () {
    initial_language();
    initial_elements();
    initial_events();
});