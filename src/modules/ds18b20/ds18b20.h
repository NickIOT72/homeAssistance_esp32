#ifndef _DS18B20_H_
#define _DS18B20_H_

#include <stdint.h>
#include <stdbool.h>

struct ds18b20_module
{
  float t;
  bool enabled;
};


int ds18b20_init();
int ds18b20_enabled();
int ds18b20_disabled();
int ds18b20_read();
float ds18b20_getTemp();

#endif // !