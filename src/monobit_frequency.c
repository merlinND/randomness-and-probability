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
double frequency(int n, int size, word32 sequence[])
{
  long sum = 0;
  char bit;
  for (int i = 0; i < n; ++i)
  {
    for (int j = size - 1; j >= 0; --j)
    {
      bit = ((sequence[i] >> j) & 0x0001);
      sum += (bit == 0 ? -1 : 1);
    }
  }

  double observed = (abs(sum) / sqrt(n * size));
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
    frequency(ARRAY_MAX_SIZE, 4, generated_rand_upper),
    frequency(ARRAY_MAX_SIZE, 4, generated_rand_lower),
    frequency(ARRAY_MAX_SIZE, 16, generated_VN),
    frequency(ARRAY_MAX_SIZE, 32, generated_MT),
    frequency(ARRAY_MAX_SIZE, 32, generated_AES));

  return 0;
}
