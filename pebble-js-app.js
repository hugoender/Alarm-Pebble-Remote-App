var timeoutForHttpRequest = 12000;

//var serverHost = localStorage.getItem("server_host") || "";
var serverHost = "/* Host IP Address */";
var serverPort = "/* Host Port*/";

function makeRequest(request) {
	//console.log("makeRequest entered");
	var xhr = new XMLHttpRequest();
	xhr.open("POST", "http://" + serverHost + ":" + serverPort + "/GPIO/" + request + "/sequence/2000,10", true);
	xhr.timeout = timeoutForHttpRequest;
	xhr.send();
	
	console.log("Following request sent to phone: http://" + serverHost + ":" + serverPort + "/GPIO/" + request + "/sequence/2000,10");
}

Pebble.addEventListener("ready", function(e) {
	console.log("Connected?: " + e.ready);	
});

Pebble.addEventListener("appmessage", function(e) {
	console.log("App Message received from Pebble: " + JSON.stringify(e.payload));
	
	//In order for the following to work, you need to specify "request" key in PebbleKit JS Message Keys 
	var request = e.payload.request;
	
	switch (request) {
		case "armAlarm":
			request = "/* GPIO# for Arm */";
			break;
		case "disarmAlarm":
			request = "/* GPIO# for Disarm */";
			break;
		case "stayAlarm":
			//I do not have RPi wired for this mode
			break;
	}
	
	makeRequest(request);
});