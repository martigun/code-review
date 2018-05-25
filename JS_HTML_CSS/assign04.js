//Gunnar Martin
//CS290
//Winter 2016
//Assignment: AJAX Interactions
	
//set city button and zip button
var cityButton = document.getElementById("cityButton")
var zipButton = document.getElementById("zipButton")

//add listeners for buttons
cityButton.addEventListener("click", cityClick);
zipButton.addEventListener("click", zipClick);
	
//for testing
//var old = "http://api.openweathermap.org/data/2.5/weather?q=Corvallis,or&appid=fa7d80c48643dfadde2cced1b1be6ca1";

//set root and appid
var root = "http://api.openweathermap.org/data/2.5/weather?q="
var appid = "&appid=fa7d80c48643dfadde2cced1b1be6ca1"

//on city click
function cityClick(event){
	
	//get city input value
	var city_input = document.getElementById("city_input").value;
	
	var req = new XMLHttpRequest();
	req.open("GET", root + city_input + appid, true); //true for async!
	
	//waits for the response to load
	req.addEventListener('load',function(){
		//check status
		if(req.status >= 200 && req.status < 400){
			//parse results for console
			console.log(JSON.parse(req.responseText));
			
			//send results string to page
			document.getElementById("weatherResults").textContent = req.responseText;
		} else {
			//there was an error
			console.log("Error in network request: " + req.statusText);
		};
	});
	
	req.send(null); //keep on truckin, since async=true!
};

//on zip click
function zipClick(event){
	
	//get zip input value
	var zip_input = document.getElementById("zip_input").value;
	zip_input = "zip=" + zip_input;
	
	var req = new XMLHttpRequest();
	req.open("GET", root + zip_input + appid, true);
	
	//waits for the response to load
	req.addEventListener('load',function(){
		//check status
		if(req.status >= 200 && req.status < 400){
			//parse results for console
			console.log(JSON.parse(req.responseText));
			
			//send results string to page
			document.getElementById("weatherResults").textContent = req.responseText;
		} else {
			//there was an error
			console.log("Error in network request: " + req.statusText);
		};
	});
	
	req.send(null);//keep on truckin, since async=true!
	
}




//set pre-pop and send data buttons
var popDataButton = document.getElementById("popDataButton");
var sendDataButton = document.getElementById("sendData");

//add listeners for buttons
popDataButton.addEventListener("click", popDataClick);
sendDataButton.addEventListener("click", sendDataClick);

//pop data click
function popDataClick(event){
	
	var prePopData = '{"FirstName":"Dan","LastName":"Welks","City":"Detroit","State":"MI"}'
	
	document.getElementById("data_input").value = prePopData;
}

//set root for post
var root_post = "http://httpbin.org/post"

//send data click
function sendDataClick(event){
	
	
	//set up request
	var req = new XMLHttpRequest();
	req.open("POST", root_post, true);
	
	//set request header data
	req.setRequestHeader('Content-Type','application/json');
	
	//set payload
	var payload = document.getElementById("data_input").value;
	
	//waits for the response to load
	req.addEventListener('load',function(){
		//check status
		if(req.status >= 200 && req.status < 400){
			//parse results for console
			console.log(JSON.parse(req.responseText));
			
			//populate what was sent
			document.getElementById("binSent").textContent = payload;
			
			//send results string to page
			document.getElementById("binResults").textContent = req.responseText;
		} else {
			//there was an error
			console.log("Error in network request: " + req.statusText);
		};
	});
	
	req.send(payload);//keep on truckin, since async=true!
	
	
	
}
  
  
  