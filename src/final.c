#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "tests.h"

#define MAX_TRIES 20
#define ARRAY_MAX_SIZE 1024

#define CSV_HEADER "Oldrand 4 MSBs,Oldrand 4 LSBs,Von-Neumann,Mesrene-Twister,AES\n"

int main()
{
  printf("# Random Number Generation & Probability Distributions\n\n");

  printf("## Random Number Testing\n\n");
  autoseed_old_c_rand();
  autoseed_aes();
  autoseed_von_neumann();
  autoseed_mesrene_twister();
  for(int i = 1; i <= MAX_TRIES; i ++) {
    word32 generated_rand_upper[ARRAY_MAX_SIZE],
          generated_rand_lower[ARRAY_MAX_SIZE],
          generated_VN[ARRAY_MAX_SIZE],
          generated_MT[ARRAY_MAX_SIZE],
          generated_AES[ARRAY_MAX_SIZE];

    printf("### Try %d\n\n", i);

    printf("#### %d generated numbers\n\n", ARRAY_MAX_SIZE);
    printf("```\n");
    printf(CSV_HEADER);
    for(int j = 0; j < ARRAY_MAX_SIZE; j ++) {
      int output_rand = autonext_old_c_rand();
      generated_rand_upper[j] = (word32) msb(output_rand);
      generated_rand_lower[j] = (word32) lsb(output_rand);
      generated_VN[j] = (word32) autonext_von_neumann(); // Von Neumann
      generated_MT[j] = (word32) autonext_mesrene_twister(); // Mersenne-Twister
      generated_AES[j] = (word32) autonext_aes(); // AES

      printf("%u,", generated_rand_upper[j]);
      printf("%u,", generated_rand_lower[j]);
      printf("%u,", generated_VN[j]);
      printf("%u,", generated_MT[j]);
      printf("%u\n",generated_AES[j]);
    }
    printf("```\n\n");

    printf("#### Monobit Frequency Test\n\n");

    printf(" - Old C Rand 4 MSBs: %f\n", frequency(ARRAY_MAX_SIZE, 4, generated_rand_upper));
    printf(" - Old C Rand 4 LSBs: %f\n", frequency(ARRAY_MAX_SIZE, 4, generated_rand_lower));
    printf(" - Von Neumann: %f\n", frequency(ARRAY_MAX_SIZE, 4, generated_VN));
    printf(" - Mesrene Twister: %f\n", frequency(ARRAY_MAX_SIZE, 4, generated_MT));
    printf(" - AES: %f\n\n", frequency(ARRAY_MAX_SIZE, 4, generated_AES));

    printf("#### Runs Length Test\n\n");

    printf(" - Old C Rand 4 MSBs: %f\n", run_length(ARRAY_MAX_SIZE, 4, generated_rand_upper));
    printf(" - Old C Rand 4 LSBs: %f\n", run_length(ARRAY_MAX_SIZE, 4, generated_rand_lower));
    printf(" - Von Neumann: %f\n", run_length(ARRAY_MAX_SIZE, 4, generated_VN));
    printf(" - Mesrene Twister: %f\n", run_length(ARRAY_MAX_SIZE, 4, generated_MT));
    printf(" - AES: %f\n\n", run_length(ARRAY_MAX_SIZE, 4, generated_AES));
  }
  return 0;
}
