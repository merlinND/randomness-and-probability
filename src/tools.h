#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>

typedef uint32_t word32;
typedef uint16_t word16;
typedef uint8_t word8;

void autoseed_old_c_rand();

void autoseed_aes();

void autoseed_von_neumann();

void autoseed_mesrene_twister();

word32 autonext_old_c_rand();

word32 autonext_aes();

word16 autonext_von_neumann();

word32 autonext_mesrene_twister();

word8 msb(int word);

word8 lsb(int word);

#endif
