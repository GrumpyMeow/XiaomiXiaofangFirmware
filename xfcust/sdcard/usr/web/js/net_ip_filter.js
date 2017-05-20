/// <reference path="en-US.js" />
/// <reference path="jquery-1.10.2.min.js" />

function initial_language() {
    $("#ip-filter-page-title").text(IAF_IP_Address_Filtering);
    $("#general_text").text(IAF_General);
    $("#enable_text").text(IAF_Enable_IP_address_filtering);
    $("#filter_allow").text(IAF_Allow);
    $("#filter_deny").text(IAF_Deny);
    $("#allow_deny_ip_text").text(IAF_the_following_IP_addresses);
    $("#apply_btn").val(IAF_Apply);
    $("#filter_ip_address_text").text(IAF_Filtered_IP_Addresses);
    $("#add_btn").val(IAF_Add);
    $("#remove_btn").val(IAF_Remove);
}

function initial_elements() {
    filterArray.sort();
    $.each(filterArray, function (index, elem) {
        $("#filter_ip_addresses").append("<option value=\"" + elem + "\">" + elem + "</option>");
    });
    if (filterArray.length == 0) {
        $("#apply_btn").attr("disabled", "disabled");
        //$('#enable_filter').removeAttr('checked');
        $("#remove_btn").attr("disabled", "disabled");
    }
    else {
        $("#filter_ip_addresses").val(filterArray[0]);
        filter_enable ? $('#enable_filter').attr('checked', 'checked') : "";
    }
    $("#filter_method").val(filter_method);
}

function initial_events() {

    $("#add_btn").click(function () {
        window.open('../html/net_filter_add_ipaddr.html', 'AddIPAddress', 'width=600,height=250');
    });

    $("#remove_btn").click(function () {
        var $remove_form = $("#ip_addr_filter_remove_form");
        var $remove_ipaddr = $("#ip_addr_filter_remove_form [name=ip_addr]");
        if (!$("#filter_ip_addresses").val()) {
            alert(IAF_Remove_select_warning);
            return false;
        }
        $remove_ipaddr.val($("#filter_ip_addresses").val());
        confirm(IAF_Remove_warning) ? $remove_form.submit() : "";
    });
}

$(function () {
    initial_language();
    initial_elements();
    initial_events();
});

function get_ip_list() {
    return filterArray;
}
