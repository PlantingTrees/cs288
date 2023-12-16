#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]){
    //using unsigned char *
    unsigned char * pArgv= (unsigned char *) &argv;
    printf("argv  | ");
    for (int i = 7; i >=0; i--){
        printf("%02hhx", *(pArgv+i));
    }
    printf("  | %p\n", pArgv);
    

    for(int i=0; i < argc; i++){
        unsigned char *pArg= (unsigned char *) &argv[i];
        printf("argv[%d] | ", i);
        for (int i=7; i >=0; i--){
            printf("%02hhx", *(pArg+i));
        }
        printf(" | %p\n", pArg+i);
    }
    unsigned char * pChar = (unsigned char *) &argv;
    int bitMask=0xf;
    int result = *pChar & bitMask;

    //get the contents in the array 
    for(int i=0; i < argc; i++){
        if(i==0){
            if(result % 8 != 0){
                int replaceMask=0x0000;
                *pArgv & replaceMask;
            }
        }
        printf("|");
        for(int j=0; j < 8; j++){
            if(isprint(*(pArgv+j))){
                printf("%d(%c)", *(pArgv+i), *(pArgv+j));
                
            }else{
                printf("00(\\0)");
            }
           
        }
        printf("|%p\n", &argv[i]);
    }
    return 0;
}

