#ifndef FONCTIONS_H
#define FONCTIONS_H

/*! \def PRECISION
 *  \brief Constante
 */
#define PRECISION 4096

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*! \file      fonctions.h
 *  \brief     Fichier contenant les différentes fonctions nécessaires au bon fonctionnement du programme
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

//LISTE GMP

/*! \struct elemgmp
 *  \brief Structure elemgmp qui va permettre de stocker un element dans une liste
 */
struct elemgmp{
	mpz_t val;/*!< valeur de l'élément*/
	int primalite;/*!< primalité de l'élément*/
	struct elemgmp *suiv;/*!< élément suivant*/
};

typedef struct elemgmp* listegmp;/*!< typedef de la structure */

listegmp creer_listegmp();

listegmp ajoute_elem_debutgmp(listegmp l,mpz_t i,int p);

int est_videgmp(listegmp l);

void affiche_listegmp(listegmp l);

listegmp libere_listegmp(listegmp l);

listegmp crible_era_gmp(mpz_t n);


//FONCTIONS


void pgcd(mpz_t resultat, const mpz_t a, const mpz_t b);

void expoRapide(mpz_t resultat, const mpz_t x, const mpz_t expo);

void squareAndMultiply(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul);

void decomposition(mpz_t s,mpz_t d, mpz_t nMoins1);

void genereAlea(mpz_t alea, gmp_randstate_t state, mp_bitcnt_t n);

void temoinMiller(mpz_t res, mpz_t a, mpz_t n);

int jacobiSymbol(mpz_t a, mpz_t b);

void critere_euler(mpz_t res,mpz_t random,mpz_t aTraiter);

void nombre_fermat(mpz_t res,mpz_t n);

void calculSequence(mpz_t seq, mpz_t modul, mpz_t k);

void mersen(mpz_t m, mpz_t n);

void suiteFibo(mpz_t res, mpz_t n);

void nombreLucas(mpz_t res, mpz_t n);

void nombreOr(mpf_t res);

void suiteFibo_or(mpz_t res, mpz_t n);

void suiteLucas_or(mpz_t res, mpz_t a, mpz_t n);

unsigned long int arrondi(mpf_t ent, mpf_t n);

void PolyFibo(mpz_t res,mpz_t a,mpz_t b,mpz_t n);

void calcul_discriminant(mpz_t res,mpz_t a,mpz_t b);

void PolyLucas(mpz_t res,mpz_t a,mpz_t b,mpz_t n);

// Mieux PolyLucas
void PolyLucas_or(mpz_t res,mpz_t a,mpz_t b,mpz_t n);

void chaineLucasBinaire(mpz_t u, mpz_t v, mpz_t V0, mpz_t V1, mpz_t n, mpz_t modul);

void rond(mpz_t res, mpz_t u, mpz_t v, mpz_t V1, mpz_t modul);

void etoile(mpz_t res, mpz_t u, mpz_t V0, mpz_t modul);

#endif
