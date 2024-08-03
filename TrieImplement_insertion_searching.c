#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrieNode {
    struct TrieNode* childNode[26];
    int indicator;
    char* meaning;
};

struct TrieNode *root=NULL;

struct TrieNode* constructor() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));

        newNode->indicator = 0;
        for (int i = 0; i < 26; i++) {
            newNode->childNode[i] = NULL;
        }
    
    newNode->meaning=NULL;
    return newNode;
}

void insertWord(struct TrieNode* root,char* word,char *meaning) {
    struct TrieNode* current = root;
    int i=0;

    while (word[i]) {
        int index = word[i] - 'a';

        if (!current->childNode[index]) {
            current->childNode[index] = constructor();
        }

        current = current->childNode[index];
        i++;
    }

    current->indicator = 1;
    
    current->meaning=(char*)malloc(sizeof(char)*500);

    int j=0;

    while(meaning[j]){
        current->meaning[j]=meaning[j];
        j++;
    }

    current->meaning[j]='\0';
    
}

void suggestWord(struct TrieNode* curr,char *word,int *cnt,int j){

if(!curr)return;

if((*cnt)>=5)return;

if(curr->indicator==1){
    for(int i=0;i<j;i++)printf("%c",word[i]);
    printf("\n");
    (*cnt)++;
    return;
}

for(int i=0;i<26;i++){
    if(curr->childNode[i]){
        word[j]=i+'a';
        suggestWord(curr->childNode[i],word,cnt,j+1);
    }
}

}



void suggestHelper(struct TrieNode* root,char* word){

int len=0;

while(word[len])len++;


char *sugArr=(char*)malloc(sizeof(char)*(len+20));

int i=0;

struct TrieNode* curr=root;
struct TrieNode* prev=NULL;

for(i=0;i<len;i++){
    
    if(!curr->childNode[word[i]-'a']) return;
    
    prev=curr;
    curr=curr->childNode[word[i]-'a'];

    sugArr[i]=word[i];
}

int cnt=0;

printf("\nDo you mean........\n");
suggestWord(prev,sugArr,&cnt,i-1);
printf("\n");

}


int searchWord(struct TrieNode* root,char* word) {
    struct TrieNode* current = root;
    int i=0;

    while (word[i]) {
        int index = word[i] - 'a';

        if (!current->childNode[index]){
        suggestHelper(root,word);
        return 0; 
        }

        current = current->childNode[index];
        i++;
    }
    
    if(current != NULL && current->indicator)printf("%s\n",current->meaning);
    else suggestHelper(root,word);

    return (current != NULL && current->indicator);
}


void readWordsFromFileAndInsert(struct TrieNode* root){
    FILE* file = fopen("storage.txt", "r");

    char word[150];
    char meaning[500];

    while (fscanf(file,"%s", word) == 1) {
        fscanf(file, " %[^\n]c", meaning);
        insertWord(root, word,meaning);
    }
    
    printf("\n..........................Loading done.......................... \n");
    printf(" ..............................welcome............................\n");

    fclose(file);
}