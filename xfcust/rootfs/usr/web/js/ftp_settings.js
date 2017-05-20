/// <reference path="jquery-1.10.2-vsdoc.js" />
/// <reference path="en-US.js" />


function initial_event() {
    $("#cancel_btn").click(function () {
        window.close();
    });

    $("#ok_btn").click(function () {

    });

    $("#test_btn").click(function () {
        var URL = "";
        if ($("#FtpServer").val() == "") {
            window.alert(FTP_Please_input_ftp_server);
            $("#FtpServer").select().focus();
            return false;
        }

        if ($("#FtpServerPort").val() == "") {
            window.alert(FTP_Please_input_ftp_server_port);
            $("#FtpServerPort").select().focus();
            return false;
        }

        if ($("#FtpUser").val() == "") {
            window.alert(FTP_Please_input_ftp_user);
            $("#FtpUser").select().focus();
            return false;
        }

        if ($("#FtpPassword").val() == "") {
            window.alert(FTP_Please_input_ftp_password);
            $("#FtpPassword").select().focus();
            return false;
        }

        URL = "/cgi-bin/ftp_settings.cgi?action=ftp_test" + "&date=" + new Date().getTime() +
		  "&FtpServer=" + $("#FtpServer").val() + "&FtpServerPort=" + $("#FtpServerPort").val() + "&FtpUser=" +
		  $("#FtpUser").val() + "&FtpPassword=" + $("#FtpPassword").val();

        document.getElementById("test_hiddenframe").src = URL;
    });
    $(window).load(function () {
        $("#FtpServerPort").css("width", $("#FtpServer").css("width"));
        $("#FtpUser").css("width", $("#FtpServer").css("width"));
        $("#FtpPassword").css("width", $("#FtpServer").css("width"));
    });
}

function initial_elements () {
    $("#FtpServer").val(FtpServer);
    $("#FtpServerPort").val(FtpServerPort);
    $("#FtpUser").val(FtpUser);
    $("#FtpPassword").val(FtpPassword);
}
function initial_language() {
    $("#ftp-settings-page-title").text(FTP_Settins);
    $("#ftp-settings_text").text(FTP_Settins);
    $("#ftpsever_text").text(FTP_server);
    $("#FtpServerPort_text").text(FTP_Server_port);
    $("#ftpuser_text").text(FTP_User_name);
    $("#FtpPassword_text").text(FTP_Password);
    $("#ftp_test_text").text(FTP_Test);
    $("#ftp_test_msg1").text(FTP_test_message_1);
    $("#ftp_test_msg2").text(FTP_test_message_2);
    $("#test_btn").val(FTP_Test);
    $("#btnSave").val(FTP_Save);
}

$(function () {
    initial_language();
    initial_elements();
    initial_event();
});
