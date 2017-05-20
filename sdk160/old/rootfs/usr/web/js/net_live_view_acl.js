/// <reference path="en-US.js" />
/// <reference path="jquery-1.10.2.min.js" />

function initial_language() {
    $("#live-view-acl-page-title").text(LVA_Live_View_ACL_Settings);
    $("#general_text").text(LVA_General);
    $("#enable_text").text(LVA_Enable_Live_View_ACL);
    $("#acl_allow").text(LVA_Allow);
    $("#acl_deny").text(LVA_Deny);
    $("#acl_deny_ip_text").text(LVA_the_following_IP_addresses);
    $("#apply_btn").val(LVA_Apply);
    $("#acl_ip_address_text").text(LVA_Filtered_IP_Addresses);
    $("#add_btn").val(LVA_Add);
    $("#remove_btn").val(LVA_Remove);
}

function initial_elements() {
    aclArray.sort();
    $.each(aclArray, function (index, elem) {
        $("#acl_ip_addresses").append("<option value=\"" + elem + "\">" + elem + "</option>");
    });
    if (aclArray.length == 0) {
        $("#apply_btn").attr("disabled", "disabled");
        //$('#enable_filter').removeAttr('checked');
        $("#remove_btn").attr("disabled", "disabled");
    }
    else {
        $("#acl_ip_addresses").val(aclArray[0]);
        acl_enable ? $('#acl_enable').attr('checked', 'checked') : "";
    }
    $("#acl_method").val(acl_method);
}

function initial_events() {

    $("#add_btn").click(function () {
        window.open('../html/net_acl_add_ipaddr.html', 'AddIPAddress', 'width=600,height=250');
    });

    $("#remove_btn").click(function () {
        var $remove_form = $("#liveview_acl_remove_form");
        var $remove_ipaddr = $("#liveview_acl_remove_form [name=ip_addr]");
        if (!$("#acl_ip_addresses").val()) {
            alert(LVA_Remove_select_warning);
            return false;
        }
        $remove_ipaddr.val($("#acl_ip_addresses").val());
        confirm(LVA_Remove_warning) ? $remove_form.submit() : "";
    });
}

$(function () {
    initial_language();
    initial_elements();
    initial_events();
});

function get_ip_list() {
    return aclArray;
}
