#include "tests.h"

#include <math.h>

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
  
  if (tested >= threshold)
    return 0.0;

  // Run-length test: evaluate the probability of sequences of same-valued bits occuring
  double pp = (p * (1.0 - p));
  double observed = (fabs(variability - (2 * nBits * pp)) / (2 * sqrt(2 * nBits) * pp));
  // ERFC returns the p-value of `observed`
  // (assuming it follows the normal distribution)
  return erfc(observed);
}

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
