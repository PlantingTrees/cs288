#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
extern int errno;
#define MAX_PATH 1000
#define MAX_LINE 1000

int  traverseDir(char *path, int *totalCount){
    struct dirent *entry; int lineCounter=0; char lineBuffer[MAX_LINE]; int errnum;
    if(path==NULL){
        perror("Problem with pathname, please review.");
        exit(EXIT_FAILURE);
    }
    DIR *directory=opendir(path);
    if(directory==NULL){
        perror("Problems with directory");
        exit(EXIT_FAILURE);
    }
    while((entry=readdir(directory))!=NULL){
        if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0){
            continue;
        }
        if(entry->d_type==DT_REG){
            char *extension=strrchr(entry->d_name, '.');
            if(extension==NULL){
            perror("Not a valid file extension");
            exit(EXIT_FAILURE);
         }
        if(strcmp(extension,".txt")==0){
            //we got .txt files
            //build the file's path
            char filename[MAX_PATH];
            snprintf(filename, MAX_PATH, "%s/%s", path,entry->d_name );
           FILE *fileHandler= fopen(filename, "r+");
           if(fileHandler==NULL){
                perror("Failed in file operation: ");
                exit(EXIT_FAILURE);
           }
           while(fgets(lineBuffer, MAX_LINE, fileHandler)!= NULL){
                lineCounter+=1;
           }
        }
        }
        else if(entry->d_type==DT_DIR){
            //build a new path
            char filePath[MAX_PATH];
            snprintf(filePath, MAX_PATH, "%s/%s", path,entry->d_name);
            traverseDir(filePath, &lineCounter);
        }
         
    }
    *totalCount+=lineCounter; //updates the main fucntion total counts
    //return line count 
    return lineCounter;
}
int main(){
    char *pathname;
    int totalCount;
    printf("Enter in the pathname: \n");
    scanf("%s", pathname);
   pathname="/Users/kingsleyhustled/Documents/cs288/cs288/hw3_test_problem_3";
    traverseDir(pathname, &totalCount);
    printf("Total line counts: %d\n", totalCount-1);
    return 0;
}