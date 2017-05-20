/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />


jQuery.fn.checkIP = function () {
    var $this = $(this);
    if (!$this.val().replace(/(^\s*)|(\s*$)/g, "").match(/^((?:(?:25[0-5]|2[0-4]\d|((1\d{2})|([1-9]?\d)))\.){3}(?:25[0-5]|2[0-4]\d|((1\d{2})|([1-9]?\d))))$/)) {
        alert(ETH_ERR_IP);
        $this.focus().select();
        return false;
    }
    else {
        return true;
    }

}
function initial_events() {
    $("#dhcp_radio").click(function () {
        $("[owner=static]").attr("disabled", "disabled");
        $("[owner=pppoe]").attr("disabled", "disabled");
    });
    $("#static_radio").click(function () {
        $("[owner=static]").removeAttr("disabled");
        $("[owner=pppoe]").attr("disabled", "disabled");
    });
    $("#pppoe_radio").click(function () {
        $("[owner=static]").attr("disabled", "disabled");
        $("[owner=pppoe]").removeAttr("disabled");
    });

    $("form").submit(function () {
        if ("static" == $("form :radio:checked").val()) {
            if (!($("#ipblank").checkIP() && $("#netmaskblank").checkIP() && $("#gatewayblank").checkIP())) {
                return false;
            }
        }
        else if ("pppoe" == $("form :radio:checked").val()) {
            if ($("#Userblank").val().replace(/(^\s*)|(\s*$)/g, "") == "") {
                $("#Userblank").focus().select();
                return false;
            }
            if ($("#Passwordblank").val() == "") {
                $("#Passwordblank").focus().select();
                return false;
            }
            if (!$("#pdnsblank").checkIP()) {
                return false;
            }
            if ($("#pdnsblank_2").val() != "" && !$("#pdnsblank_2").checkIP()) {
                return false;
            }
        }
        if (!$("#primary_dns").checkIP()) {
            return false;
        }
        if ($("#secondary_dns").val() != "" && !$("#secondary_dns").checkIP()) {
            return false;
        }
        if ($("#hostname").val().replace(/(^\s*)|(\s*$)/g, "") == "") {

            $("#hostname").focus().select();
            return false;
        }
        return true;
    });
    if (netselect == 1) {
        $("#dhcp_radio").click();
    }
    else if (netselect == 2) {
        $("#static_radio").click();
    }
    else {
        $("#pppoe_radio").click();
    }
}

function initial_elements() {

    $("#ipblank").val(netaddress);
    $("#netmaskblank").val(netmask);
    $("#gatewayblank").val(gateway);
    $("#Userblank").val(pppoe_user);
    $("#Passwordblank").val(pppoe_password);
    $("#pdnsblank").val(dns1);
    $("#pdnsblank_2").val(dns2);
    $("#pppoe_addr").val(pppoe_address);
    $("#primary_dns").val(primary_dns);
    $("#secondary_dns").val(secondary_dns);
    $("#hostname").val(hostname);
    $("#Enable_IPv6").prop("checked",if_ipv6 != 0);

}

function initial_language() {
    $("#ethernet-page-title").text(ETH_Ethernet_Settings);
    $("#IPv4_title").text(ETH_IPv4_Address_Configuration);
    $("#dhcp_label").text(ETH_DHCP);
    $("#static_label").text(ETH_Static);

    $("#IPv4_ip_text").text(ETH_IP);
    $("#IPv4_mask_text").text(ETH_Netmask);
    $("#IPv4_gateway_text").text(ETH_Gateway);
    $("#pppoe_label").text(ETH_PPPoE);

    $("#pppoe_name_text").text(ETH_User_name);
    $("#pppoe_pwd_text").text(ETH_Password);
    $("#pppoe_dns1_text").text(ETH_DNS1);
    $("#pppoe_dns2_text").text(ETH_DNS2);

    $("#pppoe_ip_text").text(ETH_IP_address);
    $("#IPv6_title").text(ETH_IPv6_Address_Configuration);
    $("#IPv6_label").text(ETH_Enable_IPv6);
    $("#dns_title").text(ETH_DNS_Configuration);

    $("#dns_dns1_text").text(ETH_Primary_DNS_server);
    $("#dns_dns2_text").text(ETH_Secondary_DNS_server);
    $("#host_title").text(ETH_Host_Name_Configuration);
    $("#host_text").text(ETH_Host_name);

    $("#btnSave").val(ETH_Save);
}

$(function () {
    initial_language();
    initial_elements();
    initial_events();
});