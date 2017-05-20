/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />

var K = 1024;
var null_option = "<option value=''>" + "--select--" + "</option>";
Number.prototype.toFixed = function (len) {
     var temp = Math.pow(10, len);
     var s = Math.ceil(this * temp)
     return s / temp;
}
function initial_language() {
    $("#record-search-page-title").text(RS_Record_Search);
    $("#sd_status_text").text(RS_SD_Card_Status);
    $("#sd_status_text1").text(RS_SD_Card);
    $("#sd_use_text").text(RS_Used_Space);
    $("#sd_free_text").text(RS_Free_Space);
    $("#format_text").text(RS_SD_Card_Format);
    $("#umount_text").text(RS_SD_Card_Umount);
    $("#mount_text").text(RS_SD_Card_Mount);
    $("#search_text").text(RS_SD_Card_Search);
    $("#record").text(RS_record);
    $("#snapshot").text(RS_snapshot);
    $("#filename_text").text(RS_File_name);
    $("#filesize_text").text(RS_Size_KB);
    $("#fileload_text").text(RS_Download);

    $("#format_btn").val(RS_Format);
    $("#umount_btn").val(RS_Umount);
    $("#mount_btn").val(RS_Mount);
    $("#search_btn").val(RS_Search);
}

function initial_elements() {
    $("#sd_status").text(eval(sd_status));
    $("#sd_use").text((sd_used / K).toFixed(2) + " MB, " + sd_used_p + " %");
    $("#sd_free").text((sd_available / K).toFixed(2) + " MB, " + sd_available_p + " %");

    $("#search_date").html("").append(null_option);
    for (var i = 0; i < search_date_array.length; i++) {
        if (search_date_array[i].match(/((^((1[8-9]\d{2})|([2-9]\d{3}))([-\/\._])(10|12|0?[13578])([-\/\._])(3[01]|[12][0-9]|0?[1-9])$)|(^((1[8-9]\d{2})|([2-9]\d{3}))([-\/\._])(11|0?[469])([-\/\._])(30|[12][0-9]|0?[1-9])$)|(^((1[8-9]\d{2})|([2-9]\d{3}))([-\/\._])(0?2)([-\/\._])(2[0-8]|1[0-9]|0?[1-9])$)|(^([2468][048]00)([-\/\._])(0?2)([-\/\._])(29)$)|(^([3579][26]00)([-\/\._])(0?2)([-\/\._])(29)$)|(^([1][89][0][48])([-\/\._])(0?2)([-\/\._])(29)$)|(^([2-9][0-9][0][48])([-\/\._])(0?2)([-\/\._])(29)$)|(^([1][89][2468][048])([-\/\._])(0?2)([-\/\._])(29)$)|(^([2-9][0-9][2468][048])([-\/\._])(0?2)([-\/\._])(29)$)|(^([1][89][13579][26])([-\/\._])(0?2)([-\/\._])(29)$)|(^([2-9][0-9][13579][26])([-\/\._])(0?2)([-\/\._])(29)$))/)) {
            $("#search_date").append("<option value='" + search_date_array[i] + "'>" + search_date_array[i] + "</option>");
        }
    }
    $("#search_hour").html("").append(null_option);
    $("#search_min").html("").append(null_option);
    $("#search_type").html("").append(null_option);

    $("select").prop("disabled", true);
    if (sd_status == "RS_Not_Ready") {
        $("input").prop("disabled", true);
    }
    else if (sd_status == "RS_Umounted") {
        //$("#btn_format").prop("disabled", true);
        $("#umount_btn").prop("disabled", true);
        $("#search_btn").prop("disabled", true);
    }
    else {
        $("#mount_btn").prop("disabled", true);
        $("select").prop("disabled", false);
    }
    warning_var != "" ? eval(warning_var) : "";
    for (var i = 0; i < search_files.length; i++) {
        $("#fileload_text").after(
        "<div class=\"col-xs-6 col-sm-6 col-md-6 download\">" + search_files[search_files.length - 1 - i][0] + "</div>" +
        "<div class=\"col-xs-3 col-sm-3 col-md-3 download align-center\">" + search_files[search_files.length - 1 - i][1] + "</div>" +
        "<div class=\"col-xs-3 col-sm-3 col-md-3 download align-center\"><img src=\"../images/download.jpg\"  class=\"download_img\" data-download_src=\"" + search_files[search_files.length - 1 - i][2] + "\"/></div>");
    }
    search_files.length == 0 ? $(".download").hide() : "";
    {
        var submit_length = 0;
        $.each($(":submit"), function (index, elem) {
            parseInt($(elem).css("width")) > submit_length ? submit_length = parseInt($(elem).css("width")) : "";
        });
        $(":submit").css("width", submit_length + "px");
    }
    {
        var select_length = 0;
        $.each($("select"), function (index, elem) {
            parseInt($(elem).css("width")) > select_length ? select_length = parseInt($(elem).css("width")) : "";
        });
        $("select").css("width", select_length + "px");
    }
    {
        if (search_type_select == "record") {
            $("#search_min").parent().hide();
            $(".search_line").removeClass("col-xs-3 col-sm-3 col-md-3").addClass("col-xs-4 col-sm-4 col-md-4");
        }
        else {
            $("#search_min").parent().show();
            $(".search_line").removeClass("col-xs-4 col-sm-4 col-md-4").addClass("col-xs-3 col-sm-3 col-md-3");
        }
    }
}
function initial_events() {
    $("#format_btn").parents("form").submit(function () {
        return confirm(RS_Format_message_1);
    });
    $("#umount_btn").parents("form").submit(function () {
        return confirm(RS_Umount_message_1);
    });
    $("#mount_btn").parents("form").submit(function () {
        return confirm(RS_SD_Card_Mount);
    });
    $("#search_btn").parents("form").submit(function () {
        //return confirm(RS_SD_Card_Mount);
    });
    $(".download_img").click(function () {
        $("#filepath").val($(this).data("download_src"));
        $(this).parents("form").submit();
    });

    $.getJSON("/cgi-bin/index.cgi", {
        "record_search": "record_search",
        "t": new Date().getTime()
    }, function (json) {
        $("#search_date").html("").append(null_option);
        $.each(json.search_date, function (index, elem) {
            if (elem.match(/((^((1[8-9]\d{2})|([2-9]\d{3}))([-\/\._])(10|12|0?[13578])([-\/\._])(3[01]|[12][0-9]|0?[1-9])$)|(^((1[8-9]\d{2})|([2-9]\d{3}))([-\/\._])(11|0?[469])([-\/\._])(30|[12][0-9]|0?[1-9])$)|(^((1[8-9]\d{2})|([2-9]\d{3}))([-\/\._])(0?2)([-\/\._])(2[0-8]|1[0-9]|0?[1-9])$)|(^([2468][048]00)([-\/\._])(0?2)([-\/\._])(29)$)|(^([3579][26]00)([-\/\._])(0?2)([-\/\._])(29)$)|(^([1][89][0][48])([-\/\._])(0?2)([-\/\._])(29)$)|(^([2-9][0-9][0][48])([-\/\._])(0?2)([-\/\._])(29)$)|(^([1][89][2468][048])([-\/\._])(0?2)([-\/\._])(29)$)|(^([2-9][0-9][2468][048])([-\/\._])(0?2)([-\/\._])(29)$)|(^([1][89][13579][26])([-\/\._])(0?2)([-\/\._])(29)$)|(^([2-9][0-9][13579][26])([-\/\._])(0?2)([-\/\._])(29)$))/)) {
                $("#search_date").append("<option value='" + elem + "'>" + elem + "</option>");
            }
        });

        $("#search_date").val($("#search_date option").filter("[value=" + search_date_select + "]").length > 0 ? search_date_select : "");
        $("#search_date").change();
    });
    $("#search_date").change(function () {
        if ($(this).val() == null || $(this).val() == "") {
            $("#search_type").html("").append(null_option).change();
            return false;
        }
        $.getJSON("/cgi-bin/index.cgi", {
            "record_search": "record_search",
            "t": new Date().getTime(),
            "search_date": $("#search_date").val()
        }, function (json) {
            $("#search_type").html("").append(null_option);
            $.each(json.search_type, function (index, elem) {
                $("#search_type").append("<option value='" + elem + "'>" + (elem == "record" ? RS_record : RS_snapshot) + "</option>");
            });
            $("#search_type").val($("#search_type option").filter("[value=" + search_type_select + "]").length > 0 ? search_type_select : "");
            $("#search_type").change();
        });
    });


    $("#search_type").change(function () {
        if ($(this).val() == null || $(this).val() == "") {
            $("#search_hour").html("").append(null_option).change();
            return false;
        }
        if ($(this).val() == "record") {
            $("#search_min").parent().hide();
            $(".search_line").removeClass("col-xs-3 col-sm-3 col-md-3").addClass("col-xs-4 col-sm-4 col-md-4");
        }
        else {
            $("#search_min").parent().show();
            $(".search_line").removeClass("col-xs-4 col-sm-4 col-md-4").addClass("col-xs-3 col-sm-3 col-md-3");
        }

        $.getJSON("/cgi-bin/index.cgi", {
            "record_search": "record_search",
            "t": new Date().getTime(),
            "search_date": $("#search_date").val(),
            "search_type": $("#search_type").val()
        }, function (json) {
            $("#search_hour").html("").append(null_option);
            $.each(json.search_hour, function (index, elem) {
                $("#search_hour").append("<option value='" + elem + "'>" + parseInt(elem) + RS_hour + "</option>");
            });
            $("#search_hour").val($("#search_hour option").filter("[value=" + search_hour_select + "]").length > 0 ? search_hour_select : "");
            $("#search_hour").change();
        });
    });
    $("#search_hour").change(function () {
        if ($(this).val() == null || $(this).val() == "" || $("#search_type").val() == "record") {
            $("#search_min").html("").append(null_option);
            return false;
        }
        $.getJSON("/cgi-bin/index.cgi", {
            "record_search": "record_search",
            "t": new Date().getTime(),
            "search_date": $("#search_date").val(),
            "search_type": $("#search_type").val(),
            "search_hour": $("#search_hour").val()
        }, function (json) {
            $("#search_min").html("").append(null_option);
            $.each(json.search_min, function (index, elem) {
                $("#search_min").append("<option value='" + elem + "'>" + elem.replace(/[Mm]/g, "") + RS_min + "</option>");
            });
            $("#search_min").val($("#search_min option").filter("[value=" + search_min_select + "]").length > 0 ? search_min_select : "");
        });
    });
    $("#search_date").change();
}
$(function () {
    initial_language();
    initial_elements();
    initial_events();
});