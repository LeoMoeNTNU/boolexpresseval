#include <stdbool.h>
#include <stdlib.h> //for malloc
#include "compiler.h"
#include <stdio.h>//for printf
#include "compilerNode.h"

//void (*parsefunc)(void); not being used. 

//start
bool parse0();
char *c;

bool parseString(char* arg){
    c=arg;
   return (parse0()&&*c==0);
   //parse0 heavily modifies c. 
   //*c==0 is to make sure that there is nothing after the expression. 
}

bool parse0(){
    if(*c=='0'||*c=='1'){
        c++;
        return true;}
    if(*c!='{'){return false;}
    c++;
    if(!parse0(c)){return false;}
    if(*c!='*'&&*c!='+'){return false;}
    c++;
    if (!parse0(c)){return false;}
    if(*c!='}'){return false;}
    c++;
    return true;
}




typedef struct{
    char* cP;
    Node_t* nP;
}dub_t;

dub_t makeTree(char* cp){
    //if(!parseString(cp)){printf("invalid syntax!\n");} THIS ONE DOESNT WORK YET. 

    Node_t* mainp=malloc(sizeof(Node_t));
    if(*cp=='0'||*cp=='1'){//This is if it is only a value.
        printf("found a bottom letter\n");
        mainp->error=false;
        mainp->bottom=true;
        mainp->value=(*cp=='1');
        cp++;
        return (dub_t){cp,mainp};
        //I dont do anything for leftp and rightp lol :)
        //They are allocated but what is there is random. 
    }
    printf("didnt start with a bottom...\n");
    mainp->bottom=false;
    if(*cp!='{'){
        mainp->error=true;
        return (dub_t){cp,mainp};
        //There is lots of stuff that I just didnt do in here. 
    }
    cp++;
    dub_t update=makeTree(cp);
    if(update.nP->error){//Now we are dealing with getting errors. 
        mainp->error=true;
        return (dub_t){cp,mainp};
    }
    cp=update.cP;//I love this pattern but its annoying. cp gets updated all the time. 
    mainp->leftp=update.nP;

    if(*cp!='+'&&*cp!='*'){
        mainp->error=true;
        return (dub_t){cp,mainp};
    }
    mainp->operand=*cp;
    cp++;
    update = makeTree(cp);
    if (update.nP->error)
    { // Now we are dealing with getting errors.
        mainp->error = true;
        return (dub_t){cp, mainp};
    }
    cp = update.cP; 
    mainp->rightp = update.nP;
    if(*cp!='}'){
        mainp->error=true;
        return (dub_t){cp,mainp};
    }
    cp++;
    mainp->error=false;
    mainp->bottom=false;
    
    return (dub_t){cp,mainp};
}

bool isTreeCorrect(char *arg){
    return !makeTree(arg).nP->error;
}

void *getTree(char *arg){
    if (!parseString(arg))
    {
        return NULL;
    }
    return makeTree(arg).nP;
}

int depth(void* tree){
    Node_t *treeNode = tree;

    if(treeNode->bottom){
        return 1;}
    int leftdepth=depth(treeNode->leftp); 
    int rightdepth=depth(treeNode->rightp);
    if(leftdepth>=rightdepth){return leftdepth+1;}
    return rightdepth+1;
}

void printwholetree(void* tree, int depth){

    Node_t *treeNode = tree;
    for(int i=0;i<depth;i++){printf(" ");}//There could be better syntax for this supposedly. 
    if(treeNode->bottom){
        printf("%d\n",treeNode->value);
        return ;
    }
    printf("%c\n",treeNode->operand);
    printwholetree(treeNode->leftp,depth+1);
    printwholetree(treeNode->rightp,depth+1);
    return ;
}

void analyzeTree(char* arg){
    printf("NEW ONE:\n");
    char* argb=arg;
    printf("the string is:   ");
    while(*argb!=0){
        printf("%c",*argb++);
    }
    printf("\n");
    printf("true is %d\n",true);
    printf("parseString: %d\n",parseString(arg));
    if(!parseString(arg)){return ;}
    void *a=getTree(arg);
    Node_t*a2=a;
    printf("tree->error:%d\n",a2->error);
    printf("its at the bottom: %d\n",a2->bottom);
    printf("the depth of the tree is %d\n",depth(a));
    printwholetree(a,0);
    return a;




}

void killTree(void *tree){
    Node_t* treeNode=tree;
    if(treeNode->bottom==false){
        killTree(treeNode->leftp);
        killTree(treeNode->rightp);
    }
    printf("the free that is bad is in killtree\n");
    free(tree);
    return ;
}
