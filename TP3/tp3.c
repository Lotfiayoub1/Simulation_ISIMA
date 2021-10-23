#include <stdio.h>
#include <stdlib.h>
#include "mt19937ar.h"

int main(int argc, char **argv){

    int             MenuInt  = 0;
    double          Pi;
    double     *    T    =   calloc(30,sizeof(double));

    while (MenuInt != 4)
    {
        //affichage du menu
        printf("* ----------------------------------Menu---------------------------------- *\n");
        printf("| Choisissez l'option qui vous convient                                    |\n");
        printf("| 1 - Q1 : (Calculer PI )                                                  |\n");
        printf("| 2 - Q2 : ( PI )                                                          |\n");
        printf("| 3 - Q3 : (Rayon de confiance PI )                                        |\n");
        printf("| 4 - EXIT                                                                 |\n");
        printf("* ------------------------------------------------------------------------ *\n");

        scanf("%d",&MenuInt);

        
        //Switch permet de faire le traitement du choix de l'utilisateur
        switch (MenuInt)
        {
            //Q1
            case 1:
                Pi = simPi(10000);
                printf("%f\n",Pi);
                break;

            //Q2
            case 2:
               T = diceFunction(30);
               for (int i = 0; i < 30; i++)
               {
                   printf("T[%d] : %f \n",i, T[i]);
               }
                break;
            //Q3 : Rayon de confiance
            case 3:
                T = diceFunction(30);
                RayonDeConfiance(T);
                break;

            case 4:
                printf("See you next time \n");
                break;

            //pour gérer les nombres hors menu 
            default:
                printf("ERREUR\n");
                break;
        }

    }
}
// gcc -O2 