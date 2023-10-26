#include <stdlib.h>
#include <stdio.h>


int main(){
    //get the file 
    FILE *fileHandler=fopen("./matrix_gen", "rb");
    if(fileHandler == NULL){
        perror("Problems with file: ");
        exit(EXIT_FAILURE);
    }
    unsigned int fileBuff[4];
    //need to read only one 4byte at a time 
    while(1){
        if(fread(fileBuff, sizeof(unsigned int), 1, fileHandler)!=1){
            break;
        }
        printf("integer: Hex: 0x%08X Dec: %u/n", fileBuff, fileBuff);
    }
}