#ifndef _FANCOOLER_H_
#define _FANCOOLER_H_

#include <stdint.h>
#include <stdbool.h>

int fanCooler_init();
int fanCooler_enabled();
int fanCooler_disabled();
int fanCooler_read();
int fanCooler_setDuty( uint8_t duty);

#endif // !