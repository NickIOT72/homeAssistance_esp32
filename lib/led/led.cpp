#include "led.h"
#include <Arduino.h>

int led_init( struct led_model *l )
{
  if( l->stateEnabled == LED_NOT_ENABLED ) return -1;
  pinMode (l->pin, OUTPUT);
  led_set(l);
  return 0;
}

int led_set( struct led_model *l )
{
  if( l->stateEnabled == LED_NOT_ENABLED ) return -1; 
  digitalWrite(l->pin, l->value);
  return 0;
}
int led_get( struct led_model *l )
{
  if( digitalRead(l->pin) != l->value )
  {
    l->value = digitalRead(l->pin);
    led_set(l);
  }
  return 0;
}
int led_setON( struct led_model *l )
{
  if( l->stateEnabled == LED_NOT_ENABLED ) return -1; 
  l->value = 1;
  led_set(l);
  return 0;
}
int led_setOFF( struct led_model *l )
{
  if( l->stateEnabled == LED_NOT_ENABLED ) return -1; 
  l->value = 0;
  led_set(l);
  return 0;
}
int led_toogle( struct led_model *l )
{
  if( l->stateEnabled == LED_NOT_ENABLED ) return -1; 
  l->value = !digitalRead(l->pin);
  led_set(l);
  return 0;
}
int led_read( struct led_model *l )
{
  if( l->stateEnabled == LED_NOT_ENABLED ) return -1; 
  led_get(l);
  return 0;
}	