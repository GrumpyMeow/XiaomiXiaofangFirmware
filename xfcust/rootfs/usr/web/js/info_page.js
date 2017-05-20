function initial_language() {
    if (typeof header_flag !== "undefined" && header_flag !== null) 
        $("#header").text(eval(header));
    else 
        $("#header").text(header);
    if (typeof infomsg_flag !== "undefined" && infomsg_flag !== null) {
        $("#infomsg").text(eval(infomsg));
    }
    else 
        $("#infomsg").text(infomsg);
    if (typeof othermsg_flag !== "undefined" && othermsg_flag !== null) 
        $("#othermsg").text(eval(othermsg));
    else 
        $("#othermsg").text(othermsg);                   
}

//document ready
$(function () {
    initial_language();
});
