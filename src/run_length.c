#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "tools.h"
#define ARRAY_MAX_SIZE 1024

/**
 * @param n The number of words
 * @param size The number of bits of each word
 * @param sequence An array of words, considered as a single bit sequence
 * @return double The probability of observing this sequence
 */
double run_length(int n, int size, word32 sequence[])
{
  long nBits = (n * size);

  long numberOfOnes = 0;
  long variability = 1;
  char bit, previousBit;
  for (int i = 0; i < n; ++i)
  {
    for (int j = size - 1; j >= 0; --j)
    {
      bit = ((sequence[i] >> j) & 0x0001);
      numberOfOnes += (bit == 1 ? 1 : 0);

      if (i != 0 || j != 0)
        variability += (bit == previousBit ? 0 : 1);
      previousBit = bit;
    }
  }

  // Pre-test: proportion of bits==1 in the sequence
  double p = (numberOfOnes / (double)nBits),
         threshold = (2 / sqrt(nBits)),
         tested = fabs(p - 0.5);
  // printf("pi: %f", p);
  // printf(" tested : %f", tested);
  // printf(" threshold: %f\n", threshold);
  if (tested >= threshold)
    return 0.0;

  // Run-length test: evaluate the probability of sequences of same-valued bits occuring
  double pp = (p * (1.0 - p));
  double observed = (fabs(variability - (2 * nBits * pp)) / (2 * sqrt(2 * nBits) * pp));
  // ERFC returns the p-value of `observed`
  // (assuming it follows the normal distribution)
  return erfc(observed);
}

int main()
{
  autoseed_old_c_rand();
  autoseed_aes();
  autoseed_von_neumann();
  autoseed_mesrene_twister();

  // sorties des generateurs
  int output_rand;
  word32 generated_rand_upper[ARRAY_MAX_SIZE],
        generated_rand_lower[ARRAY_MAX_SIZE],
        generated_VN[ARRAY_MAX_SIZE],
        generated_MT[ARRAY_MAX_SIZE],
        generated_AES[ARRAY_MAX_SIZE];
  for(int i = 0; i < ARRAY_MAX_SIZE; i ++) {
    output_rand = autonext_old_c_rand(); // rand du C
    generated_rand_upper[i] = (word32) msb(output_rand);
    generated_rand_lower[i] = (word32) lsb(output_rand);
    generated_VN[i] = (word32) autonext_von_neumann(); // Von Neumann
    generated_MT[i] = (word32) autonext_mesrene_twister(); // Mersenne-Twister
    generated_AES[i] = (word32) autonext_aes(); // AES
  }

  printf("%f,%f,%f,%f,%f\n",
    run_length(ARRAY_MAX_SIZE, 4, generated_rand_upper),
    run_length(ARRAY_MAX_SIZE, 4, generated_rand_lower),
    run_length(ARRAY_MAX_SIZE, 16, generated_VN),
    run_length(ARRAY_MAX_SIZE, 32, generated_MT),
    run_length(ARRAY_MAX_SIZE, 32, generated_AES));

  return 0;
}
