/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />


function initial_language() {
    $("#upnp-page-title").text(UP_UPnP_Settings);
    $("#enable_upnp_text").text(UP_UPnP_Switch);
    $("#friendlyname_text").text(UP_Friendly_Name);
    $("#control_upnpc_text").text(UP_External_Network_Access);
    $("#ipaddress_text").text(UP_Router_IP);
    $("#upnp_enable").text(UP_Enable);
    $("#upnp_disable").text(UP_Disable);
    $("#upnpc_yes").text(UP_Yes);
    $("#upnpc_no").text(UP_No);

    $("#btnSave").val(UP_Save);
}

function initial_elements() {
    $("#enable_upnp").val(if_upnpd == 1 ? "yes" : "no");
    $("#friendlyname").val(friendlyname);
    $("#control_upnpc").val(upnpc_switch == 1 ? "yes" : "no");
    $("#ipaddress").val(ipaddress);
}
function initial_events() {
    $("form").submit(function () {
        if ($("#friendlyname").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
            $("#friendlyname").select().focus();
            return false;
        }
    });
}
$(function () {
    initial_language();
    initial_elements();
    initial_events();
});