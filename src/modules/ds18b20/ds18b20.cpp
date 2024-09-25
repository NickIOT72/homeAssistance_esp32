#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "ds18b20.h"

#define ds18b20_PIN  32 // Digital pin connected to the DHT sensor
OneWire oneWire(ds18b20_PIN);
DallasTemperature sensor_ds18b20(&oneWire);

struct ds18b20_module ds18b20_s1;

int ds18b20_init()
{
  ds18b20_enabled();
  sensor_ds18b20.begin();
  ds18b20_read();
  return 0;
}
int ds18b20_enabled()
{
  ds18b20_s1.enabled = true;
  return 0;
}
int ds18b20_disabled()
{
  ds18b20_s1.enabled = false;
  return 0;
}
int ds18b20_read()
{
  if( !ds18b20_s1.enabled ) return -1;
  sensor_ds18b20.requestTemperatures();
  ds18b20_s1.t = sensor_ds18b20.getTempCByIndex(0);

  if (isnan( ds18b20_s1.t  ) )  // Check if any reads failed and exit early (to try again).
  {
    Serial.println(F("Failed to read from ds18b20 sensor!"));
    return -2;
  }
 
  Serial.print(F("%  Temperature: "));
  Serial.print(ds18b20_s1.t);
  Serial.println(F("°C "));

  return 0;
}
float ds18b20_getTemp()
{
  return ds18b20_s1.t;
}