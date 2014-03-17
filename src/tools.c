#include "tools.h"

#include <time.h>

#include "von_neumann.h"
#include "aes.h"
#include "mersenne_twister.h"
#include "old_c_rand.h"

static word16 x; // nombre entre 1000 et 9999 pour Von Neumann
static struct mt19937p mt; // Pour Mersenne-Twister
static int seed; // Pour Mersenne-Twister
static u32 Kx[NK], Kex[NB*NR], Px[NB]; // pour l'AES

void autoseed_old_c_rand() {
  srand(rdtsc());
  seed = rand();
  oldinit_rand(seed);
}

void autoseed_aes() {
  init_rand(Kx, Px, NK, NB, 45);
  KeyExpansion(Kex,Kx);
}

void autoseed_von_neumann() {
  x=1111;
}

void autoseed_mesrene_twister() {
  int tmp = rand();
  sgenrand(time(NULL)+(tmp), &mt);
}

int autonext_old_c_rand() {
  return oldrand();
}

word32 autonext_aes() {
  return AES(Px, Kex);
}

word16 autonext_von_neumann() {
  return Von_Neumann(&x);
}

word32 autonext_mesrene_twister() {
  return genrand(&mt);
}
