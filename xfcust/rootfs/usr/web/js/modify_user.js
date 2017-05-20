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
        $("#action").val("modify");
        $("#op").val("user");
        $("#user").removeAttr("disabled");
        $("#submitForm").submit();
        $("#user").attr("disabled", "disabled");
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

function initial_elements() {
    var select_user = window.opener.get_select_user();
    $("#user").val(select_user[0]);
    $("#user").val() == "root" ? $("#view_radio").attr("disabled", "disabled") : "";
    $("#" + (select_user[2] == "Administrator" ? "admin_radio" : "view_radio")).click();
}

$(function () {
    initial_language();
    initial_event();
    initial_elements();
});
