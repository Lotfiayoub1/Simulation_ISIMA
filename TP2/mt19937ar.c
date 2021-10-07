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

/* initializes mt[N] with a seed */
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




/* -------------------------------------------------------------------- */
/* -------------------------------------Q2: a-------------------------- */
/* uniform :  générer 1000 nombres aléatoire entre deux réels.          */
/*                                                                      */
/* En entrée: min, max Deux nombres réels.                              */
/*                                                                      */
/* En sortie: afficher 1000 nombres aléatoire entre a et b.             */
/* -------------------------------------------------------------------- */
void uniform(double min, double max){

    //message explicatif pour les pseudo-random numbers qui s'affiche dans le terminal.
    printf("\n1000 outputs of random pseudo-random numbers between %lf and %lf\n\n", min , max);
    for (int i=0; i<1000; ++i)
    {   
        //affichage du nombre aléatoire générer entre le min et le max.
        printf("%10.8f ", (genrand_real2() * (max - min + 1))+min);
        if (i%5==4) printf("\n");
    }
}


/* ------------------------------------------------------------------------ */
/* -------------------------------------Q3: a------------------------------ */
/* discrete_empirical_distributions : Calculer de la probabilités cumulées  */
/*                                    pour les trois classes A,B et C.      */
/*                                                                          */
/* En entrée: void                                                          */
/*                                                                          */
/* En sortie: le poucentage obtenu pour chaque cas                          */
/*            si le nombre aléatoir est < 0.5 en cumule dans la calsse A    */
/*            si le nombre aléatoir est < 0.6 en cumule dans la calsse B    */
/*            sinon  en cumule dans la classe C                             */
/*            On affiche le pourcentage obtenu pour chaque classe           */
/* ------------------------------------------------------------------------ */
void discrete_empirical_distributions(){
    
    //la déclaration des trois classes et les initialisées avec 0
    int     A   =   0,
            B   =   0,
            C   =   0;


    int     iteration;

    printf("\nC'est la question a de l'exercice 3\n");
    printf("Entrer le nombre de iteration : ");
    scanf("%d",&iteration);
    int sum = 0;
    double random_number;
    for (int i = 0; i < iteration; i++)
    {
        random_number = genrand_real3() ;
        printf("%f  --  ",random_number);
        if (i%5==4) printf("\n");
        if (random_number < 0.5){
            A++;
        }else if (random_number < 0.6)
        {
            B++;
        }else{
            C++;
        }
            
    }
    printf("\nnumber of A is %d the percentage obtained for Class A is : %lf\n",A,(A/(double)iteration));
    printf("number of B is %d  the percentage obtained for Class B is : %lf\n",B,(B/(double)iteration));
    printf("number of C is %d  the percentage obtained for Class C is : %lf\n",C,(C/(double)iteration));

    sum = ((A+B+C)/(double)iteration);
    printf("the sum of the percentages is : %d\n",sum );
    
}

/* ------------------------------------------------------------------------ */
/* -------------------------------------Q3: b------------------------------ */
/*  generic_function() : generic function qui prend des paramètre           */    
/*                                                                          */
/* En entrée: ClasseSize    - un entier qui représente  la taille           */ 
/*                            la taille du tableau des classes              */
/*            ClasseArray[] - tableau contient le nombre d'individus        */
/*                            observés dans chaque classe                   */
/*                                                                          */
/* En sortie: le poucentage obtenu pour chaque cas                          */
/*            si le nombre aléatoir est < 0.5 en cumule dans la calsse A    */
/*            si le nombre aléatoir est < 0.6 en cumule dans la calsse B    */
/*            sinon  en cumule dans la classe C                             */
/*            On affiche le pourcentage obtenu pour chaque classe           */    
/* ------------------------------------------------------------------------ */

double *generic_function(int ClasseSize, int IndividualsObservedInEachClass[]){

    double          proba[ClasseSize];
    double       *  Cumulatif           =   calloc(ClasseSize, sizeof(double));
    int             TotalOfObservation  =   0;

    //Calculer le totale des observations
    for (int i = 0; i < ClasseSize; i++)
    {
        TotalOfObservation += IndividualsObservedInEachClass[i]; 
    }

    //Remplir le tableau des cumulatifs
    for (int i = 0; i < ClasseSize; i++)
    {
        proba[i] = IndividualsObservedInEachClass[i]/(double) TotalOfObservation; 
        // printf("Proba[%d] = %d/%d = %f\n",i,IndividualsObservedInEachClass[i],TotalOfObservation,proba[i]);
        if (i == 0)
        {
            Cumulatif[i] = proba[i];
            // printf("%f\n",Cumulatif[i]);
        }
        else
        {

            Cumulatif[i] = Cumulatif[i-1]+proba[i];
            // printf("%f\n",Cumulatif[i]);
        }
    }
    return Cumulatif;
}

