#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <stdint.h>

struct ssidList {
  char ssid[40];
  int rssi;
};

bool getAllowButton();
void setAllowButton(bool value );
int wifi_scanSSID(struct ssidList *sl, uint8_t size);
int connectAWS();
void publishMessage(String sensorInfo);
void messageHandler(char* topic, uint8_t* payload, unsigned int length);
void networkLoop();
bool returnBulbPublishStatus();
#endif // !