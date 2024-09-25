#ifndef _DHTMOD_H_
#define _DHTMOD_H_

#include <stdint.h>
#include <stdbool.h>

struct dth_module
{
  float h ;
  float t;
  bool enabled;
};


int dht_init();
int dht_enabled();
int dht_disabled();
int dht_read();
float dht_getTemp();
float dht_getHum();

#endif // !