#include "bulbLigth.h"
#include <led.h>

/****
 * Fan Cooler 
 */
const int bulbLigthPin = 23;
struct led_model bulbLigth = { bulbLigthPin , 0, LED_ENABLED };

int bulbLigth_init()
{
  bulbLigth_enable();
  led_init(&bulbLigth);
  bulbLigth.value ? bulbLigth_ON(): bulbLigth_OFF();
  return 0;
}
int bulbLigth_ON()
{
  led_setON(&bulbLigth);
  return 0;
}
int bulbLigth_OFF()
{
  led_setOFF(&bulbLigth);
  return 0;
}
int bulbLigth_Toogle()
{
  led_toogle(&bulbLigth);
  return 0;
}
int bulbLigth_enable()
{
  bulbLigth.stateEnabled = LED_ENABLED;
  return 0;
}	
int bulbLigth_disable()
{
  bulbLigth.stateEnabled = LED_NOT_ENABLED;
  return 0;
}	
int bulbLigth_Read()
{
  led_read(&bulbLigth);
  return bulbLigth.value;
}