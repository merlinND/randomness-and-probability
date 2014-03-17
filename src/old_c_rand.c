#include "old_c_rand.h"

#define OLDRAND_MAX 2147483647

static int next;

int rdtsc()
{
  // cette fonction suivante cree un warning : c'est normal.
  __asm__ __volatile__("rdtsc");
}

void oldinit_rand(int seed)
{
  next = seed;
}

int oldrand()
{
  next = next * 1103515245 + 12345;
  return (unsigned int)(next % OLDRAND_MAX);
}
