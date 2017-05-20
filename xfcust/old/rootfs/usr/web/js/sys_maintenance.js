/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />

function initial_language() {

    $("#sys_maintenace-page-title").text(Maintenance_title);

    $("#upgrade_fw_title").text(Maintenance_up_fw);
    $("#update_fw_text").text(Maintenance_up_fw_txt);
    $("#reset_lable").text(Maintenance_up_fw_reset);
    $("#upgrade_btn").val(Maintenance_up_fw_btn);

    $("#reset_factory_title").text(Maintenance_restore_fact)
    $("#reset_factory_text").text(Maintenance_restart_txt);
    $("#reset_factory_btn").val(Maintenance_restore_fact_btn);

    $("#backup_file_title").text(Maintenance_bck_file);
    $("#backup_file_text").text(Maintenance_bck_file_txt);
    $("#backup_file_btn").val(Maintenance_bck_file_btn);

    $("#reset_file_title").text(Maintenance_restore_file);
    $("#reset_file_text").text(Maintenance_restore_file_txt);
    $("#reset_file_btn").val(Maintenance_restore_file_btn);

    $("#reboot_title").text(Maintenance_restart);
    $("#reboot_text").text(Maintenance_restart_txt);
    $("#reboot_btn").val(Maintenance_restart_btn);
}

function initial_events() {

    $("#reset_checkbox").click(function () {
        $("#clear_etc_value").val($(this).is(":checked") ? "true" : "false");
    });

    $("#upgrade_btn").click(function () {
        var ret = false;
        if ($("#upgrade_file").val().replace(/(^\s*)|(\s*$)/g, "").length == 0) {
            alert(Maintenance_no_inputfile);
            ret = false;
        }
        else {
            ret = confirm(Maintenance_up_fw_waring);
        }
        return ret;
    });

    $("#reset_factory_btn").click(function () {
        return confirm(Maintenance_restore_fact_waring);
    });

    $("#backup_file_btn").click(function () {
        return confirm(Maintenance_bck_file_waring);
    });

    $("#reset_file_btn").click(function () {
        var ret = false;
        if ($("#reset_file_file").val().replace(/(^\s*)|(\s*$)/g, "").length == 0) {
            alert(Maintenance_no_inputfile);
            ret = false;
        }
        else {
            ret = confirm(Maintenance_restore_file_waring);
        }
        return ret;
    });

    $("#reboot_btn").click(function () {
        return confirm(Maintenance_restart_waring);
    });
}

$(function () {
    initial_language();
    initial_events();
})