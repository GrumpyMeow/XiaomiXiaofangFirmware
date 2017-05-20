/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />


function initial_language() {
    $("#ddns-page-title").text(DN_DDNS_Settings);
    $("#enable_label").text(DN_Enable_DDNS);
    $("#username_text").text(DN_User_name);
    $("#pwd_text").text(DN_Password);
    $("#domain_text").text(DN_Domain_name);

    $("#btnSave").val(DN_Save);
}

function initial_elements() {
    if_ddns == 0 ? $("#enable_ddns").removeAttr("checked") : $("#enable_ddns").attr("checked", "checked");
    $("#username").val(username);
    $("#password").val(password);
    $("#domain").val(domain);
}
function initial_events() {
    $("form").submit(function () {
        try {
            if ($("#username").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
                alert(DN_Username_can_not_be_null);
                return false;
            }
            if ($("#password").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
                alert(DN_Password_can_not_be_null);
                return false;
            }
            if ($("#domain").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
                alert(DN_Domain_name_can_not_be_null);
                return false;
            }
        } catch (exception) {
            alert(exception.message);
            return false;
        }
    });
}
$(function () {
    initial_language();
    initial_elements();
    initial_events();
});