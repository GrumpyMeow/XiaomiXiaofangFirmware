/// <reference path="jquery-1.10.2-vsdoc.js" />
/// <reference path="en-US.js" />
/// <reference path="common.js" />

var mousedown_left_flag = false;
var mousedown_right_flag = false;

function initial_event() {
    $(window).resize(function () {
        $("#mask_div").css({
            "height": $("#bgpic").css("height"),
            "width": $("#bgpic").css("width"),
            "position": "absolute",
            "top": $("#bgpic").position().top + "px",
            "left": $("#bgpic").position().left + "px",
            "text-align": "left"
        });
        var elem_height = parseInt($("#mask_div").css("height")) / 12;
        var elem_width = parseInt($("#mask_div").css("width")) / 16;
        for (var i = 0; i < 192; i++) {
            $("#" + i).css({
                "height": elem_height + "px",
                "width": elem_width + "px",
                //"position": "absolute",
                "top": parseInt((i / 16)) * elem_height + "px",
                "left": parseInt((i % 16)) * elem_width + "px"
                //"opacity": "0.5"
            });
        }
        $("#slier-div").css("height", $("#slier-div").next().css("height"));
        $("#slider").css("margin-top", (parseInt($("#slider").parent().height()) - parseInt($("#slider").height())) / 2 + "px"); //align center
    })
	.load(function () {
		$(this).resize();
	});
    $(".mask_elem").mousedown(function (e) {
        switch (e.which)//Determine the button of mouse which is pressed by jQuery . 1 left , 2 middle , 3 right . Modify by xyd
        {
            case 1: //left button
                mousedown_left_flag = true;
                mousedown_right_flag = false;
                break;
            //case 2:   //middle button        
            case 3: //right button
                mousedown_right_flag = true;
                mousedown_left_flag = false;
                break;
            default: //reserve
                break;
        }
        $(this).mouseenter();
        return false;
    })
    .mouseenter(function () {
        mousedown_left_flag ? $(this).addClass("mask_elem_color") : "";
        mousedown_right_flag ? $(this).removeClass("mask_elem_color") : "";

    })
    .contextmenu(function (e) {
        mousedown_right_flag = mousedown_left_flag = false;
        e.preventDefault();
        return false;
    });
    $(document).mouseup(function () {
        mousedown_right_flag = mousedown_left_flag = false;
        return false;
    });
    $("#selectAll_btn").click(function () {
        $(".mask_elem").addClass("mask_elem_color");
    });
    $("#clearAll_btn").click(function () {
        $(".mask_elem").removeClass("mask_elem_color");
    });
    $("#reset_btn").click(function () {
        $("#clearAll_btn").click();
        var select_elems = MotionAreas.split(/\&/);
        $.each(select_elems, function (index, elem) {
            $("#" + elem).addClass("mask_elem_color");
        });
    });
    $("#btnSave").click(function () {
        {//save select areas
            var count = "";
            var URL = "";
            $.each($(".mask_elem_color"), function (index, elem) {
                count += (index == 0 ? "" : "&") + $(elem).prop("id");
            });
            MotionAreas = count;
            URL = "/cgi-bin/motion_area.cgi?" + new Date().getTime() + "@" + count;
            $("#areas_hiddenframe").attr("src", URL);
        }
        {//save sensitivity
            var URL = "";
            URL = "/cgi-bin/motion_detection.cgi?action=md_save" +
		    "&date=" + new Date().getTime() + "&sensitivity=" + sensitivity_value;

            $("#motion_hiddenframe").attr("src", URL);
        }
    })
}

function initial_elements() {
    {//initial slider bar
        $("#slider").slider({
            value: current_value,
            min: min_value,
            max: max_value,
            step: step_value,
            slide: function (event, ui) {
                $("#amount").val(ui.value);
                sensitivity_value = ui.value;
                $(this).attr("title", ui.value);
            }
        })
        .attr("title", current_value);
        $("#amount").val($("#slider").slider("value"));
        $("#slier-div").css("height", $("#slier-div").next().css("height"));
        $("#slider").css("margin-top", (parseInt($("#slider").parent().height()) - parseInt($("#slider").height())) / 2 + "px"); //align center

    }
    {//initial select areas
        $("#bgpic").parent().append("<div id=\"mask_div\"></div>");
        $("#mask_div").css(
        {
            "height": $("#bgpic").css("height"),
            "width": $("#bgpic").css("width"),
            "position": "absolute",
            "top": $("#bgpic").position().top + "px",
            "left": $("#bgpic").position().left + "px",
            "text-align": "left"
        });
        var elem_height = parseInt($("#mask_div").css("height")) / 12;
        var elem_width = parseInt($("#mask_div").css("width")) / 16;
        for (var i = 0; i < 192; i++) {
            $("#mask_div").append("<div class=\"mask_elem div-inline\" id=\"" + i + "\"></div>");
            $("#" + i).css({
                "height": elem_height + "px",
                "width": elem_width + "px",
                "position": "absolute",
                "top": parseInt((i / 16)) * elem_height + "px",
                "left": parseInt((i % 16)) * elem_width + "px",
                "opacity": "0.5"
            });
        }
        var select_elems = MotionAreas.split(/\&/);
        $.each(select_elems, function (index, elem) {
            $("#" + elem).addClass("mask_elem_color");
        });
    }
}
function initial_language() {
    $("#motion_detection-page-title").text(MD_Motion_Detection);
    $("#note_text").text(MD_Note);
    $("#note_message_text").text(MD_Note_message);
    $("#Sensitivity_text").text(MD_Sensitivity);
    $("#low_text").text(MD_Low);
    $("#high_text").text(MD_High);

    $("#selectAll_btn").val(MD_Select_All);
    $("#clearAll_btn").val(MD_Clean_All);
    $("#reset_btn").val(MD_Reset);
    $("#btnSave").val(MD_Save);
}

$(function () {
    initial_language();
    initial_elements();
    initial_event();
});
