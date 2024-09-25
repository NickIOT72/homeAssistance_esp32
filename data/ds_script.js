function returnTwoDigits(val) {
    if (val < 10) return ("0" + val)
    else return val
}

function getCurrentTimestamp() {
    const currentDate = new Date();
    const timestamp = currentDate.getTime();
    let year = currentDate.getFullYear();
    let month = currentDate.getMonth() + 1;
    let day = currentDate.getDate();
    let hours = currentDate.getHours();
    let minutes = currentDate.getMinutes();
    let seconds = currentDate.getSeconds();
    let strDateTime = returnTwoDigits(day) + "/" + returnTwoDigits(month) + "/" + returnTwoDigits(year) + ' ' + returnTwoDigits(hours) + ":" + returnTwoDigits(minutes) + ":" + returnTwoDigits(seconds);
    return strDateTime;
}

function setDateTime() {
    document.getElementById("dateTimeVal").innerHTML = getCurrentTimestamp();
}

function updateEventList(mode, msg) {
    let actualTinme = getCurrentTimestamp();
    let classMode = mode == 1 ? "completed" : "not-completed";
    document.getElementById('eventList').innerHTML += `<li class="${classMode}"><p> ${actualTinme} => ${msg}</p></li>`
}

let objStatusSubmit = {
    bulb: 0,
    fan: 50,
    m: 0,
}

var statusProv = 0;

function getBulbStatus(objStatusS) {
    let msg = "";
    if (objStatusS.bulb >= 0) {
        if (true) {
            objStatusSubmit.bulb = objStatusS.bulb;
            if (objStatusS.bulb == 0) {
                document.getElementById('bulbSet').innerHTML = `<i class="fa-solid fa-lightbulb" style='font-size:48px;color:black'></i><span class="text"><h3>OFF</h3><p>Bedroom Lamp</p></span>`
            } else if (objStatusS.bulb == 1) {
                document.getElementById('bulbSet').innerHTML = `<i class="fa-regular fa-lightbulb" style='font-size:48px;color:yellow'></i><span class="text"><h3>ON</h3><p>Bedroom Lamp</p></span>`
            }
        }
        msg = objStatusS.bulb == 0 ? "Lamp OFF" : "Lamp ON";
    }
    if (objStatusS.fan >= 0) {
        objStatusSubmit.fan = objStatusS.fan;
        document.getElementById('fancoolerH3').innerHTML = `${objStatusS.fan}%`;
        if (objStatusS.m == 1 || objStatusS.m == 2 || objStatusS.m == 3) document.getElementById('myRangeFanCooler').value = objStatusS.fan;
        /*document.getElementById('fancooler').innerHTML = `<i class='fa-solid fa-fan' style='font-size:48px;color:black'></i>
					<span class="text">
						<h3>${objStatusS.fan}</h3>
						<p>Fan Cooler Bedroom</p>
                        <div class="slidecontainer">
						  <input type="range" min="0" max="100" value="${objStatusS.fan}" class="slider" id="myRangeFanCooler">
						</div>
					</span>`*/
        msg += ` , Fan Cooler ${objStatusS.fan}`;
    }
    msg += objStatusS.m == 2 || objStatusS.m == 3 ? " [MQTT publish] " : "";
    if (objStatusS.m == 1 || objStatusS.m == 2 || objStatusS.m == 3) updateEventList(1, msg);
}

//let sensorl = 0;
//
//let sensorLimits = {
//    temp: [20, 30, 40],
//    hum: [50, 80, 95],
//    water: [20, 50, 80]
//}
//
//let sensorObj = {
//    temp: 20,
//    hum: 50,
//    water: 20
//}

