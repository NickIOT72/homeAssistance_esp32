#include "waterLevel.h"
#include <adc.h>

/****
 * Water Level Sensor
 */
const uint8_t waterLevelPin = 34;
const float waterLevelGain = 100/1023;
struct adc_model water_level = { waterLevelPin, 0 ,waterLevelGain ,0 , ADC_ENABLED };


int waterLevel_init()
{
  waterLevel_enable();
  adc_init(&water_level);
  return 0;
}
int waterLevel_read()
{
  if ( water_level.enabled == ADC_NOT_ENABLED ) return -1;
  adc_read(&water_level);
  adc_convert(&water_level);
  return 0;
}
int waterLevel_enable()
{
  water_level.enabled = ADC_ENABLED;
  return 0;
}
int waterLevel_disable()
{
  water_level.enabled = ADC_NOT_ENABLED;
  return 0;
}

int waterLevel_getValue()
{
  return water_level.value;
}
float waterLevel_getGainValue()
{ 
  return water_level.gainResult;
}