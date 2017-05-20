/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />
jQuery.fn.trimVal = function () {
    $(this).val($.trim($(this).val()));
    return $(this).val();
}
function initial_language() {
    document.title = IAF_Add_Page_Title;
    $("#add-ip-page-title").text(IAF_Add_Page_Title);
    $("#general_text").text(IAF_Add_Page_Title);
    $("#ip_addr_text").text(IAF_Add_Page_IP);
    $("#ok_btn").val(IAF_Add_Page_btn_OK);
    $("#cancel_btn").val(IAF_Add_Page_btn_Cancel);
}
function initial_language_ajax() {
    $.getJSON("/cgi-bin/index.cgi",
    {
        "get_language": "get_language",
        "v": (typeof (FIRMWARE_VERSION) != "undefined" ? FIRMWARE_VERSION : new Date().getTime())
    },
     function (json) {
         change_language(json.get_language);
     });
 }
 function initial_elements() {
     $("#ip_addr").focus();
 }
function initial_events() {
    $("form").submit(function () {
        var ip_addresses = window.opener.get_ip_list();
        var ret = true;
        //check ip address regular
        if (!$("#ip_addr").val().replace(/(^\s*)|(\s*$)/g, "").match(/^((?:(?:25[0-5]|2[0-4]\d|((1\d{2})|([1-9]?\d)))\.){3}(?:25[0-5]|2[0-4]\d|((1\d{2})|([1-9]?\d))))$/)) {
            alert(IAF_Add_Page_invalidIP_warning);
            $("#ip_addr").focus().select();
            return false;
        }
        if (ip_addresses.length >= 10) {
            alert(IAF_Add_Page_MaxIP_warning);
            return false;
        }
        $.each(ip_addresses, function (index, elem) {
            if (elem == $("#ip_addr").val().replace(/(^\s*)|(\s*$)/g, "")) {
                alert(elem + IAF_Add_Page_existIP_warning);
                $("#ip_addr").focus().select();
                ret = false;
                return;
            }
        });
        ret ? $("#ip_addr").trimVal() : "";
        return ret;
    });
    $("#cancel_btn").click(function () {
        window.close();
    });
}
$(function () {
    initial_language_ajax();
    initial_elements();
    initial_events();
});