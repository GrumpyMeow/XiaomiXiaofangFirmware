/*common function ,I will move it later*/
function dw(s)
{
	document.write(s);
}
/*common function ,I will move it later*/
$(document).ready(function(){
         
});

function initial_language() {
    $("#header").text(WL_3title);
	$("#ssid").val(ap);
	$("#submit").val(WL_3apply);
	$("#Cancel").val(WL_3cancel);		      		     
}
function initial_events() {
	$(":radio").click(list);
}
//document ready
$(function () {
    initial_language();
	initial_events();
	list();
	document.getElementById('keymode_wifi').onchange();	
    var inputs = document.getElementsByTagName('input');
    var i = 0;
    for (i = 0; i < inputs.length; i++) {
        inputs.item(i).style.imeMode = "disabled";
        inputs.item(i).onpaste = function(){
            return false;
        };
        inputs.item(i).ondrop = function(){
            return false;
        };
    }	
});
                                                
