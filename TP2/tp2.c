#include"mt19937ar.h"



int main(int argc, char* argv[]){

    int i;
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);
    
    uniform(-89.2,56.7);

    printf("\n");
    discrete_empirical_distributions();
    return 0;
}