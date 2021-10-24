/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include "mt19937ar.h"
#include <math.h>

/* initializes mt[N] with a seed */
static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) 
{ 
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 
/* These real versions are due to Isaku Wada, 2002/01/09 added */






/* -----------------------------------TP3---------------------------------- */
/* -----------------------------------Q1: R^2------------------------------ */
/*  simPi() : Calculer la const PI en utilisant la méthode de Monte-Carlo   */    
/*                                                                          */
/* En entrée: int numberOfPoints : le nombre de points utiliser dans        */
/*                                  dans l'estimation                       */
/*                                                                          */
/* En sortie: la valeur de PI                                               */    
/* ------------------------------------------------------------------------ */
double simPi(int numberOfPoints){

    //Déclaration des deux variables qu'on va appliquer l'équation R1^2 + R2^2 < 1 

    double  R1,
            R2;

    double  PI=0.;
    //boucle qui fait la faire 
    for (int i = 0; i < numberOfPoints; i++)
    {
        R1 = genrand_real1();
        R2 = genrand_real1();
        if ( pow(R1,2) + pow(R2,2) < 1 )
        {
            PI++;
        }
    }
    // printf("PI = %f\n", (PI/(double)numberOfPoints)*4);
    return (PI/(double)numberOfPoints)*4;
}

/* -----------------------------------Q2: R^2------------------------------ */
/*  diceFunction() :                                                        */    
/*                                                                          */
/* En entrée: int n : le nombre de fois qu'on lance le Dé                   */
/*                                                                          */
/* En sortie: la différence entre Pi générer et PI existe dans la library   */    
/*              math.h                                                      */    
/* ------------------------------------------------------------------------ */
double * diceFunction(int n){

    double *    T       =   calloc(30,sizeof(double));
    double      Test    =   0.;
    double      Mean    =   0;
    double      S2      =   0;

    //boucle qui permet de stocker les valeurs de pi n fois dans un tableau qui va être retourner 
    for (int i = 0; i < n; i++)
    {
        T[i] = simPi(1000);
        // printf("%f\n",T[i]);
        Mean += T[i];
    }
    
    //affichage de résultats
    printf("mean_PI : %f\n", Mean/(double) n);
    printf("M_PI : %f\n", M_PI);
    printf("mean_PI - M_PI = %f - %f = %f\n",Mean/(double) n,M_PI,Mean/(double) n-M_PI);
    return T;
}

/* -----------------------------------Q3:---------------------------------- */
/*  RayonDeConfiance() :                                                    */    
/*                                                                          */
/* En entrée: double *T : adresse du tableau                                */
/*                                                                          */
/* En sortie: le Rayon de confiance                                         */    
/*                                                                          */    
/* ------------------------------------------------------------------------ */

void RayonDeConfiance(double *T){

    double         Mean     =   0;
    double         S2       =   0;
    double         R        =   0;

    //boucle pour calculer l'espérance 
    for (int i = 0; i < 30; i++)
    {
        Mean += T[i]; 
    }
    Mean = Mean/(double) 30;

    //boucle pour calculer la variance corrigé 
    for (int i = 0; i < 30; i++)
    {
        S2 += pow(T[i] - Mean,2);
    }
    
    // 29 car c'est la variance corrigé 
    S2 = S2/29.;

    //l'erreur
    R = 2.042*sqrt(S2/30.);

    //affichage des données
    printf("R = %f\n",R );
    printf(" le Rayon de confiance : \n");
    printf(" [ X - R , X + R ]\n");
    printf(" [ %f , %f ] \n",Mean-R , Mean + R);

}