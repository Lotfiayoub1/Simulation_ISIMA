#include "lgcs.h"

int *intRand(){
    long X0,X1,A,C,M;
    int *r = calloc(32, sizeof(int)); 

    printf("-------------------------------------\n");
    printf("          X1 = (a*X0 + c) modulo m        \n");
    printf("---------------------------------------\n");
    printf("insert the seeds and (a,c,m) tuples \n");

    printf("Entrer le nombre X0 = ");
    scanf("%i",&X0);

    
    printf("Entrer le nombre a = ");
    scanf("%i",&A);

    printf("Entrer le nombre c = ");
    scanf("%i",&C);

    printf("Entrer le nombre m = ");
    scanf("%i",&M);
    printf("\n");
    for (int i = 0; i < 32; i++)
    {

        X1 = (A * X0 + C) % M;
        r[i] = X1;
        X0 = X1;
    }

    return r;
}

float *floatRand(int *N, int divide){
    float *floatResult = calloc(32, sizeof(float));
    for (int i = 0; i < 32; i++)
    {
        floatResult[i] =(float) N[i]/divide;
    }
    printf("\n");

    return floatResult;
}

void affichage_tableau(void *N, char type[]){

    
    if (strcmp(type,"int")==0)
    {
        int *M = (int*)N;
        for (int i = 0; i <31; i++)
        {
        printf( "%d ,",M[i]);
        }
        printf("%d.\n",M[31]); 
    }
    else if(strcmp(type,"float")== 0)
    {
        float *M = (float*)N;
        for (int i = 0; i <31; i++)
        {
        printf( "%0.4f ,",M[i]);
        }
        printf("%0.4f.\n",M[31]); 
        printf("\n");

    }
}
