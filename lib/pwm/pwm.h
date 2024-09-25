#ifndef _PWM_H_
#define _PWM_H_

#include <stdint.h>

#define PWM_ENABLED 1
#define PWM_NOT_ENABLED 0

struct pwm_model{
  uint8_t pin;
  uint16_t duty;
  bool stateEnabled;
};

int pwm_init( struct pwm_model *p );
int pwm_set( struct pwm_model *p );
int pwm_get( struct pwm_model *p );
int pwm_setON( struct pwm_model *p );
int pwm_setOFF( struct pwm_model *p );
int pwm_toogle( struct pwm_model *p );
int pwm_read( struct pwm_model *p );
#endif // !