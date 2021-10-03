#include "middle_square.h"


void middle_square(){
    long N, i,M,j = 0;
    int digit = 0;
    printf("Entrer le nombre N0 = ");
    scanf("%i",&N); 
    digit = count_digit(N,digit);
    printf("nombre de digits %d \n", digit);
    printf("Entrer le nombre d'iteration = ");
    scanf("%i", &i);
    printf("************************* TP1 **********************\n");
    for (j = 1; j <= i; j++)
    {
        N = N*N;
        // printf("ici ca va etre lblan kaml %4d \n", N);
        N = N/100;
        // printf("hyd joj lkhrin  %4d \n", N);
        N = N%10000;
        printf(" N%i = %4d \n",j,N);
        digit = 0;
        digit = count_digit(N,digit);
        if (digit <= 1)
        {
            printf("le nombre de digit pour la %i iteration est : %i\n",j,digit);
            printf("le Generateur s'arrete la car tous le reste vont 0\n");
            break;
        }
        
    }
}

int count_digit(long long seed,int digit) //to count the number of digit 
{
	long long p;
	p=seed;
	while(p!=0) /*digit count*/
	{
		p=p/10;
		digit++;
	}
	return digit;
}
