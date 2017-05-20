/// <reference path="en-US.js" />
/// <reference path="jquery-1.10.2.min.js" />

function initial_elements() {
    if (action == "delete" && no_permission) {
        alert(User_no_permission_del_err);
        history.go(-1);
    }
    if (action == "get_modify_page" && no_permission) {
        alert(User_no_permission_modify_err);
        window.close();
    }
    if (action == "get_add_page" && no_permission) {
        alert(User_no_permission_add_err);
        window.close();
    }
    if (action == "modify" || action == "add") {
        window.opener.location.href = '/cgi-bin/sys_user.cgi?p=' + new Date().getTime();
        window.close();
    }
    $.each(user_array, function (i, val) {
        var val_name = val[0];
        var show_name = val[1];
        var power_name = val[2];
        var option_show = show_name;

        var space_num = parseInt($("#user_list").css("width")) / parseInt($("#user_list").css("font-size")) * (11 / 6) - 9;
        $(window).width() == 772 ? space_num-- : "";
        if (power_name == "Administrator") {
            power_name = User_admin;
        }
        else if (power_name == "Operator") {
            power_name = User_oper;
        }
        else {
            power_name = User_viewer;
        }
        for (var i = 0; i < space_num - show_name.length; i++) {
            option_show += "&nbsp;";
        }
        option_show += power_name;
        $("#user_list").append("<option value=\"" + val_name + "\">" + option_show + "</option>");
    });
    $("#user_list").val(user_array[0][0]);
}

function initial_language() {
    $("#user-page-title").text(User_title);
    $("#users_list_text").text(User_list);
    $("#users_text").text(User_username);
    $("#group_text").text(User_group);
    $("#add_btn").val(User_add);
    $("#modify_btn").val(User_modify);
    $("#remove_btn").val(User_del);
}

function initial_events() {

    $("#add_btn").click(function () {
        window.open('/cgi-bin/sys_user.cgi?action=get_add_page', 'Adduser', 'width=350,height=300');
        //TODO
        //window.open('add_user.htm', 'Adduser', 'width=350,height=300');
    });
    $("#modify_btn").click(function () {
        window.open('/cgi-bin/sys_user.cgi?action=get_modify_page&user=' + $("#user_list").val(), 'Modifyuser', 'width=350,height=300');
        //window.open('modify_user.htm', 'Modifyuser', 'width=350,height=300');
    });
    $("#remove_btn").click(function () {
        var deleteConfirm = window.confirm(User_del_warning);
        if (!deleteConfirm)
            return false;
        var action = "delete";
        var submitForm = deleteForm;
        var userName = $("#user_list").val();
        // Build submitstring
        if (userName == "root") {
            alert(User_del_root_err);
            return false;
        }
        submitForm.action.value = action;
        submitForm.op.value = "user";
        submitForm.user.value = userName;
        submitForm.submit();
        //	window.reload();
        return true;
    });
    $(window).resize(function () {
        var select_user = $("#user_list").val();
        $("#user_list").html("");
        $.each(user_array, function (i, val) {
            var val_name = val[0];
            var show_name = val[1];
            var power_name = val[2];
            var option_show = show_name;

            var space_num = parseInt($("#user_list").css("width")) / parseInt($("#user_list").css("font-size")) * (11 / 6) - 9;
            $(window).width() == 772 ? space_num-- : "";
            if (power_name == "Administrator") {
                power_name = User_admin;
            }
            else if (power_name == "Operator") {
                power_name = User_oper;
            }
            else {
                power_name = User_viewer;
            }
            for (var i = 0; i < space_num - show_name.length; i++) {
                option_show += "&nbsp;";
            }
            option_show += power_name;
            $("#user_list").append("<option value=\"" + val_name + "\">" + option_show + "</option>");
        });
        $("#user_list").val(select_user);
    });
}

function get_usre_list() {
    var users = new Array();
    $("#user_list option").each(function (index, elem) {
        users[index] = $(elem).val();
    });
    return users;
}
function get_select_user() {
    var select_user = $("#user_list :selected").val();
    var ret;
    $.each(user_array, function (index, elem) {
        if (select_user == elem[0]) {
            ret = elem;
        }
    });
    return ret;
}
$(function () {
    initial_elements();
    initial_language();
    initial_events();
});