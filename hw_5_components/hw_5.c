#include <stdio.h>
#include <stdlib.h>

int main(){
    int Size;
    float **inputArray;
    float **bufferArray;
    float **negativeArray;
    int Counter[16];
    int Offset[16];
    //read file 
    FILE *fileHandler= fopen("./input", "r");
    if(fileHandler == NULL){
        perror("File does not exit");
        exit(EXIT_FAILURE);
    }
    //read first value to size
    if((fscanf(fileHandler, "%d", &Size))!= EOF){
        //allocate input & buffer arrays
        inputArray=(float **) malloc(Size * sizeof(float *));
        if(inputArray == NULL){
            perror("Cannot allocate space to inputArray");
            exit(1);
        }
        negativeArray=(float **) malloc(Size * sizeof(float *));
        if(negativeArray==NULL){
            perror("cannot allocate array for negative");
        }
        bufferArray=(float**) malloc(Size * sizeof(float *));
        if(bufferArray == NULL){
            perror("Cannot allocate space to bufferArray");
            exit(1);
        }
    }
    //get the values from input.txt into inputArray
    for(int i=0; i< Size; i++){
        inputArray[i]= (float *) malloc(sizeof(float));
        negativeArray[i]=(float *) malloc(sizeof(float));
        float temp;
        fscanf(fileHandler, "%f", &temp);
        if(temp < 0){
            *negativeArray[i]=temp; 
        }else{
            *inputArray[i]=temp;
        }
    }
    //convert float point to unsigned in, sort it and swap back to floats
    for(int i=0; i<16; i++){
        Counter[i]=0;
    }
    for(int value=0; value<Size; value++){
        unsigned int fp;
        fp=(unsigned int ) (*inputArray[value]);
        //get the lsd using mask
        unsigned int hex_mask= 0xf;
        unsigned int result = (fp & hex_mask);
        Counter[result]+=1;
        
    }
    
    //calculate the offsets 
    for(int i=0; i<16; i++){
        if(i==0){
            Offset[i]=0;
        }
        else{
            Offset[i]=Offset[i-1] + Counter[i-1];
        }
    }

    //put it in bufferArray
    for(int i=0; i< Size; i++){
        //cver back to normal float
        
    }
    //fclose(fileHandler);
    return 0;

}