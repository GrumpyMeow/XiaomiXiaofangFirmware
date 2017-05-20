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

        var form = document.smtp_form;
        var mail_server = form.MailServer.value;
        var mail_server_port = form.MailServerPort.value;
        var mail_user = form.MailUser.value;
        var mail_password = form.MailPassword.value;
        var mail_sender = form.MailSender.value;
        var test_mail_addr = form.test_mail_addr.value;

        if (mail_server == "") {
            window.alert(SMTP_Please_input_mail_server);
            form.MailServer.focus();
            return false;
        }

        if (mail_server_port == "") {
            window.alert(SMTP_Please_input_mail_server_port);
            form.MailServer.focus();
            return false;
        }

        if (mail_sender == "") {
            window.alert(SMTP_Please_input_mail_sender);
            form.MailSender.focus();
            return false;
        }

        if (test_mail_addr == "") {
            window.alert(SMTP_Please_input_test_mail_address);
            form.test_mail_addr.focus();
            return false;
        }

        URL = "http://" + ip_addr + "/cgi-bin/smtp_settings.cgi?action=smtp_test" + "&date=" + date +
		"&ip_addr=" + ip_addr + "&MailServer=" + mail_server + "&MailServerPort=" + mail_server_port +
		"&MailUser=" + mail_user + "&MailPassword=" + mail_password +
		"&MailSender=" + mail_sender + "&test_mail_addr=" + test_mail_addr;

        document.getElementById("test_hiddenframe").src = URL;	
    });
}

function initial_elements() {
    $("#MailServer").val(MailServer);
    $("#MailServerPort").val(MailServerPort);
    $("#MailPassword").val(MailPassword);
    $("#MailSender").val(MailSender);
    $("#MailRecipients").val(MailRecipients);
    $("#MailSubject").val(MailSubject);
    $("#MailContent").val(MailContent);
}
function initial_language() {
    $("#smtp-settings-page-title").text(SMTP_email_Settings);
    $("#smtp-settings_text").text(SMTP_Settings);
    $("#MailServer_text").text(SMTP_Mail_server);
    $("#MailServerPort_text").text(SMTP_Server_port);
    $("#MailUser_text").text(SMTP_User_name);
    $("#MailPassword_text").text(SMTP_Password);
    $("#MailSender_text").text(SMTP_Mail_sender);
    $("#MailRecipients_text").text(SMTP_Mail_recipients);
    $("#MailSubject_text").text(SMTP_Mail_subject);
    $("#MailContent_text").text(SMTP_Mail_content);
    $("#smtp_test_text").text(SMTP_Test);
    $("#smtp_test_to_text").text(SMTP_Send_test_mail_to);

    $("#test_btn").val(SMTP_Send);
    $("#btnSave").val(SMTP_Save);
}

$(function () {
    initial_language();
    initial_elements();
    initial_event();
});
