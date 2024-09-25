#ifndef _WATERLEVEL_H_
#define _WATERLEVEL_H_

#include <stdint.h>

int waterLevel_init();
int waterLevel_read();
int waterLevel_enable();
int waterLevel_disable();
int waterLevel_getValue();
float waterLevel_getGainValue();
#endif // !