#include <stdlib.h>
#include <stdio.h>

int main(){
    float float_num_to_investigate=123.45;
    unsigned int *p, i, j;
    char value_of_bits4to7;
    p=(int *) &float_num_to_investigate;
    i=(int) float_num_to_investigate;
    j=*p;
    int bit_max=32;
    unsigned int bitmask= 0xff<<23;
    while(bit_max != 0){
        unsigned int calculations = (*p & bitmask);
        float result=*(float *) &calculations;
        
        printf("value : %f", result);
        bit_max-=4;
    }
    
    
    
    return 0;
}