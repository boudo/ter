#include "mesure.h"

/*! \file      mesure.c
 *  \brief     Fichier contenant les tests de mesures
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

/*! \fn double pow(double a, double b)
 *  \brief Fonction qui permet de calculer un nombre a la puissance b
 *  \param a : nombre a
 *  \param b : puissance b
 * 	\return a^b
 */
double pow(double a, double b) {
	if(a == 1.0 || b == 0.0) {
		return 1.0;
	} 

	return a * pow(a,b-1);
}

/*! \fn int estPremier(mpz_t nombre,int nombreIteration)
 *  \brief Fonction qui permet de dire si un nombre est premier ou non
 *  \param nombre : nombre à tester
 *  \param nombreIteration : nombre d'iterations
 * 	\return retourne 1 si premier sinon 0
 */
int estPremier(mpz_t nombre,int nombreIteration) 
{
	if(Fermat(nombre,nombreIteration) && Miller_Rabin(nombre,nombreIteration) && solovayStrassen(nombre,nombreIteration))
	{
		return 1;
	}
	
	return 0;
}

/*! \fn void generNbrPremier(mpz_t resultat, int nbrBit,int nombreIteration)
 *  \brief Fonction qui permet de generer un nombre premier
 *  \param resultat : nombre à tester
 *  \param nbrBit : nombrede bits
 *  \param nombreIteration : nombre d'iterations
 */
//fonction de generation d'un nombre prenier a n bits
void generNbrPremier(mpz_t resultat, int nbrBit,int nombreIteration) 
{
	mpz_t bornSup,bornInf,diff,exposant,exposer,alea;
	
	mpz_inits(bornSup,bornInf,diff,exposant,exposer,alea,NULL);
	
	mpz_set_ui(exposer,2);
	mpz_set_ui(exposant,nbrBit);
	
	expoRapide(bornSup,exposer,exposant);
	mpz_sub_ui(exposant,exposant,1);
	
	expoRapide(bornInf,exposer,exposant);
	mpz_sub(diff,bornSup,bornInf);
	mpz_add_ui(alea,bornInf,1);
	//gmp_printf("chiffre : %Zd\n",bornInf);
	do {
		mpz_add_ui(alea,alea,2);
		mpz_add(resultat,alea,bornInf);
	}while(!estPremier(resultat,nombreIteration));
	//gmp_printf("chiffre : %Zd\n",resultat);
	mpz_clears(bornSup,bornInf,diff,exposant,exposer,alea,NULL);
}

/*! \fn void mesureTempsFichier(char *nomFichier,int nbrIteration,int nbrBitMax)
 *  \brief Fonction qui permet d'ecrire les mesures dans un fichier
 *  \param nomFichier : nom du Fichier où seront stockés les mesures
 *  \param nbrIteration : nombre d'iterations
 *  \param nbrBitMax : nombre maximal de bit
 */