function getParamStatus(sensorObj) {
    let tempColor = sensorObj.temp < 25 ? 'blue' : sensorObj.temp >= 25 && sensorObj.temp <= 75 ? 'black' : 'red'
    let tempIcon = sensorObj.temp < 25 ? "fa-solid fa-temperature-low" : sensorObj.temp >= 25 && sensorObj.temp <= 75 ? "fa-solid fa-temperature-half" : "fa-solid fa-temperature-high";
    document.getElementById('tempCard').innerHTML = `<i class='${tempIcon}' style='font-size:48px;color:${tempColor}'></i>
					<span class="text">
						<h3>${sensorObj.temp}ºC</h3>
						<p>Bedroom Temperature</p>
					</span>`
    let humColor = sensorObj.hum < 75 ? 'blue' : 'black'
    let humIcon = sensorObj.hum < 75 ? "fa-solid fa-temperature-arrow-down" : "fa-solid fa-temperature-arrow-up";
    document.getElementById('humCard').innerHTML = `<i class="${humIcon}" style='font-size:48px;color:${humColor}'></i>
					<span class="text">
						<h3>${sensorObj.hum}%</h3>
						<p>Bedroom Humidity</p>
					</span>`
    let waterColor = sensorObj.water < 25 ? 'red' : sensorObj.water >= 25 && sensorObj.water <= 75 ? 'black' : 'green'
    document.getElementById('waterCard').innerHTML = `<i class="fa-solid fa-water" style='font-size:48px;color:${waterColor}'></i>
					<span class="text">
						<h3>${sensorObj.water}%</h3>
						<p>Water Tank Level</p>
					</span>`
    tempColor = sensorObj.tempds < 25 ? 'blue' : sensorObj.tempds >= 25 && sensorObj.tempds <= 75 ? 'black' : 'red'
    tempIcon = sensorObj.tempds < 25 ? "fa-solid fa-temperature-low" : sensorObj.tempds >= 25 && sensorObj.tempds <= 75 ? "fa-solid fa-temperature-half" : "fa-solid fa-temperature-high";
    document.getElementById('tempDSCard').innerHTML = `<i class='${tempIcon}' style='font-size:48px;color:${tempColor}'></i>
					<span class="text">
						<h3>${sensorObj.tempds}ºC</h3>
						<p>Temperature Living Room</p>
					</span>`
        //sensorl += 1;
        //sensorl %= 3;
        //sensorObj.temp = sensorLimits.temp[sensorl];
        //sensorObj.hum = sensorLimits.hum[sensorl];
        //sensorObj.water = sensorLimits.water[sensorl];

    let msg = `Bedroom Temperature: ${sensorObj.temp}ºC,Bedroom Humidity: ${sensorObj.hum}%, Water Tank Level: ${sensorObj.water}%, Living Room Temperature: ${sensorObj.tempds}°C`
    updateEventList(0, msg)
}

function initDashboard() {
    //document.addEventListener("DOMContentLoaded", function(event) {
    setDateTime();
    // requestSensorData();
    //código a ejecutar cuando existe la certeza de que el DOM está listo para recibir acciones
    setInterval(setDateTime, 500);
    objStatusSubmit.m = 0;
    sendBulbLigthStatus(objStatusSubmit)
        //statusProv = (statusProv + 1) % 2;
    requestSensorsData();
    //setInterval(requestSensorData, 500);
    document.getElementById('bulbSet')
        .addEventListener('click', function(event) {
            // do something
            console.log('Bulb set clicked');
            objStatusSubmit.bulb = (objStatusSubmit.bulb + 1) % 2;
            let objBulb = {
                bulb: objStatusSubmit.bulb,
                m: 1
            }
            objStatusSubmit.m = 0;
            sendBulbLigthStatus(objBulb)
        });
    document.getElementById('myRangeFanCooler')
        .addEventListener('click', function(event) {
            // do something
            console.log('fancooler set clicked');
            objStatusSubmit.fan = event.target.value; //(objStatusSubmit.fan + 10) % 255;
            let objBulb = {
                fan: objStatusSubmit.fan,
                m: 1
            }
            objStatusSubmit.m = 0;
            sendBulbLigthStatus(objBulb)
        });
    setInterval(function() { requestSensorsData() }, 5000);
    setInterval(function() {
        objStatusSubmit.m = 0;
        sendBulbLigthStatus(objStatusSubmit)
    }, 1000); /**/
    //});
}