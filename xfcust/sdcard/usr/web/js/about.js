/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />


function initial_language() {
    $("#about_title").text(NV_About);
    $("#IPCam_name").text(About_snx_IP_Camera);
    $("#fw_version_text").text(About_firmware_version);
    $("#mac_address_text").text(About_mac_address);
    $("#copy_right").text(About_copyright);
}

function initial_elements() {
    $("#fw_version").text(fw_version);
    $("#mac_address").text(mac);
}

$(function () {
    initial_language();
    initial_elements();
});