void mesureTempsFichier(char *nomFichier,int nbrIteration,int nbrBitMax) 
{
	FILE* fichier = NULL;
	fichier = fopen(nomFichier, "w");
	
 	float temps;
 	float pfermat,pmiller,pstrassen,plucasfrob;
    clock_t t1, t2;
    mpz_t bornSup,bornInf,diff,exposant,exposer,alea,delta_t,a_t,b_t,abdelta,gcd,resultat;
	mpz_inits(bornSup,bornInf,diff,exposant,exposer,alea,delta_t,a_t,b_t,abdelta,gcd,resultat,NULL);
    mpz_t nbrPremier;
    mpz_inits(nbrPremier,NULL);
    
    if(fichier != NULL)
    {
    	//fprintf(fichier,"  Fermat    Miller  Strassen   Eratos\n");
    	fprintf(fichier,"  Fermat    Miller  Strassen LucasFrob PFermat PMiller PStrassen PFrobinius Erastotene\n");
    	for(int i=1; i<=nbrBitMax; i++){
    		fprintf(fichier,"%d ", i);
    		//printf("%d : ", i);
    		
    		if(i != 1)
    		{
    			generNbrPremier(nbrPremier,i,nbrIteration);
    			//gmp_printf("%Zd\n",nbrPremier);
    		}
    		
    		else 
    		{
    			mpz_set_ui(nbrPremier,1);
    		}
    		
    		//Fermat
	    	t1 = clock();
	    	Fermat(nbrPremier,nbrIteration);
	    	t2 = clock();
	    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	    	pfermat = (float)pow(0.5,nbrIteration)*temps;
	        fprintf(fichier,"%f ", temps);
	        
	        //Miller
	        if(i != 1)
	        {
	        	t1 = clock();
		    	Miller_Rabin(nbrPremier,nbrIteration);
		    	t2 = clock();
		    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
		    	pmiller = (float)pow(0.25,nbrIteration)*temps;
	        }
	        
	        else 
	        {
	        	temps = 0.000001;
	        }
	        fprintf(fichier,"%f ", temps);
	        
	        //Solovay
	        t1 = clock();
	    	solovayStrassen(nbrPremier,nbrIteration);
	    	t2 = clock();
	    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	    	pstrassen = (float)pow(0.5,nbrIteration)*temps;
	        fprintf(fichier,"%f ", temps);
	        
	        //Lucas Frobinius

			
			/*mpz_set_ui(exposer,2);
			mpz_set_ui(exposant,i);
			
			expoRapide(bornSup,exposer,exposant);
			mpz_sub_ui(exposant,exposant,1);
			
			expoRapide(bornInf,exposer,exposant);
			mpz_sub(diff,bornSup,bornInf);
			mpz_add_ui(alea,bornInf,1);*/
			if(i>2){
				t1 = clock();
				LucasFrobenius_avecIteration(resultat, nbrPremier, nbrIteration, i);
				t2 = clock();
				temps = (float)(t2-t1)/CLOCKS_PER_SEC;
				// gmp_randstate_t state;
				// gmp_randinit_mt(state);
				// do {
				// 	gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));
				// 	mpz_urandomm (alea , state , nbrPremier);
				// 	//mpz_add_ui(alea,alea,2);
				// 	//mpz_add(a_t,alea,bornInf);
				// 	mpz_set(a_t,alea);
				// 	mpz_set_ui(b_t,1);
				// 	calcul_discriminant(delta_t,a_t,b_t);
				// 	mpz_mul(abdelta, a_t, b_t);
				// 	mpz_mul(abdelta, abdelta, delta_t);
				// 	mpz_mul_ui(abdelta, abdelta, 2);
				// 	pgcd(gcd, nbrPremier, abdelta);
				// }while(mpz_cmp_ui(gcd,1) != 0);
				// gmp_printf("gcd : %Zd \n", gcd);
				// t1 = clock();
				// LucasFrobenius(resultat, nbrPremier, a_t, b_t, delta_t);
				// t2 = clock();
				// temps = (float)(t2-t1)/CLOCKS_PER_SEC;
				// gmp_randclear(state);
			}else {
				temps = 0.000001;
			}
			plucasfrob = (float)pow((float)(1.0/7710.0),nbrIteration)*temps;
			fprintf(fichier," %f ", temps);

			fprintf(fichier, "%f ", pfermat);
			fprintf(fichier, "%f ", pmiller);
			fprintf(fichier, "%f ", pstrassen);
			fprintf(fichier, "%f ", plucasfrob);
	        //Erastothene
	        if(i > 1 && i<35){
	        	if(i != 1)
		        {
					t1 = clock();
					Eratosthene(nbrPremier);
					t2 = clock();
					temps = (float)(t2-t1)/CLOCKS_PER_SEC;
		    	}	
		    	else 
		    	{
		        	temps = 0.000001;
		        }
		        fprintf(fichier," %f\n", temps);
	        }
			else {
	        fprintf(fichier,"\n");
	        }
    	}
    	
        fclose(fichier);
    }
    mpz_clears(bornSup,bornInf,diff,exposant,exposer,alea,delta_t,a_t,b_t,abdelta,gcd,resultat,NULL);
    mpz_clears(nbrPremier,NULL);
}

/*! \fn void mesureTempsPepin(char *nomFichier,int max)
 *  \brief Fonction qui permet d'ecrire les mesures dans un fichier
 *  \param nomFichier : nom du Fichier où seront stockés les mesures
 *	\param max : nombre d'iteration max
 */
void mesureTempsPepin(char *nomFichier,int max){
	FILE* fichier = NULL;
	fichier = fopen(nomFichier, "w");
	int retour;
	mpz_t n;
    mpz_inits(n,NULL);
 	float temps;
    clock_t t1, t2;
    if(fichier != NULL){
	    fprintf(fichier,"F P   Temps\n");
	    for(int i=1; i<=max;i++){
	    	mpz_set_ui(n,i);
	    	fprintf(fichier,"%d ", i);
			t1 = clock();
			retour = Pepin(n);
			t2 = clock();
			fprintf(fichier,"%d ", retour);
			temps = (float)(t2-t1)/CLOCKS_PER_SEC;
			fprintf(fichier," %f\n", temps);
		}
		fclose(fichier);
	}
	mpz_clears(n,NULL);
}

/*! \fn void mesureTempsLucas(char *nomFichier,int max)
 *  \brief Fonction qui permet d'ecrire les mesures dans un fichier
 *  \param nomFichier : nom du Fichier où seront stockés les mesures
 *	\param max : nombre d'iteration max
 */
void mesureTempsLucas(char *nomFichier,int max){
	FILE* fichier = NULL;
	fichier = fopen(nomFichier, "w");
	int retour;
	mpz_t n;
	int i = 1;
    mpz_inits(n,NULL);
    mpz_set_ui(n,3);
	LucasLehmer(n);
 	float temps;
    clock_t t1, t2;
    if(fichier != NULL){
	    fprintf(fichier,"N P   Temps\n");
	    while(i<=max){

	    	mpz_set_ui(n,i);
	    	fprintf(fichier,"%d ", i);
			t1 = clock();
			retour = LucasLehmer(n);
			t2 = clock();
			fprintf(fichier,"%d ", retour);
			temps = (float)(t2-t1)/CLOCKS_PER_SEC;
			fprintf(fichier," %f\n", temps);
			i=i+1;
		}
		fclose(fichier);
	}
	mpz_clears(n,NULL);
}

