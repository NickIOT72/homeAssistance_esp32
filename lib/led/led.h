#ifndef _LED_H_
#define _LED_H_

#include <stdint.h>

#define LED_ENABLED 1
#define LED_NOT_ENABLED 0

struct led_model{
  uint8_t pin;
  uint16_t value;
  bool stateEnabled;
};

int led_init( struct led_model *l );
int led_set( struct led_model *l );
int led_get( struct led_model *l );
int led_setON( struct led_model *l );
int led_setOFF( struct led_model *l );
int led_toogle( struct led_model *l );
int led_read( struct led_model *l );
#endif // !