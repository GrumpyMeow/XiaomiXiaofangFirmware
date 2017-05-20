/*common function ,I will move it later*/
function cconnecting() {
    var check = document.getElementsByName("check");
    var ap = "";

    for (var i = 0; i < check.length; i++) {

        if (check[i].checked == true) {
            ap = check[i].value;
            break;
        }
    }
    if ($("[name='check']:checked").length <= 0) {
        alert(WL_2warning);
        return false;
    }
    location.href = "/cgi-bin/wireless.cgi?op=wireless&action=connect&accesspoint=" + ap;
    return true;
}
/*common function ,I will move it later*/
$(document).ready(function () {
    for (i = 0; i < wireless_scanning_list.length; i++) {
        $("#end_first_line").after("<div id=\"ssid_" + i + "\" class=\"col-xs-3 col-sm-3 col-md-3\">" + wireless_scanning_list[i].essid +
        "</div><div class=\"col-xs-2 col-sm-2 col-md-2\">" + eval(wireless_scanning_list[i].mode) + "</div><div class=\"col-xs-2 col-sm-2 col-md-2\">" +
        wireless_scanning_list[i].quality + "</div><div class=\"col-xs-2 col-sm-2 col-md-2\">" + eval(wireless_scanning_list[i].enc) +
        "</div><div class=\"col-xs-2 col-sm-2 col-md-2\">" + wireless_scanning_list[i].bitrate + "</div><div class=\"col-xs-1 col-sm-1 col-md-1\">" +
        "<input type='radio' name='check' value='" + wireless_scanning_list[i].essid + "'>" + "</div>");
        var $cur = $("#end_first_line").next();
        for (var ii = 0; ii < 6; ii++) {
            $cur.addClass("no_nl");
            $cur = $cur.next();
        }
    }
});

function initial_language() {
    $("#card_info").text(card_info[0] + " " + card_info[1]);
    $("#header").text(WL_2title);
    $("#info").text(WL_2status);
    $(".ssid_text").text(WL_2ssid);
    $(".mode_text").text(WL_2mode);
    $(".quality_text").text(WL_2quality);
    $(".encrypty_text").text(WL_2encryptkey);
    $(".bitrate_text").text(WL_2bitrate);
    $("#connect").val(WL_2connect);
    $("#refresh").val(WL_2refresh);
}
function initial_events() {
    $(window).resize(function () {
        var $ssid = $("#info").next();
        for (var i = 0; i < wireless_scanning_list.length + 1; i++) {
            var max_height = 0;
            var $head = $ssid;
            for (var ii = 0; ii < 6; ii++) {
                (i % 2 == 1 ? $ssid.css("background-color", "#ececec") : $ssid).removeClass("min_padding").addClass("min_padding");
                parseInt($ssid.css("height")) > max_height ? max_height = parseInt($ssid.css("height")) : "";
                $ssid = $ssid.next();
            }
            var $ssid = $head;
            for (var ii = 0; ii < 6; ii++) {
                $ssid.css("height", max_height + "px");
                $ssid = $ssid.next();
            }
        }
    })
    .resize();
    
}
//document ready
$(function () {
    initial_language();
    initial_events();
});

