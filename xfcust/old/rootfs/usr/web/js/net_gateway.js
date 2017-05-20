/// <reference path="jquery-1.10.2.min.js" />
/// <reference path="en-US.js" />


jQuery.fn.checkIP = function () {
    var $this = $(this);
    if (!$this.val().replace(/(^\s*)|(\s*$)/g, "").match(/^((?:(?:25[0-5]|2[0-4]\d|((1\d{2})|([1-9]?\d)))\.){3}(?:25[0-5]|2[0-4]\d|((1\d{2})|([1-9]?\d))))$/)) {
        typeof (ETH_ERR_IP) != "undefined" ? alert(ETH_ERR_IP) : "";
        $this.focus().select();
        return false;
    }
    else {
        return true;
    }

}

function initial_language() {
    $("#gateway-page-title").text(GW_Route_table);
    $("#destination_title").text(GW_Destination);
    $("#gateway_title").text(GW_Gateway);
    $("#gatemask_title").text(GW_Gatemask);
    $("#flags_title").text(GW_Flags);
    $("#metric_title").text(GW_Metric);
    $("#iface_title").text(GW_Iface);
    $("#set_text").text(GW_Set_default_gateway);

    $("#set_btn").val(GW_Save);
}

function initial_elements() {
    $.each(route_tables, function (index, elem) {
        if (elem != "") {
            var elems = elem.split(/\s{1,}/);
            $.each(elems, function (index, elem) {
                if (index == 5 || index == 6) {// Ref and Use field, not use
                    return;
                }
                $("#space_div").before("<div class=\"col-xs-2 col-sm-2 col-md-2\">" + elem + "</div>");
            });
        }
    });
}
function initial_events() {
    $("form").submit(function () {
        try {
            return $("#gateway").checkIP();
        } catch (exception) {
            alert(exception.message);
            return false;
        }
    });
}
$(function () {
    initial_language();
    initial_elements();
    initial_events();
});