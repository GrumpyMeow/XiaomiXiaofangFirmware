/// <reference path="en-US.js" />
/// <reference path="index.js" />
/// <reference path="jquery-1.10.2.min.js" />

var setup_url = "/cgi-bin/video_settings.cgi";
var liveview_url = "/cgi-bin/live_view.cgi";
var is_setUp = false;
$(document).on('click.bs.collapse.data-api', '[data-toggle="collapse"]', function (e) {
    var href = $(this).attr("href");
    var span = href + "-span";
    $(".caret-down").removeClass().addClass("caret-right");
    $(span).removeClass().addClass($(this).hasClass("collapsed") ? "caret-right" : "caret-down");
});
function child_page_ready()
{
	if(is_setUp == false )
	{
		$("#contant_iframe").parent().removeClass("col-xs-12 col-sm-12 col-md-12").addClass("col-xs-10 col-sm-10 col-md-10 left-border");
		$("#menu").show();
		is_setUp = true;
	}
}
function initial_language() {

    //media

    $("#media-title").text(NV_Media);
    $("#media-video-settings").text(NV_Video_settings);
    $("#media-audio-settings").text(NV_Audio_settings);
    $("#media-image-settings").text(NV_Image_settings);
    $("#media-osd-settings").text(NV_OSD_settings);
    $("#media-private-mask").text(NV_Private_Mask);

    //network

    $("#network-title").text(NV_Network);
    $("#network-ip-filter").text(NV_IP_address_filter);
    $("#network-liveview-acl").text(NV_Liveview_acl);
    $("#network-eth").text(NV_Ethernet);
    $("#network-ddns").text(NV_DDNS);
    $("#network-wireless").text(NV_Wireless);
    $("#network-socks").text(NV_SOCKS);
    $("#network-qos").text(NV_QoS);
    $("#network-snmp").text(NV_SNMP);
    $("#network-upnp").text(NV_UPnP);
    $("#network-bonjour").text(NV_Bonjour);
    $("#network-gateway").text(NV_Gateway);
    $("#network-port-settings").text(NV_Port_Settings);

    //event

    $("#event-title").text(NV_Event);
    $("#event-event-settings").text(NV_Event_settings);
    $("#event-motion-detection").text(NV_Motion_detection);
    $("#event-record-search").text(NV_Record_search);

    //system

    $("#system-title").text(NV_System);
    $("#system-information").text(NV_Information);
    $("#system-date").text(NV_Date_and_time);
    $("#system-user").text(NV_User);
    $("#system-log").text(NV_Logs_and_reports);
    $("#system-maintenance").text(NV_Maintenance);

    //about

    $("#about-title").text(NV_About);

    //topTitle
    $("#topTitle").text(IX_Camera);

    //liveview
    $("#liveview_btn").val(IX_Liveview);

    //setup
    $("#setup_btn").val(IX_Setup);

    //help
    $("#help_btn").val(IX_Help);
}

function initial_window() {
    var win_height = $(window).height();
    var win_width = $(window).width();
    var $menu = $("#menu");
    var $navigate = $("#navigate");
    $("#container").removeClass()
    .addClass(parseInt(win_width) < 992 ? "container-fluid" : "container");
    $menu.css({
        "padding-left": "0px",
        "padding-right": "0px"
    });
    $("#menu_context").css("height", win_height - 10 - parseInt($navigate.css("height")) + "px");
    $("#topTitle").center();
    $("#lang").center();
    $("#liveview_btn").center();
    $("#setup_btn").css("width", $("#liveview_btn").css("width")).center();
    $("#help_btn").css("width", $("#liveview_btn").css("width")).center();
}

function initial_events() {
    $(".panel-body a").click(function (e) {
        $("#contant_iframe").attr("src", $(this).data("cgi_href") + "?t=" + new Date().getTime());
        e.stopPropagation();
    });
    $(".panel-body").click(function () {
        $(this).find("a").click();
    });
    $("#about-title").parent().click(function () {
        $("#contant_iframe").attr("src", $("#about-title").data("cgi_href") + "?t=" + new Date().getTime());
    });
    $(window).resize(function () {
        initial_window();
    });

    $("#liveview_btn").click(function () {
        $("#menu").hide();
        if (is_setUp) {
            setup_url = $("#contant_iframe").prop("src").replace(/\?.*$/g,"");
        }
        $("#contant_iframe").attr("src", liveview_url + "?t=" + new Date().getTime()).parent().removeClass("col-xs-10 col-sm-10 col-md-10 left-border").addClass("col-xs-12 col-sm-12 col-md-12");	
        is_setUp = false;
    }).click();
    $("#setup_btn").click(function () {
        $.getJSON("/cgi-bin/index.cgi",
        {
            "get_power": "get_power",
            "t": new Date().getTime()
        },
        function (json) {
            if (json.get_power.match("snxadmin") != null) {
                $("#contant_iframe").attr("src", setup_url + "?t=" + new Date().getTime());		
            }
            else {
                alert(IX_Refuse_setup);
            }
        });
    });

    $("#lang").change(function () {
        $.get("/cgi-bin/save_language.cgi", {
            "p": new Date().getTime(),
            "lang": $("#lang").val()
        }, function (data, status) {
            if (status == "success") {
                change_language($("#lang").val());
                $("#contant_iframe")[0].contentWindow.change_language($("#lang").val());
            }
            else {
                alert(status + ":/cgi-bin/save_language.cgi");
            }
        });
    });

    $.getJSON("/cgi-bin/index.cgi",
    {
        "get_language": "get_language",
        "sd_support": "sd_support",
        "v": (typeof (FIRMWARE_VERSION) != "undefined" ? FIRMWARE_VERSION : new Date().getTime())
    },
    function (json) {
        change_language(json.get_language);
        $("#lang").val(json.get_language);
        json.sd_support == false ? $("#event-record-search").parent().remove() : "";
    });
    $(window).load(initial_window);
}

//document is ready
$(function () {
    initial_language();
    initial_events();
    initial_window();
});

