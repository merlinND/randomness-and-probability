#ifndef VON_NEUMANN_H
#define VON_NEUMANN_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "mersenne_twister.h"
#include "aes.h"
#include "tools.h"

// cette fonction permet de connaitre la taille d�cimale d'un nombre n�cessaire pour le calcul de VON NEUMANN
int Dec_size(word32 e);
// =============================VON NEUMANN =============================
// next est au premier clock la graine et ensuite l'�tat courant du g�n�rateur de Von Neumann. La graine devra faire 4 chiffres d�cimaux.
// la sortie de la fonction est �galement un mot de 4 chiffres d�cimaux.
word16 Von_Neumann(word16 *next);

#endif
