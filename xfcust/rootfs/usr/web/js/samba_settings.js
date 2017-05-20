/// <reference path="jquery-1.10.2-vsdoc.js" />
/// <reference path="en-US.js" />


function initial_event() {
    $("#cancel_btn").click(function () {
        window.close();
    });

    $("#ok_btn").click(function () {

    });

    $("#test_btn").click(function () {
        var ip_addr = window.location.host;
        var date = new Date().getMilliseconds();
        var URL;

        var form = document.samba_form;
        var samba_server = form.SambaServer.value;
        var samba_shared_folder = form.SambaSharedFolder.value;
        var samba_user = form.SambaUser.value;
        var samba_password = form.SambaPassword.value;

        if (samba_server == "") {
            window.alert(Samba_Please_input_samba_server);
            form.SambaServer.focus();
            return false;
        }

        if (samba_shared_folder == "") {
            window.alert(Samba_Please_input_samba_shared_folder);
            form.SambaServer.focus();
            return false;
        }

        if (samba_user == "") {
            window.alert(Samba_Please_input_samba_user);
            form.MailSender.focus();
            return false;
        }

        if (samba_password == "") {
            window.alert(Samba_Please_input_samba_password);
            form.test_mail_addr.focus();
            return false;
        }

        URL = "http://" + ip_addr + "/cgi-bin/samba_settings.cgi?action=samba_test" + "&date=" + date +
		"&SambaServer=" + samba_server + "&SambaSharedFolder=" + samba_shared_folder +
		"&SambaUser=" + samba_user + "&SambaPassword=" + samba_password;

        document.getElementById("test_hiddenframe").src = URL;	
    });
    
}

function initial_elements() {
    $("#SambaServer").val(SambaServer);
    $("#SambaSharedFolder").val(SambaSharedFolder);
    $("#SambaUser").val(SambaUser);
    $("#SambaPassword").val(SambaPassword);

}
function initial_language() {
    $("#samba-settings-page-title").text(Samba_Settings);
    $("#samba-settings_text").text(Samba_Settings);
    $("#SambaServer_text").text(Samba_server);
    $("#SambaSharedFolder_text").text(Samba_Shared_folder);
    $("#SambaUser_text").text(Samba_User_name);
    $("#SambaPassword_text").text(Samba_Password);
    $("#samba_test_text").text(Samba_Test);
    $("#samba_test_msg1").text(Samba_test_message_1);
    $("#samba_test_msg2").text(Samba_test_message_2);

    $("#test_btn").val(Samba_Test);
    $("#btnSave").val(Samba_Save);
}

$(function () {
    initial_language();
    initial_elements();
    initial_event();
});
