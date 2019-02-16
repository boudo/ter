#ifndef TESTPROBABILISTES_H
#define TESTPROBABILISTES_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

#include "../liste/liste.h"
#include "../fonctions/fonctions.h"

int Fermat(mpz_t n, int iter);

void Miller_Rabin(mpz_t n, int rep);

void temoinMiller(mpz_t res, mpz_t a, mpz_t n);



#endif