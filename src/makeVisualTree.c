#include "compiler.h" //for making the tree.
#include "compilerNode.h" //for the node description. 
#include "wiresetup.h" //for set, and something else maybe.
#include "signalling.h" //for pushSigStack
#include "boolports.h" //for makeport
#include "makeVisualTree.h"//where im exporting all this to. 

typedef struct {
    int x;
    int y;
}xy_t;

xy_t buildNode(Node_t *a, int* portP){
    if(a->bottom){
        *portP+=1;
        xy_t startpoint={0,10*(*portP)};
        signal_t newsig={startpoint.x,startpoint.y,UP,sameascolor(a->value)};
        //I dont know why the fuck UP works and LEFT doesn't. 
        //well too bad I guess.  
        horiWire(startpoint.x,startpoint.y,startpoint.x+3);
        //Holy fuck the line above is cursed. 
        //The reason why is that the signal will check if the one on the right is a wire before it
        //decides to go right or not. 
        //TODO: FIX THIS SHIT. 

        pushSigStack(newsig);
        return startpoint;
    }
    else{
        xy_t upper=buildNode(a->leftp,portP);
        xy_t downer= buildNode(a->rightp,portP);
        int maxX;
        if(upper.x>=downer.x){
            maxX=upper.x;
        }
        else{
            maxX=downer.x;
        }
        maxX+=10;
        horiWire(upper.x+1,upper.y,maxX);
        horiWire(downer.x+1,downer.y,maxX);
        int meetingY=(upper.y+downer.y)/2;
        printf("maxX is %d\n",maxX);
        vertWire(maxX,upper.y,downer.y);
        //vertWire(upper.y,maxX,downer.y);
        enum Port p;
        if(a->operand=='+'){
            printf("making an OR\n");
            p=OR;}
        else if(a->operand=='*'){
            printf("making an AND\n");
            p=AND;}
        makePort(maxX,meetingY,p);
        return (xy_t){maxX,meetingY};
    }
}

void makeSyntaxTree(char *args){
    void * a=getTree(args);
    int ports=0;
    Node_t* tree=a;
    xy_t finishingpoint=buildNode(tree,&ports);
    horiWire(finishingpoint.x+1,finishingpoint.y,finishingpoint.x+50);

}
