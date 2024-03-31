var external = null;

String.prototype.format = function() {  
    if(arguments.length == 0) return this;  
    var obj = arguments[0];
    //console.log('Logging message obj: \n', obj);
    var s = this;  
    for (var key in obj) {
        console.log('=============key:\n', key);
        console.log('=============obj[key]:\n', obj[key]);
        s = s.replace(new RegExp("\\{\\{" + key + "\\}\\}", "g"), obj[key]);
    }

    console.log('=============FINISH s:\n', s);
    return s;  
}  

new QWebChannel(qt.webChannelTransport,
	function(channel) {
		external = channel.objects.external;
	}
);

function appendHtml(msg) {
	$("#placeholder").append(external.msgRHtmlTmpl.format(msg));
	window.scrollTo(0,document.body.scrollHeight); ;  
};

function recvHtml(msg) {
	$("#placeholder").append(external.msgLHtmlTmpl.format(msg));
	window.scrollTo(0,document.body.scrollHeight); ;  
};