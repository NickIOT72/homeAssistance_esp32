#ifndef  _ADC_H_
#define _ADC_H_

#include <stdint.h>
#include <stdbool.h>

#define ADC_ENABLED 1
#define ADC_NOT_ENABLED 0

struct adc_model{
  uint8_t pin;
  uint16_t value;
  float gain;
  float gainResult;
  bool enabled;
};

int adc_init( struct adc_model *ad );
int adc_read( struct adc_model *ad );
int adc_convert( struct adc_model *ad );

#endif // !