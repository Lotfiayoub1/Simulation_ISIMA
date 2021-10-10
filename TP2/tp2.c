#include"mt19937ar.h"



int main(int argc, char* argv[]){

 
    int             init2[6] =   {100,400,600,400,100,200};
    double        * r        =   calloc(6, sizeof(double));

    int             MenuInt  = 0;
    double          sum      = 0.;

    
    //la boucle qui permet d'afficher le menu a chaque fois sauf si on décide de fermer l'application en appuyant sur le 5.
    while (MenuInt != 5)
    {
        //affichage du menu
        printf("* ----------------------------------Menu---------------------------------- *\n");
        printf("| Choisissez l'option qui vous convient                                    |\n");
        printf("| 1 - Q2 : (Generation of uniform random numbers between A and B)          |\n");
        printf("| 2 - Q3 : (Simulation d'une distribution discrete)                        |\n");
        printf("| 3 - Q4 : (Simuler la loi exponentielle)                                  |\n");
        printf("| 4 - Q5 : (Simulation de lois de distribution non reversibles)            |\n");
        printf("| 5 - EXIT                                                                 |\n");
        printf("* ------------------------------------------------------------------------ *\n");

        scanf("%d",&MenuInt);

        //Switch permet de faire le traitement du choix de l'utilisateur
        switch (MenuInt)
        {
            //Q2
            case 1:
                uniform(-89.2,56.7);
                printf("\n");
                break;

            //Q3    
            case 2:

                //a
                discrete_empirical_distributions();

                //b {a,b,c}
                r= generic_function(6,init2);
                generic_affichage(r);
                break;

            //Q4
            case 3:

                printf("La question b :\n");
                //b
                for (int i = 0; i < 1000000; i++)
                {
                    //a
                    sum += negExp(10);
                    
                }
                printf("%lf\n",sum/1000000);
                
                //c
                printf("La question c :\n");
                test20bins();
                break;

            //Q5
            case 4:
                commondice();
                Box_Muller();
                break;

            // Quitter le menu
            case 5:
                printf("I hope you like the application \n");
                printf("See you in the next TP ^_^ \n");
                break;

            //pour gérer les nombres hors menu 
            default:
                printf("ERREUR\n");
                break;
        }

    }
    return 0;
}