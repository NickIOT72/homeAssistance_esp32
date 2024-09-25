#include <Arduino.h>
#include "modules/network/esp_mango.h"
#include <EEPROM.h>

const char* NETWORK_NAME = "ESP32_NETWORK";
const char* PASSWORD = "12345678";

#define homeESP32 "homeESP32"
#define WIFI_PIN 2

unsigned long tstartWifi = 0;
#define DELAY_WIIFI 5000

bool WiFiConection(String ssid , String password)
{	
	WiFi.mode(WIFI_STA);
	char ssid_char[40];
	char pwd_char[40];
	ssid.toCharArray(ssid_char , 40);
	password.toCharArray(pwd_char , 40 );
	WiFi.disconnect();
  WiFi.begin(ssid_char, pwd_char);

  Serial.println("Connecting to Wi-Fi");
	uint16_t countSSID = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
		digitalWrite( WIFI_PIN , !digitalRead( WIFI_PIN ) );
		countSSID += 1;
		if ( countSSID % 5 == 0)
		{
			Serial.print(".");
		}
		if( countSSID == 50) break;
  }
	if ( WiFi.status() != WL_CONNECTED   )
	{
		Serial.println("Couldn't connect to ");
		Serial.print(ssid_char);
		Serial.println("");
		digitalWrite( WIFI_PIN , LOW);
	}
	else{
		Serial.print("Successfully Connectted to ");
		Serial.print(ssid_char);
		Serial.println("");
		digitalWrite( WIFI_PIN , HIGH);
	}
	return WiFi.status() == WL_CONNECTED;
}

void scanSpiffs()
{
	if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
 
  File root = SPIFFS.open("/");
 
  File file = root.openNextFile();
 
  while(file){
 
      Serial.print("FILE: ");
      Serial.println(file.name());
 
      file = root.openNextFile();
  }
}

void setup() {
	Serial.begin(115200);
	EEPROM.begin(512);
	WiFi.mode(WIFI_AP);
	pinMode(WIFI_PIN , OUTPUT);
	digitalWrite( WIFI_PIN , LOW);
	dht_init();
	waterLevel_init();
	bulbLigth_init();
	ds18b20_init();
	fanCooler_init();
	int eepromByteCredentials = EEPROM.read(101);
	bool isConnected = false;
	if ( eepromByteCredentials == 49 ){
		String ssid_str = "";
		String pwd_str = "";
		for(int i=0; i< 50 ; i++){
			if ( EEPROM.read(i) != 0) ssid_str += (char)EEPROM.read(i);
			if ( EEPROM.read(i+50) != 0) pwd_str += (char)EEPROM.read(i +50);
		}
		Serial.print("ssid_str: ");
		Serial.print(ssid_str);
		Serial.print(" , pwd_str: ");
		Serial.println(pwd_str);
		isConnected = WiFiConection(ssid_str , pwd_str);
	}
	if ( !isConnected )
	{
		for(int i = 0; i < 200 ; i++) EEPROM.writeByte(i, 0);
		EEPROM.commit();
		WiFi.disconnect();
		WiFi.mode(WIFI_AP);
		WiFi.softAP(NETWORK_NAME,PASSWORD);
		Serial.println("\nAccess Point mode");
		Serial.println(WiFi.softAPIP());
	}
	else{
		int err = connectAWS();
		if ( err != 0 )
		{
      Serial.println("Error connecting to AWS");
			while (1) delay(1);
    }
	}

	//scanSpiffs();
	//while(1){delay(1);}

	//loop2_ESP8266_period = 10000; //UNCOMMENT IF YOU ARE USING ESP8266
	startESPMangoServer(homeESP32);
	tstartWifi = millis();
}


void loop() {
	ESPMangoLoop();
	if (millis() - tstartWifi >= DELAY_WIIFI)
	{
		if( WiFi.status() != WL_CONNECTED && EEPROM.read(101) == 49 ) ESP.restart();
    else tstartWifi = millis();
	}
}

/*
	If you are using an ESP32 Based board, loop2() runs in the second core, so it's a parallel loop, and works like that.
	If you are using an ESP8266 Based board, loop2() runs as a ticker callback, so the function will be called each "loop2_ESP8266_period"
	milliseconds (YOU HAVE TO DEFINE THAT VARIABLE BEFORE "startESPMangoServer()") and delay functions will be ignored.
*/
void loop2() {
	delay(1);// delay for stability. If you are using ESP8266 based board delete this delay.
}

