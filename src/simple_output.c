#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "tools.h"

#define ARRAY_MAX_SIZE 1000

int main()
{
	autoseed_old_c_rand();
	autoseed_aes();
	autoseed_von_neumann();
	autoseed_mesrene_twister();

	word32 output_rand = autonext_old_c_rand(); // rand du C
	word32 output_VN = autonext_von_neumann(); // Von Neumann
	word16 output_MT = autonext_mesrene_twister(); // Mersenne-Twister
	word32 output_AES = autonext_aes(); // AES

	// affichage
	printf("- Generating sample random numbers -\n");
	printf("rand du C : %u \n",output_rand);
	printf("Von Neumann : %u\n",output_VN);
	printf("Mersenne Twister : %u\n",output_MT);
	printf("AES : %u\n",output_AES);


	return 0;
}
