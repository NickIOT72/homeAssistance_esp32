#include <Arduino.h>
#include "dhtmod.h"

#include "DHT.h"

#define DHTPIN 14  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

struct dth_module dth_s1;

DHT dht(DHTPIN, DHTTYPE);

int dht_init()
{
  dht_enabled();
  dht.begin();
  dht_read();
  return 0;
}
int dht_enabled()
{
  dth_s1.enabled = true;
  return 0;
}
int dht_disabled()
{
  dth_s1.enabled = false;
  return 0;
}
int dht_read()
{
  if( !dth_s1.enabled ) return -1;
  dth_s1.h = dht.readHumidity();
  dth_s1.t = dht.readTemperature();

  if (isnan( dth_s1.h ) || isnan( dth_s1.t  ) )  // Check if any reads failed and exit early (to try again).
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return -2;
  }
 
  Serial.print(F("Humidity: "));
  Serial.print(dth_s1.h );
  Serial.print(F("%  Temperature: "));
  Serial.print(dth_s1.t);
  Serial.println(F("°C "));

  return 0;
}
float dht_getTemp()
{
  return dth_s1.t;
}
float dht_getHum()
{
  return dth_s1.h;
}