#include <Arduino.h>
#include "network.h"
#include "keys.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

#include "../dht/dhtmod.h"
#include "../bulbLigth/bulbLigth.h"
#include "../fancooler/fancooler.h"

#define AWS_IOT_PUBLISH_TOPIC   "" // set this
#define AWS_IOT_SUBSCRIBE_TOPIC "" // set this
 
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

void wifi_cleanClientStruct(struct ssidList *sl, uint8_t size)
{
  for( int i = 0; i < size; i++ )
  {
    strcpy(sl[i].ssid, "");
    sl[i].rssi = 0;
  }
}

int wifi_scanSSID(struct ssidList *sl, uint8_t size)
{
  Serial.println("scan start");
  wifi_cleanClientStruct( sl, size );
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      (WiFi.SSID(i)).toCharArray(sl[i].ssid, 40);
      sl[i].rssi = WiFi.RSSI(i);
      delay(10);
    }
  }
  Serial.println("");
  return n;
}

int connectAWS()
{
  if( (WiFi.status() != WL_CONNECTED) ) return -1;
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return -2;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");

  return 0;
}
 
void publishMessage(String sensorInfo)
{
  char jsonBuffer[512];
  sensorInfo.toCharArray(jsonBuffer, sizeof(jsonBuffer)+1);
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
bool allowBulbPublish = false;

bool getAllowButton()
{
  return allowBulbPublish;
}
void setAllowButton(bool value )
{
  allowBulbPublish = value;
}

void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  JsonObject root = doc.as<JsonObject>();

  int statusBulb = -1;
	int statusFan = -1;
	
	Serial.println("Print Subscribe AWS status");
	for (JsonPair kv : root) {
		String parmaKey = String(kv.key().c_str());
    Serial.print(parmaKey);
		Serial.print(" : ");
    Serial.println(kv.value().as<const int>());
		if ( parmaKey == "lamp" ) statusBulb = root["lamp"];
		else if ( parmaKey == "fan" ) statusFan = root["fan"];
	}
	Serial.println("Results Json:" + String(statusBulb)+ " , " + String(statusFan));

  if ( statusBulb == 0 ) bulbLigth_OFF();
	else if (  statusBulb == 1 ) bulbLigth_ON();
	if(statusFan >= 0 )fanCooler_setDuty( statusFan );
  allowBulbPublish = true;
}

void networkLoop()
{
  //publishMessage();
  client.loop();
}