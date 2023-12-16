//#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
 // mac value
#define MAX 999
int main(int argc, char* argv[]){
    char file_path[1024];
    printf("Enter filepath: ");
    scanf("%s", file_path);
    //open the file 
    FILE *file_handler= fopen(file_path, "rb");
    if(file_handler == NULL){
        perror("Error opening file");
        exit(-1);
    }
    //reading the data into a buffer
    struct stat file_details;
    int _ = stat(file_path, &file_details);
    
    int file_size = file_details.st_size;
    if(file_size == -1){
        perror("Cannot seek file");
    }
    //making an array based on the number of elements in the file 
    int no_of_elements= file_size/sizeof(int);
    int input_array[no_of_elements];
    //int* input_array = (int *) malloc(no_of_elements * sizeof(int));
    if((fread(input_array, sizeof(int), no_of_elements, file_handler)) <= 0){
        //cannot read the total file contents 
        perror("Error reading the file.");
    }
    int count_array[MAX+1];
    //clean up the count_array i will use calloc later but i need to see what's going on under the hood 
    for(int cleanup=0; cleanup<= MAX+1; ++cleanup){
        if(count_array[cleanup] != 0){
            count_array[cleanup]=0;
        }
    }
    for(int occurence=0; occurence < no_of_elements; ++occurence){
        int value=input_array[occurence];
        count_array[value]+=1;
    }
   
    //get the cumulative sum of the count_array
    int sum=0;
    for(int c_sum=1; c_sum <= MAX; ++c_sum){
        count_array[c_sum]+=count_array[c_sum-1];
    }
    // for(int i=0; i<=MAX; ++i ){
    //     printf("%d\n", count_array[i]);
    // }

    //make another array called output_array 
    int output_array[no_of_elements];
    //loop through input_array from end to beginning 
    //problem here
    for(int end=no_of_elements-1; end >= 0; --end){
        int input_array_number = input_array[end];
        int c_sum_value = count_array[input_array_number];
        c_sum_value=c_sum_value-1;
        output_array[c_sum_value] = input_array_number;
    }
    for(int i=0; i <= no_of_elements-1; ++i){
        printf("%d\n",output_array[i]);
    }
    
    return 0;
}



// int num_of_elem= file_size/ sizeof(int);

    // int *buffer= (int *) malloc(num_of_elem * sizeof(int));

    // fread(buffer, sizeof(int), file_size, file_handler);
    
    // //implement count_sort 
    // //get the max value of the array 
    
    // // int * unique_count_array= (int *) calloc(num_of_elem, sizeof(int));
    // int unique_count_array[MAX];
    // int output_count_array[MAX];
    // //clean up array
    // for(int j=0; j < MAX; j++){
    //     if(unique_count_array[j] != 0){
    //         unique_count_array[j] = 0;
    //     }
    // }
    // for(int i=0; i < num_of_elem; ++i){
    //     int number=buffer[i];
    //     if(unique_count_array[number] == 0){
    //         unique_count_array[number] += 1;
    //     }
    // }
    
    // //calcualte the cummulative sum
    // for(int j=1; j <= MAX; ++j){
    //     unique_count_array[j]+=unique_count_array[j-1];
    // }
    // for(int i=MAX-1; i >=0; i--){
    //     int number= buffer[i];
    //     int mapped_value_number= unique_count_array[number];
    //     int output_mapped_value_number=mapped_value_number - 1;
    //     output_count_array[output_mapped_value_number]=number;

    // }
    // for(int k=0; k <=MAX; k++){
    //     printf("%d", output_count_array[k]);
    // }