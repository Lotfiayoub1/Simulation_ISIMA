#include "regular_dice.h"

void regular_dice(){
    int random_number, number_of_experiments;
    int nombreFaces = 0;
    int *N = NULL; // ce pointeur va servir de tableau après l'appele de calloc
    printf("how many images do you want the dice to have  (6 or 10): ");
    scanf("%d",&nombreFaces);

    N = calloc(nombreFaces, sizeof(int));

    if (nombreFaces == 6)
    {
        
        printf("entrer the number of experiments : ");
        scanf("%d",&number_of_experiments);

        for (int i = 0; i < number_of_experiments; i++)
        {
    
            random_number = rand()%nombreFaces +1;
            // printf("%d\n",random_number);
            switch (random_number)
            {
                case 1:
                    N[0]++;
                    break;
                case 2:
                    N[1]++;
                    break;
                case 3:
                    N[2]++;
                    break;
                case 4:
                    N[3]++;
                    break;
                case 5:
                    N[4]++;
                    break;
                case 6:
                    N[5]++;
                    break;
                default:
                    printf("random_number it's not in [1-6] \n");
                    break;
            }
        }
        printf("for %d experiments we get %d times the number 1 \n", number_of_experiments, N[0]);
        printf("for %d experiments we get %d times the number 2 \n", number_of_experiments, N[1]);
        printf("for %d experiments we get %d times the number 3 \n", number_of_experiments, N[2]);
        printf("for %d experiments we get %d times the number 4 \n", number_of_experiments, N[3]);
        printf("for %d experiments we get %d times the number 5 \n", number_of_experiments, N[4]);
        printf("for %d experiments we get %d times the number 6 \n", number_of_experiments, N[5]);
        printf("\n");
    }else if(nombreFaces==10){
        
        printf("entrer the number of experiments : ");
        scanf("%d",&number_of_experiments);
        for (int i = 0; i < number_of_experiments; i++)
        {
    
            random_number = rand()%nombreFaces +1;
            // printf("%d\n",random_number);
            switch (random_number)
            {
                case 1:
                    N[0]++;
                    break;
                case 2:
                    N[1]++;
                    break;
                case 3:
                    N[2]++;
                    break;
                case 4:
                    N[3]++;
                    break;
                case 5:
                    N[4]++;
                    break;
                case 6:
                    N[5]++;
                    break;
                case 7:
                    N[6]++;
                    break;
                case 8:
                    N[7]++;
                    break;
                case 9:
                    N[8]++;
                    break;
                case 10:
                    N[9]++;
                    break;
                default:
                    printf("random_number it's not in [1-10] \n");
                    break;
            }
        }
        printf("for %d experiments we get %d times the number 1 \n", number_of_experiments, N[0]);
        printf("for %d experiments we get %d times the number 2 \n", number_of_experiments, N[1]);
        printf("for %d experiments we get %d times the number 3 \n", number_of_experiments, N[2]);
        printf("for %d experiments we get %d times the number 4 \n", number_of_experiments, N[3]);
        printf("for %d experiments we get %d times the number 5 \n", number_of_experiments, N[4]);
        printf("for %d experiments we get %d times the number 6 \n", number_of_experiments, N[5]);
        printf("for %d experiments we get %d times the number 7 \n", number_of_experiments, N[6]);
        printf("for %d experiments we get %d times the number 8 \n", number_of_experiments, N[7]);
        printf("for %d experiments we get %d times the number 9 \n", number_of_experiments, N[8]);
        printf("for %d experiments we get %d times the number 10 \n", number_of_experiments, N[9]);
        printf("\n");
    }else
    {
        printf("Choose 6 or 10 next time\n");
    }
    
    
    
}

