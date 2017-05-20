/// <reference path="jquery-1.10.2-vsdoc.js" />
/// <reference path="en-US.js" />

function initial_event() {
    $("#cancel_btn").click(function () {
        window.close();
    });

    $("#ok_btn").click(function () {
        var reg_user = /^[a-zA-Z]\w{0,31}/g;
        var reg_pwd = /\S{1,64}/g;
        var user_list = window.opener.get_usre_list();
        var user = $("#user").val();
        var pwd = $("#pwd").val();
        var repwd = $("#repwd").val();
        if (user_list.length > 9) {
            alert(User_too_many_user);
            return;
        }
        if (!user.match(reg_user)) {
            alert(User_name_invalid);
            return;
        }
        if (pwd != repwd) {
            alert(User_passwd_match_err);
            return;
        }
        if (!pwd.match(reg_pwd)) {
            alert("error pwd");
            return;
        }
        for (var i = 0; i < user_list.length; i++) {
            if (user_list[i] == user) {
                alert(User_name_exist);
                return;
            }
        }
        $("#action").val("add");
        $("#op").val("user");
        $("#submitForm").submit();
    });
}
function initial_language() {
    $("#name_text").text(User_username);
    $("#passwd_text").text(User_passwd);
    $("#repasswd_text").text(User_repasswd);
    $("#group_text").text(User_group);
    $("#view_text").text(User_viewer);
    $("#admin_text").text(User_admin);
    $("#ok_btn").val(User_OK);
    $("#cancel_btn").val(User_cancel);
}

$(function () {
    initial_language();
    initial_event();
});
