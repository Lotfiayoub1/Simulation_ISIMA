#include"mt19937ar.h"



int main(int argc, char* argv[]){

 
    int             init2[6] =   {100,400,600,400,100,200};
    double        * r        =   calloc(6, sizeof(double));

    int             MenuInt  = 0;
    
    while (MenuInt != 3)
    {
        printf("* ----------------------------------Menu---------------------------------- *\n");
        printf("| Choisissez l'option qui vous convient                                    |\n");
        printf("| 1 - Q2 : (Generation of uniform random numbers between A and B)          |\n");
        printf("| 2 - Q3                                                                   |\n");
        printf("| 3 - Q4                                                                   |\n");
        printf("| 4 - EXIT                                                                 |\n");
        printf("* ------------------------------------------------------------------------ *\n");
        scanf("%d",&MenuInt);
        switch (MenuInt)
        {
            case 1:
                uniform(-89.2,56.7);
                printf("\n");
                break;
            case 2:
                discrete_empirical_distributions();
                r= generic_function(6,init2);
                generic_affichage(r);
                break;
            case 3:
                
                for (int i = 0; i < 1000000; i++)
                {
                    printf("%f --  ",negExp(10));
                    if (i%5 == 0) printf("\n");
                }
                
                break;
            case 4:
                printf("I hope you like the application \n");
                printf("See you in the next TP ^_^ \n");
                break;

            default:
                printf("ERREUR\n");
                break;
        }

    }
    return 0;
}