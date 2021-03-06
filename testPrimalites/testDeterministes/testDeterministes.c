#include "testDeterministes.h"

/*! \file      testDeterministes.c
 *  \brief     Fichier contenant les différents tests probabilistes
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

 /*!\fn int Eratosthene(mpz_t n)
 *  \brief Fonction Deterministe qui utilise le crible d'erastothene pour dire si un nombre est premier ou non
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé et -1 si erreur
 */
int Eratosthene(mpz_t n)
{
	//Si n < 2
	if (mpz_cmp_ui(n, 2) < 0)
	{
		return -1;
	}
	
	//Si n = 2
	if (mpz_cmp_ui(n, 2) == 0)
	{
		return 1;
	}

	mpz_t racine_n,finalteDiv,nmoins1;
	mpz_inits(racine_n,finalteDiv,nmoins1,NULL);

	//Liste des nombfinal premiers < à racine_n
	mpz_sqrt(racine_n,n);
	listegmp premier = creer_listegmp();
	
	if(mpz_cmp_ui(n,3)==0)//Cas pour 3
	{
		mpz_sub_ui(nmoins1,n,1);
		premier = crible_era_gmp(nmoins1);
	}
	else
	{
		premier = crible_era_gmp(racine_n); 
	}

	//On teste si chacun de ces nombfinal premiers / n
	listegmp tmp = premier;

	while (tmp->val != NULL)
	{
		if (tmp->primalite == 1)
		{
			mpz_mod(finalteDiv,n,tmp->val);
			
			//Cas quand composé
			if (mpz_cmp_ui(finalteDiv,0) == 0 ) 
			{
				mpz_clears(finalteDiv, racine_n,nmoins1, NULL);
				libere_listegmp(premier);
				return 0;
			}
		}
		tmp = tmp->suiv;
	}
		
	//Cas quand 1er
	mpz_clears(finalteDiv,racine_n,nmoins1,NULL);
	libere_listegmp(premier);
	return 1;
}

/*! \fn int Pepin(mpz_t n)
 *  \brief Fonction Test De Pepin
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé
 */
int Pepin(mpz_t n)
{
	mpz_t Fn,trois,Ce,FnMoins1;
	mpz_inits(Fn,trois,Ce,FnMoins1,NULL);
	
	mpz_set_ui(trois,3);
	
	nombre_fermat(Fn,n);
	mpz_sub_ui(FnMoins1,Fn,1);
	
	//gmp_printf("testfnbrfermat=%Zd\n",Fn);
	
	critere_euler(Ce,trois,Fn);
	//gmp_printf("testCe=%Zd\n",Ce);
	
	if(mpz_cmp(Ce,FnMoins1) == 0)
	{
		mpz_clears(Fn,trois,Ce,FnMoins1,NULL);
		return 1;
	}
	
	mpz_clears(Fn,trois,Ce,FnMoins1,NULL);
	return 0;

}

/*! \fn int LucasLehmer(mpz_t n)
 *  \brief Fonction Test De Lucas pour les ombre de Mersen
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé
 */
int LucasLehmer(mpz_t n) // on a n impaire, on veut savoir si 2^n - 1 est premier
{
	mpz_t pair;
	mpz_init(pair);
	mpz_mod_ui(pair,n,2);
	if (mpz_cmp_ui(pair,0) == 0)
	{ // SI n % 2 est egale a 0
		mpz_clear(pair);
		return 0;
	}
	// initialisation
	mpz_t seq, mers, deux, k;
	mpz_inits(seq, mers, deux, k, NULL);
	mpz_set_ui(deux, 2);
	// calcul de la sequence
	mersen(mers, n);
	mpz_sub_ui(k, n, 2);
	// gmp_printf("k = %Zd\n", k);
	calculSequence(seq, mers, k);
	// test du finalultat de le sequence
	if( mpz_cmp_ui(seq, 0) == 0)
	{
		// gmp_printf("%Zd est 1er\n", mers);
		mpz_clears( seq, mers, deux, pair, k, NULL);
		return 1;
	}

	// gmp_printf("%Zd est composé\n", mers);
	mpz_clears(seq, mers, deux, pair, k, NULL);
	return 0;
}
