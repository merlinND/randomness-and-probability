#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "tools.h"
#include "distributions.h"
#define ARRAY_MAX_SIZE 10
#define LAMBDA 0.5


int main() {
  init_distributions();

  printf("- Uniform Generation -\n");
  for(int i = 0; i < ARRAY_MAX_SIZE; i ++) {
    printf("%f\n", next_uniform_value());
  }

  printf("- Exponential Generation -\n");
  for(int i = 0; i < ARRAY_MAX_SIZE; i ++) {
    printf("%f\n", next_exponential_value(LAMBDA));
  }

  return 0;
}
