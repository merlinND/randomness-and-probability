#include <stdlib.h>
#include <stdio.h>
#include "tools.h"


#define ARRAY_MAX_SIZE 1024

int main()
{
  int output_rand;
  word32 output_AES;
  word16 output_VN;
  word32 output_MT;

  autoseed_old_c_rand();
  autoseed_aes();
  autoseed_von_neumann();
  autoseed_mesrene_twister();

  printf("Old Rand Big Endian, Old Rand Little Endian, Von Neumann, Mesrene Twister, AES\n");
  // sorties des generateurs
  for(int i = 0; i < ARRAY_MAX_SIZE; i ++) {
    output_rand = autonext_old_c_rand(); // rand du C
    output_VN = autonext_von_neumann(); // Von Neumann
    output_MT = autonext_mesrene_twister(); // Mersenne-Twister
    output_AES = autonext_aes(); // AES

    printf("%u,", (output_rand >> 27) & 0x0F);
    printf("%u,", output_rand & 0x0F);
    printf("%u,", output_VN);
    printf("%u,", output_MT);
    printf("%u\n",output_AES);
  }
  return 0;
}
