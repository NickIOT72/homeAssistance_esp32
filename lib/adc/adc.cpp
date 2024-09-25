#include "adc.h"
#include <Arduino.h>

int adc_init( struct adc_model *ad )
{
  if ( ad->enabled == ADC_NOT_ENABLED ) return -2;
  adc_read(ad);
  if ( ad->gain != 1 ) adc_convert(ad);
  return 0;
}
int adc_read( struct adc_model *ad )
{
  if ( ad->enabled == ADC_NOT_ENABLED ) return -2;
  ad->value = analogRead(ad->pin);
  return 0;
}
int adc_convert( struct adc_model *ad )
{
  if ( ad->enabled == ADC_NOT_ENABLED ) return -2;
  ad->gainResult = ad->gain*ad->value;
  return 0;
}