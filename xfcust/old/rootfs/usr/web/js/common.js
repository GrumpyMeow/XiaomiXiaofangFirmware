/// <reference path="jquery-1.10.2.min.js" />
$.fn.extend({
    center: function () {
        var obj = $(this);
        var height = parseInt(obj.css("height"));
        var width = parseInt(obj.css("width"));
        var $p = obj.parent();
        var pheight = parseInt($p.css("height"));
        var pwidth = parseInt($p.css("width"));
        obj.css({
            "position": "absolute",
            "top": (pheight - height) / 2 + "px",
            "left": (pwidth - width) / 2 + "px"
        });
        return obj;
    }
});

function load_res(filename) {
    filename = filename.replace(/\?.*$/g, "");
    if (filename.toLowerCase().match(/\.js$/)) {
        document.write('<script type="text/javascript" src="' + filename + '?v=' + (typeof (FIRMWARE_VERSION) != "undefined" ? FIRMWARE_VERSION : new Date().getTime()) + '"></script>');
    }
    else if (filename.toLowerCase().match(/\.css$/)) {
        document.write('<link href="' + filename + '?v=' + (typeof (FIRMWARE_VERSION) != "undefined" ? FIRMWARE_VERSION : new Date().getTime()) + '" rel="stylesheet" type="text/css" />');
    }
}

function change_language(lang) {
    typeof initial_language == "function" ? $.getScript("../js/" + lang + ".js", initial_language) : window.location.reload(true);
}

$(function () {
    $(".title-font").parent().addClass("body-border");
    $(".title-font").parent().find(".row").addClass("content-border");
});
$(window).load(function () {	
    if(parent != self)
    	{
    		if(parent.$("#contant_iframe").attr("src").indexOf("/cgi-bin/live_view.cgi") == -1)  //not liveview page.
			parent.child_page_ready();	
    	}
    	
    $(".title-font").parent().append("<div class=\"col-xs-12 col-sm-12 col-md-12 height30\"></div>")
    .find(".row").addClass("content-style");
//    var lineSize = parseInt($(".title-font").parent().find(".row").width());
//    var lines = $(".title-font").parent().find(".row").find("div");
//    var lineIndex = 0;
//    var curSize = 0;
//    $.each(lines, function (index, elem) {
//        if (lineIndex % 2 == 1) {
//            //TODO
//            $(elem).addClass("line-mark");
//        }
//        curSize += parseInt($(elem).width() + 30);
//        if (curSize + 11 >= lineSize) {
//            lineIndex++;
//            curSize = 0;
//        }
//    });
})
