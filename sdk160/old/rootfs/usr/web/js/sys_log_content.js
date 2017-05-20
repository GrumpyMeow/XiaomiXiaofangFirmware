/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />

function initial_language() {
    $("#sys_log_content-page-title").text(logs[0].match(/messages/) ? Logs_system_btn : Logs_web_btn);
    $("#back_link").text("<<" + Logs_back);
}

function initial_elements() {
    $.each(logs, function (index, elem) {
        if (elem.replace(/(^\s*)|(\s*$)/g, "").length > 0)
            $("#content_end").before("<div class=\"col-xs-12 col-sm-12 col-md-12\">" + elem.replace(/(^\s*)|(\s*$)/g, "") + "</div>\n");
    });
}

function initial_events() {
    $("#back_link").click(function (e) {
        history.back(-1);
        $(this).attr("disabled", "disabled");
		e.preventDefault();
		return false;
    });
}

$(function () {
    initial_language();
    initial_elements();
    initial_events();
});