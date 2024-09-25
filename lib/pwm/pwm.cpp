#include <Arduino.h>
#include "pwm.h"

int pwm_init( struct pwm_model *p )
{
  if( p->stateEnabled == PWM_NOT_ENABLED ) return -1;
  pinMode (p->pin, OUTPUT);
  pwm_set(p);
  return 0;
}

int pwm_set( struct pwm_model *p )
{
  analogWrite(p->pin, p->duty);
  return 0;
}	
int pwm_get( struct pwm_model *p )
 {
  return p->duty;
}
int pwm_setFULL( struct pwm_model *p )
{
  p->duty = 255;
  pwm_set(p );
  return 0;
}
int pwm_setOFF( struct pwm_model *p )
{
  p->duty = 0;
  pwm_set(p );
  return 0;
}