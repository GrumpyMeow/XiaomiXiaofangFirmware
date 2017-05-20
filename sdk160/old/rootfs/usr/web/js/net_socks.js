/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />

function initial_language() {
    $("#socks-page-title").text(SK_SOCKS_Settings);
    $("#server_text").text(SK_Server);
    $("#server_port_text").text(SK_Server_port);
    $("#server_type_text").text(SK_Server_type);
    $("#local_text").text(SK_Local_networks);
    $("#local_note_text").text(SK_note_message);
    $("#btnSave").val(SK_Save);
}

function initial_elements() {
    $("#server").val(server);
    $("#server_port").val(server_port);
    $("#server_type").val(server_type);
    $("#local").val(local);

    $("#server_type").css("width", $("#server").css("width"));
    $("#server_port").css("width", $("#server").css("width"));
    $("#local").css("width", parseInt( $("#server").css("width")) * 1.5 + "px");
}
function initial_events() {
    $("form").submit(function () {
        if ($("#server").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
            $("#server").focus().select();
            return false;
        }
        else if ($("#server_port").val().replace(/(^\s*)|(\s*$)/g, "") == "" || parseInt($("#server_port").val()) < 1 || parseInt($("#server_port").val()) > 65535) {
            $("#server_port").focus().select();
            return false;
        }
        else if ($("#local").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
            $("#local").focus().select();
            return false;
        }
    });
}
$(function () {
    initial_language();
    initial_elements();
    initial_events();
});