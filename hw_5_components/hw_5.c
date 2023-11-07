#include <stdio.h>
#include <stdlib.h>

int main(){
    int Size;
    float **inputArray;
    float **bufferArray;
    int numFloat;
    numFloat=1;
    //read file 
    FILE *fileHandler= fopen("./input", "r");
    if(fileHandler == NULL){
        perror("File does not exit");
        exit(EXIT_FAILURE);
    }
    //read first value to size
    if((fscanf(fileHandler, "%d", &Size))!= 1){
        //allocate input & buffer arrays
        inputArray=(float **) malloc(Size * sizeof(float *));
        if(inputArray == NULL){
            perror("Cannot allocate space to inputArray");
            exit(1);
        }
        bufferArray=(float**) malloc(Size * sizeof(float *));
        if(bufferArray == NULL){
            perror("Cannot allocate space to bufferArray");
            exit(1);
        }
    }
    //get the values from input.txt into inputArray
    for(int i=0; i< Size; i++){
        inputArray[i]= (float *)malloc(sizeof(float) * numFloat);
        if(inputArray[i] == NULL){
            perror("Cannot make space for input float values");
            exit(EXIT_FAILURE);
        }
    }
    //fclose(fileHandler);
    return 0;
}