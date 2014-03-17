#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "von_neumann.h"
#include "aes.h"
#include "mersenne_twister.h"
#include "old_c_rand.h"

#define ARRAY_MAX_SIZE 1024

int main()
{
  word16 x=1111; // nombre entre 1000 et 9999 pour Von Neumann
  struct mt19937p mt; // Pour Mersenne-Twister
  int tmp = rand(), seed; // Pour Mersenne-Twister
  u32 Kx[NK], Kex[NB*NR], Px[NB]; // pour l'AES

  int output_rand; // sortie du rand du C
  word32 output_AES; // sortie pour l'AES
  word16 output_VN; // sortie pour pour Von Neumann
  word32 output_MT; // sortie pour Mersenne-Twister


  // initialisation des graines des generateurs

  srand(rdtsc());  // rand du C
  seed = rand();
  oldinit_rand(seed);
  sgenrand(time(NULL)+(tmp), &mt); // Mersenne-Twister
  // Initialisation de la clé et du plaintext pour l'AES
  // 45 est un paramètre qui doit changer à chaque initialisation
  init_rand(Kx, Px, NK, NB, 45);
  KeyExpansion(Kex,Kx); // AES : sous-clefs

  printf("Old Rand Big Endian, Old Rand Little Endian, Von Neumann, Mesrene Twister, AES\n");
  // sorties des generateurs
  for(int i = 0; i < ARRAY_MAX_SIZE; i ++) {
    output_rand = oldrand(); // rand du C
    output_VN = Von_Neumann(&x); // Von Neumann
    output_MT = genrand(&mt); // Mersenne-Twister
    output_AES = AES(Px, Kex); // AES

    printf("%u,", (output_rand >> 27) & 0x0F);
    printf("%u,", output_rand & 0x0F);
    printf("%u,", output_VN);
    printf("%u,", output_MT);
    printf("%u\n", output_AES);
  }
  return 0;
}
