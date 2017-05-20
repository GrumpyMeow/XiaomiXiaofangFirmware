/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />
/// <reference path="common.js" />
String.prototype.trim = function () {
    return this.replace(/(^\s*)|(\s*$)/g, "");
}
String.prototype.format = function () {
    var args = arguments;
    return this.replace(/\{(\d+)\}/g,
        function (m, i) {
            return args[i];
        });
}
function isDate(dateString) {
    var date_err_info_str = Date_err_info.format(Date_man_data, get_date(), Date_man_time, get_time());
    var dtstring = dateString.trim();
    if (dtstring == "") {
        alert(date_err_info_str);
        return false;
    }
    var r = dtstring.match(/^(\d{1,4})\-(\d{1,2})\-(\d{1,2}) (\d{1,2}):(\d{1,2}):(\d{1,2})$/);
    if (r == null) {
        alert(date_err_info_str);
        return false;
    }
    var d = new Date(r[1], r[2] - 1, r[3], r[4], r[5], r[6]);
    var num = (d.getFullYear() == r[1] && (d.getMonth() + 1) == r[2] && d.getDate() == r[3] && d.getHours() == r[4] && d.getMinutes() == r[5] && d.getSeconds() == r[6]);
    if (num == 0) {
        alert(date_err_info_str);
    }
    if (d.getTime() < Date.parse("1/1/2000 0:0:0")) {
        alert(Date_range_err);
        num = 0;
    }
    if (d.getTime() > Date.parse("1/1/2037 0:0:0")) {
        alert(Date_range_err);
        num = 0;
    }
    return (num != 0);
}

function isDateTime() {
    var date_test = $("#manually_date").val();
    var time_test = $("#manually_time").val();
    var dtstring = date_test.trim() + " " + time_test.trim();
    return isDate(dtstring);
}

function get_date() {
    var t = new Date();
    var ret;
    var month = 1 + t.getMonth();
    ret = t.getFullYear() + "-" + month + "-" + t.getDate();
    return ret;
}

function get_time() {
    var t = new Date();
    var ret;
    ret = t.getHours() + ":" + t.getMinutes() + ":" + t.getSeconds();
    return ret;
}

function get_datetime() {
    return get_date() + " " + get_time();
}
function get_dateByseconds(seconds) {
    var t = new Date();
    var ret;
    t.setTime(seconds * 1000);
    var month = 1 + t.getMonth();
    ret = t.getFullYear() + "-" + month + "-" + t.getDate();
    return ret;

}
function get_timeByseconds(seconds) {
    var t = new Date();
    var ret;
    t.setTime(seconds * 1000);
    ret = t.getHours() + ":" + t.getMinutes() + ":" + t.getSeconds();
    return ret;
}
function get_datetimeByseconds(seconds) {
    return get_dateByseconds(seconds) + " " + get_timeByseconds(seconds);
}
function trigger_1s() {
    var time = get_datetime();
    $("#computer_time").val(time);
    $("#computer_time_show").val(time);
    $("#current_time_value").text(get_datetimeByseconds(time_seconds));
    time_seconds++;
}
function date_time_init() {
    var time = get_datetime();
    $("#computer_time").val(time);
    $("#computer_time_show").val(time);
    $("#manually_date").val(get_dateByseconds(time_seconds));
    $("#manually_time").val(get_timeByseconds(time_seconds));
    $("#time_zones").selectedIndex = re_time_mode_select;
    $("#ntp_server").val($("#re_ntp").val());
    $("#time_zones").change();
}

function initial_events() {

    $("#daylight").click(function () {
        $(this).is(":checked") ? $(this).val("on") : $(this).val("off");
    });

    $("#set_time_zone_btn").click(function () {
        $("[name=action]").val("savetz");
    });

    $(":radio").click(function () {
        $("#action").val($(this).val());
    });

    $("#save_btn").click(function () {
        if ($("#manually_radio").attr("checked") && !isDateTime()) return false;
    });

    $("#reset_btn").click(function () {
        date_time_init();
    });

    $("#time_zones").change(function () {
        var param = {
            r: new Date().getTime(),
            action: "gettime",
            time_zone: $(this).val().replace(/\_.*/, "")
        };
        $.get("/cgi-bin/sys_time.cgi", param, function (data, status) {
            if (status == "success") {
                time_seconds = new Date(data).getTime() / 1000;
                $("#current_time_zone_value").text($("#time_zones option:selected").text());
                trigger_1s();
            }
        });
    });
    $("#set_time_zone_btn").click(function () {
        $("[name=action]").val("savetz");
    });

    setInterval('trigger_1s()', 1000);
}
function initial_elements() {
    if (daylight_switch == "on")
        $("#daylight").attr("checked", "checked");
    $.each(timezone_array, function (i, val) {
        $("#time_zones").append("<option value=\"" + val[0] + "\">" + val[1] + "</option>");
    });
    $("#time_zones").val(timezone_array[re_time_mode_select][0]);
}
function initial_language() {

    $("#time-page-title").text(Date_title + " : ");
    $("#time_zone_title").text(Date_time_zone + " : ");
    $("#current_time_zone_title").text(Date_current_time_zone + " : ");
    $("#current_time_zone_value").text(time_zone_current);
    $("#current_time_title").text(Date_current_time + " : ");
    $("#current_time_value").text(current_time);
    $("#daylight_text").text(Date_daylight);
    $("#set_time_zone_btn").val(Date_set_time_zone_btn);
    $("#manually_text").text(Date_man_txt);
    $("#manually_date_text").text(Date_man_data + " : ");
    $("#manually_time_text").text(Date_man_time + " : ");
    $("#computer_text").text(Date_pc_txt);
    $("#computer_time_text").text(Date_pc_time + " : ");
    $("#ntp_text").text(Date_ntp_txt);
    $("#ntp_server_text").text(Date_ntp_ip + " : ");
    $("#save_btn").val(Date_ok_btn);
    $("#reset_btn").val(Date_reset_btn);
}
function initial_others() {
    date_time_init();
}

//document ready
$(function () {
    initial_elements();
    initial_language();
    initial_events();
    initial_others();
});
