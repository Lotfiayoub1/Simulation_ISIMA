#include"mt19937ar.h"



int main(int argc, char* argv[]){

 
    int             init2[6] =   {100,400,600,400,100,200};
    double        * r        =   calloc(6, sizeof(double));

    
    uniform(-89.2,56.7);
    printf("\n");
    discrete_empirical_distributions();
    r= generic_function(6,init2);
    generic_affichage(r);
    
    return 0;
}