/* ------------------------------------------------------------------------ */
/* -------------------------------------Q3: b------------------------------ */
/*  generic_affichage() : qui permet d'afficher le tableau cumulatif qui    */
/*                        est calculer par la fonction generic_function()   */    
/*                                                                          */
/* En entrée: Cumulatif []  - un tableau de double qui contient les         */ 
/*                             cumulatifs                                   */
/*                                                                          */
/* En sortie: affichage du tableau en entrer                                */
/*            ps: la dérniere case doit être égale à 1 pour qu'il soit      */
/*                une  loi de probabilité                                   */
/* ------------------------------------------------------------------------ */
void generic_affichage(double *cumulatifs){

    printf("\nC'est la question b de l'exercice 3\n");
    for (int i = 0; i <6 ; i++)
    {
        printf("            C[%i] = %f\n",i,cumulatifs[i]);
    }
    
}



/* ------------------------------------------------------------------------ */
/* -------------------------------------Q4: a------------------------------ */
/*  negExp() : Negative exponential law(Average)                            */
/*                                                                          */
/*  En entrée : Mean                                                        */
/*                                                                          */
/*  En Sortie : un réel                                                     */
/* ------------------------------------------------------------------------ */

double negExp(double Mean){

    return -Mean*log( 1 - genrand_real3());
}

/* ------------------------------------------------------------------------ */
/* -------------------------------------Q4: b------------------------------ */
/*  test20bins() :  calcule la fréquence des nombres génerer entre          */
/*                  [0,1];[1,2] ...[19,20] par la fonction negExp           */
/*                                                                          */
/*  En entrée :   void                                                      */
/*                                                                          */
/*  En Sortie : affichage du Number of occurence Frequence et l'accumulation*/
/* ------------------------------------------------------------------------ */
void test20bins(){


    int     Test20bins[21]  =   {0};
    double  frequency[21]   =   {0.};
    double  accumulate[21]  =   {0.};

    //remplir le tableau des test20bins
    for (int i=0; i<1000000; ++i)
    {
        double negd = negExp(10.);
        int neg = (int) negd;
        // neg<20? neg : 20 {'explication : if neg < 20 tu vas ajouter dans la case |neg| else tu vas ajouter dans la case 20'}
        (Test20bins[neg<20? neg : 20]) ++;
    }
        printf("\n\nNumber\tFrequency\tAccumulation\n");

        // affectation des premiers valeurs de frequency et accumulate pour qu'on puisse commencer a calculer le reste on se basent sur ces valeurs
        frequency[0] = (double) Test20bins[0]/1000000;
        accumulate[0] = frequency[0];
        printf("%d\t%lf\t%lf\n", Test20bins[0],frequency[0],  accumulate[0]);

    //Le calcule des fréquences ainsi que accumulate    
    for (int i=1; i<21; ++i)
    {
        frequency[i] =(double) Test20bins[i]/1000000;   
        accumulate[i] = frequency[i] + accumulate[i-1];
        printf("%d\t%lf\t%lf\n", Test20bins[i], frequency[i], accumulate[i]);
        
    }
    printf("\n");
}

/* ------------------------------------------------------------------------ */
/* -------------------------------------Q5: a------------------------------ */
/*  commondice() :  Somme les valeurs générées par la fonction              */
/*                  genrand_real2() avec une modification pour que          */
/*                  les valeurs soit compris dans [1,6]                     */
/*                                                                          */
/*  En entrée :   void                                                      */
/*                                                                          */
/*  En Sortie : affichage de la somme                                       */
/* ------------------------------------------------------------------------ */
void commondice(){
    int     sum     =   0;

    //cette boucle permet de calculer la somme de tout les 20 lance du dé.
    for (int i = 0; i < 20; i++)
    {
        sum += (int) (genrand_real2()*6) + 1;
    }

    //affichage de la somme
    printf("%d\n", sum);
    

}