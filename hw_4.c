#include <stdio.h>
#include <stdlib.h>


int main(){
  int count;
  int bucket_sizes[16];
  char file_contents[100];
  int unsortedArray[16]={1,3,4,5,6,7,87,3,4,5,33,55,66,77,33,22};
  int offsets[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int buffer[16]={0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  count=5;
  //clean out bucket dirt
  for (int c=0; c<16; c++){
    if(bucket_sizes[c]==0){
      continue;
    }
    else{
      bucket_sizes[c]=0;
    }
    
  }
  for (int unsortedIndex=0; unsortedIndex < 16; unsortedIndex++){
    int unsortedVal = unsortedArray[unsortedIndex];
    //bitwise mask 0xf
    int bitwise_lsd_value=(unsortedVal & 0XF);
    bucket_sizes[bitwise_lsd_value]+=1;
  }
  //offset array 
  for(int i=0; i<16; i++){
    for(int j=0; j<i; j++){
      offsets[i]+=bucket_sizes[j];
    }

  }
  int value;
  //map to buffer_array using offset
  for(int i=0; i<16; i++){
    //get the lsd 
    int lsd=(unsortedArray[i] & 0XF);
    if(buffer[offsets[lsd]]==0){
      buffer[offsets[lsd]]=unsortedArray[i];
    }
    while(buffer[(offsets[i])+value]!=0){
        value=bucket_sizes[i]-1;
    }
    perror("not enough buckets...");
    break;

}
  for(int i=0; i<16; i++){
    printf("%d\n", buffer[i]);
  }
}



// if(buffer[offsets[lsd]]==0){
//       buffer[offsets[lsd]]=unsortedArray[i];
//     }
//     else if(buffer[(offsets[lsd])+()]==0){
      
//   }