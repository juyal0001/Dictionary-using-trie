#include<stdio.h>
#include "TrieImplement_insertion_searching.c"

char takeWordInput[50];

int main(){
    
    //initializing main root of trie
    root=constructor();
    
    //load file data into trie
    readWordsFromFileAndInsert(root);
    
    char wordInput[50]; 
    
    while(1){
    
    printf("\n");
    
    printf("1. search\n2. exit\n");
    
    int x;
    scanf("%d",&x);
    
    printf("\n");

    if(x==2) {
        printf("adios amigos");
        break;
    }

    if(x==1){
        printf("\nenter word : ");
        scanf("%s",wordInput);

        int i=0;

        while(wordInput[i]){
            if(wordInput[i]>=65 && wordInput[i]<=90)
            wordInput[i]+=32;
            i++;
        }

        searchWord(root,wordInput);
        printf("\n");
    }

    }

    return 0;
}


