#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node * next;
};
int main(){
    struct Node *newNode=(struct Node *)malloc(sizeof(struct Node));
    newNode->data=45;
    newNode->next=NULL;
    struct Node *head=newNode;
    struct Node *newNode2=malloc(sizeof(struct Node));
    newNode->next=newNode2;
    newNode2->data=30;
    newNode2->next=NULL;

    //traveersal node 
    struct Node *traversalNode=head;
    while(traversalNode!=NULL){
        printf("Data: %d\n", traversalNode->data);
        traversalNode->next;
        traversalNode=traversalNode->next;
    }
    return 0;
}