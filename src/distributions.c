#include <math.h>

#include "distributions.h"
#include "tools.h"

#define MAX_AES_SIZE 4294967295

void init_distributions() {
  autoseed_aes();
}

double next_uniform_value() {
  return (double)autonext_aes()/MAX_AES_SIZE;
}

double next_exponential_value(double lambda) {
  return - (log(1 - next_uniform_value()) / lambda);
}
