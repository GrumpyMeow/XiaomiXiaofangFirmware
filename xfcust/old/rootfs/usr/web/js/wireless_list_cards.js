/*common function ,I will move it later*/
function setCookie(c_name, value, expiredays) {
    var exdate = new Date();
    exdate.setDate(exdate.getDate() + expiredays);
    document.cookie = c_name + '=' + escape(value) + ((expiredays == null) ? '' : ';expires=' + exdate.toGMTString());
}
function getCookie(c_name) {
    if (document.cookie.length > 0) {
        c_start = document.cookie.indexOf(c_name + '=');
        if (c_start != -1) {
            c_start = c_start + c_name.length + 1;
            c_end = document.cookie.indexOf(';', c_start);
            if (c_end == -1)
                c_end = document.cookie.length;
            return unescape(document.cookie.substring(c_start, c_end));
        }
    }
    return '';
}
/*common function ,I will move it later*/
var wireless_url = '/cgi-bin/wireless.cgi?op=wireless&action=kill_process';
function radio_change(r, isConnect) {
    var t = isConnect;
    var cardname = document.getElementById('cardname');
    cardname.value = r.value;
    if (t == 'yes') {
        document.getElementById('disable').value = WL_disable;
        document.getElementById('disable').action = 'disable';
        return;
    }
    else {
        document.getElementById('disable').value = WL_enable;
        document.getElementById('disable').action = 'Enable';
        return;
    }
}
function trigger_time() {
    self.location = wireless_url;
}


function initial_language() {
    $("#header").text(WL_title1);
    $("#info").text(WL_list1);
    $(".cards_text").text(WL_cards);
    $(".status_text").text(WL_status);
    $(".ip_text").text(WL_IP);
    $(".ssid_text").text(WL_ssid);
    $(".select_text").text(WL_select);
}
function initial_events() {
    $("#disable").click(function () {
        if ($(this).val() == WL_enable)
            $(this).attr("action", 'Enable');
        else
            $(this).attr("action", 'disable');
        $("#action").val($(this).attr("action"));
        $("#submit").prop("disabled", false);
        if ($(this).attr("action") == 'Enable') {
            wireless_url += '&select_card=' + getCookie('select_device');
            setTimeout(trigger_time, 90000);
        }
        $("#submit").trigger("click");
        $("#submit").attr("disabled", "disabled");
        $(this).attr("disabled", 'true');
    });
    $(window).resize(function () {
        var $ssid = $("#info").next();
        for (var i = 0; i < wireless_card_list.length + 1; i++) {
            var max_height = 0;
            var $head = $ssid;
            for (var ii = 0; ii < 5; ii++) {
                (i % 2 == 1 ? $ssid.css("background-color", "#ececec") : $ssid).removeClass("min_padding").addClass("min_padding")
                parseInt($ssid.css("height")) > max_height ? max_height = parseInt($ssid.css("height")) : "";
                $ssid = $ssid.next();
            }
            var $ssid = $head;
            for (var ii = 0; ii < 5; ii++) {
                $ssid.css("height", max_height + "px");
                $ssid = $ssid.next();
            }
        }
    })
    .resize();
}
function initial_elements() {
    for (i = 0; i < wireless_card_list.length; i++) {
        if (wireless_card_list[i].isConnect == "yes")
            $("#end_first_line").after("<div class=\"col-xs-2 col-sm-2 col-md-2\">" + wireless_card_list[i].card_name +
            "</div><div class=\"col-xs-2 col-sm-2 col-md-2\">" + WL_status_connect + "</div><div class=\"col-xs-3 col-sm-3 col-md-3\">" + wireless_card_list[i].IP +
            "</div><div class=\"col-xs-3 col-sm-3 col-md-3\">" + wireless_card_list[i].ssid + "</div><div class=\"col-xs-2 col-sm-2 col-md-2\"><input type='radio' name='select_cards' id='" +
            wireless_card_list[i].card_name + "' value='" + wireless_card_list[i].card_name + "' onclick=\"radio_change(this, 'yes');setCookie('select_device',this.value,1);\" mymark='yes'>" + "</div>");
        else
            $("#end_first_line").after("<div class=\"col-xs-2 col-sm-2 col-md-2\">" + wireless_card_list[i].card_name +
            "</div><div class=\"col-xs-2 col-sm-2 col-md-2\">" + WL_status_disconnect + "</div><div class=\"col-xs-3 col-sm-3 col-md-3\">" + WL_null +
            "</div><div class=\"col-xs-3 col-sm-3 col-md-3\">" + WL_null + "</div><div class=\"col-xs-2 col-sm-2 col-md-2\"><input type='radio' name='select_cards' id='" +
            wireless_card_list[i].card_name + "' value='" + wireless_card_list[i].card_name + "' onclick=\"radio_change(this, 'no');setCookie('select_device',this.value,1);\" mymark='no'></div>");
        var $cur = $("#end_first_line").next();
        for (var ii = 0; ii < 5; ii++) {
            $cur.addClass("no_nl");
            parseInt($(window).width()) <= 1024 ? $cur.css("font-size", "90%") : "";
            $cur = $cur.next();
        }
    }
    document.getElementById('submit').value = WL_setwifi;
    var t = getCookie('select_device');
    if (t && document.getElementById(t)) {
        document.getElementById(t).click();
    }
    else {
        document.getElementById(wireless_card_list[0].card_name).click();
    }
    wireless_url += '&processes=udhcpc%2Bwpa_supplicant';
}
//document ready
$(function () {
    initial_elements();
    initial_language();
    initial_events();
});