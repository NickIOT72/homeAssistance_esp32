#include "fancooler.h"
#include <pwm.h>

#define FAN_COOLER_PWM_PIN 16

struct pwm_model fanCool = { FAN_COOLER_PWM_PIN , 0 , PWM_ENABLED};

int fanCooler_init()
{
  pwm_init(&fanCool);
  return 0;
}

int fanCooler_enabled()
{
  fanCool.stateEnabled = PWM_ENABLED;
  return 0;
}
int fanCooler_disabled()
{
  fanCool.stateEnabled = PWM_NOT_ENABLED;
  return 0;
}
int fanCooler_read()
{
  return fanCool.duty;
}
int fanCooler_setDuty(uint8_t duty)
{
  fanCool.duty = duty;
  pwm_set(&fanCool);
  return 0;
}	
