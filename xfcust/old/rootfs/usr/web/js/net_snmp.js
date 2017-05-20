/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />


function initial_language() {
    $("#snmp-page-title").text(SP_SNMP_Settings);
    $("#enable_label").text(SP_Enable_SNMP);
    $("#read_text").text(SP_Read_community);
    $("#write_text").text(SP_Write_community);

    $("#btnSave").val(DN_Save);
}

function initial_elements() {
    if_snmpd == 0 ? $("#enable_snmp").removeAttr("checked") : $("#enable_snmp").attr("checked", "checked");
    $("#read_community").val(rocommunity);
    $("#write_community").val(rwcommunity);
}
function initial_events() {
    $("form").submit(function () {
        try {
            if ($("#read_community").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
                alert(SP_Read_community_can_not_be_null);
                $("#read_community").select().focus();
                return false;
            }
            if ($("#write_community").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
                alert(SP_Write_community_can_not_be_null);
                $("#write_community").select().focus();
                return false;
            }
            if ($("#write_community").val() == $("#read_community").val()) {
                alert(SP_Read_community_and_write_community_can_not_be_same);
                $("#write_community").select().focus();
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