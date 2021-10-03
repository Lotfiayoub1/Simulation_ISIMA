/*
*************************************************************************
Name : ex1.c TP1
Author : LOTFI Ayoub
Description : make a generator using a simple methode 
************************************************************************ 
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "middle_square.h"
#include "coin_tossing.h"
#include "regular_dice.h"
#include "lgcs.h"

int main(void){

    int *p;
    float *F;
    int menuItem = 0;
    while (menuItem != 5)
    {
        printf("--------------Generator Menu---------------- \n");
        printf("1- middle square technique \n");
        printf("2- coin tossing simulation \n");
        printf("3- dice simulation \n");
        printf("4- linear congruential generators \n");
        printf("5- EXIT\n");
        printf("\n");
        printf("choose the method you want by pressing the exact number : ");
        scanf("%i",&menuItem);
        printf("\n");
        switch (menuItem)
        {
            case 1:
                middle_square();
                break;
            case 2:
                coin_tossing();
                break;
            case 3:
                regular_dice();
                break;
            case 4:
                p = intRand();
                affichage_tableau(p,"int");
                
                F = floatRand(p,16);
                affichage_tableau(F,"float");
                break;
            case 5:
                printf("See you next Time");
                exit(0);
                break;
                
            default:
                printf("this number it's not in the menu list\n");
                break;
        }  

    }
    return 0;
}








