/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />


function initial_language() {
    $("#bonjour-page-title").text(BJ_Bonjour_Settings);
    $("#enable_label").text(BJ_Enable_Bonjour);
    $("#friendlyname_text").text(BJ_Friendly_name);

    $("#btnSave").val(BJ_Save);
}

function initial_elements() {
    if_bonjour == 0 ? $("#enable_bonjour").removeAttr("checked") : $("#enable_bonjour").attr("checked", "checked");
    $("#friendlyname").val(friendlyname);
}
function initial_events() {
    $("form").submit(function () {
        try {
            if ($("#friendlyname").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
                $("#friendlyname").select().focus();
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