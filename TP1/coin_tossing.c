#include "coin_tossing.h"

void coin_tossing(){
    float heads=0, tails=0;
    int experiment;
    printf("Entrer the number of experiments : ");
    scanf("%d",&experiment);
    for (int i = 0; i < experiment; i++)
    {
        if (flip() == 1)
        {
            heads++;
        }else{
            tails++;
        }
        
    }
    printf("for %d tries we get\n",experiment);
    printf("number of heads is = %d\n so the probablity to get a heads is %0.2f\n", (int) heads, (heads/experiment));
    printf("number of tails is = %d\n so the probablity to get a tails is %0.2f\n", (int) tails, (tails/experiment));
   
}


int flip(){
    int answer = rand() % 2;
    if (answer == 0){
        /* if the number is pair*/
        return 1;
    }else{
        /* if the number isn't pair*/
        return 0;
    }
    
}