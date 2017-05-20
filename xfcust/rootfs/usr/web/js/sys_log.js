/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />

function initial_language() {
    $("#sys_log-page-title").text(Logs_title);
    $("#logs_small_title").text(Logs_logs);
    $("#sys_log_text").text(Logs_system_txt);
    $("#web_log_text").text(Logs_web_txt);
    $("#sys_log_btn").val(Logs_system_btn);
    $("#web_log_btn").val(Logs_web_btn);
}

function initial_events() {
    $("#sys_log_btn").click(function () {
        window.location.href = "/cgi-bin/sys_log.cgi?action=systemlog" + "&t=" + new Date().getTime();
    });

    $("#web_log_btn").click(function () {
        window.location.href = "/cgi-bin/sys_log.cgi?action=boalog" + "&t=" + new Date().getTime();
    });
}
function initial_elements() {
    {//initial width
        var max_width = 0;
        $.each($(":button"), function (index, elem) {
            max_width = max_width > parseInt($(elem).css("width")) ? max_width : parseInt($(elem).css("width"));
        });
        $(":button").css("width", max_width + "px");
    }
}
$(function () {
    initial_language();
    initial_elements();
    initial_events();
});