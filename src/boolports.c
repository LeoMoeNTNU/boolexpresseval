#include "boolports.h"
#include "basicdirections.h"
#include "wiresetup.h"

#define green (Color_t){50,250,12}
#define red (Color_t) { 248, 20, 16 }
#define purple (Color_t) { 238, 130, 238 }
#define orange (Color_t) {255,165,0}
//I should probably have an array of these. 
Color_t portcolorarray[]={green,red,purple,orange};
int portcolors=4;

typedef struct xy{
    int x;
    int y;
}xy_t;

//Functions in the file:
void setupboolports();
void makePort(int x, int y, enum Port p);
void getMoreSpace();//getMoreSpace will be used inside of makePort.
Color_t clr(enum Port p);//I am putting it higher up to avoid implicit definitions. 

    typedef struct PortInfo
{
    int x;
    int y;
    enum Port p;
    direction_t out;
    bool notified;
    bool storedoutput;
} PortInfo_t;

int currports;
int maxports;
PortInfo_t *pip;
//TODO: put it in main.  
void setupboolports(){
    currports=0;
    maxports=2;
    pip=malloc(sizeof(PortInfo_t)*maxports);
}

//I dont know what happens if there are three inputs to the port. 
bool output(PortInfo_t p){

    

    xy_t twoinputs[2];//Im not sure I have to declare that it is zero yet. 
    int indextoputin=0;
    int xtolookat;
    int ytolookat;

    

    for(int i=0;i<4;i++){
        //This whole sequence is to find the two actual directions. 
        //This could be found when I make the Port way earlier. 
        direction_t d=directions[i];
        xtolookat=p.x+d.x;
        ytolookat=p.y+d.y;
        
        if(d.dir!=RIGHT&&isWire(xtolookat,ytolookat)){
            twoinputs[indextoputin++]=(xy_t){xtolookat,ytolookat};//I used i++ and am happy about it. It makes me feel smart. 
        }
        
    }


    bool newoutput;
    bool firstbool=isTrue(twoinputs[0].x,twoinputs[0].y);
    bool secbool=isTrue(twoinputs[1].x,twoinputs[1].y);

    switch (p.p)
    {
    case AND:
        newoutput=(firstbool&&secbool);
        break;
    case OR:
        newoutput=(firstbool||secbool);
        break;
    case NAND:
        newoutput=!(firstbool&&secbool);
        break;

    case NOR:
        newoutput=!(firstbool||secbool);
        break;
    }
    return newoutput;
}


//I assume all the ports have out to the RIGHT. If not, I'll change this later. 
//Doesnt make sure that you dont make two ports on the same place 
void makePort(int x, int y, enum Port p){
    printf("making port at (%d,%d) going at index %d\n",x,y,currports);
    if(currports>=maxports){//could be == but I like >= for some reason. 
        printf("apparently %d is >= than %d\n",currports,maxports);
        getMoreSpace();
    }

    pip[currports].x=x;
    pip[currports].y=y;
    pip[currports].p=p;
    pip[currports].out=dir(RIGHT);//for my current build output is always right. 
    pip[currports].notified=false;
    pip[currports].storedoutput=false;
    setTile(clr(p),x,y);
    currports++;
    
}

Color_t clr(enum Port p){
    switch (p)
    {
    case AND://red
        return red;
    case OR://orange
        return orange;
    case NOR://purple
        return purple;
    case NAND://green
        return green;
    }
    return (Color_t){0, 0, 0};
}

void notifyPort(int xNew, int yNew){
   
    //This has to be a bad idea. 
    printf("looking for the port at (%d,%d)\n",xNew,yNew);
    for(int i=0;i<=currports+1;i++){
        printf("there is a port at (%d,%d)\n",pip[i].x,pip[i].y);
        if(pip[i].x==xNew&&pip[i].y==yNew){
            pip[i].notified=true;
            return ;
        }
    }
    printf("the port wasn't notified\n");
    return ;

}

bool isPort(int x, int y)
{
    Color_t color = tile(x, y);
    for (int i = 0; i < portcolors; i++)
    {
        if (sameas(portcolorarray[i],color)){return true;}
    }
    return false;
}

void getMoreSpace(){
    maxports*=2;
    printf("I need more space for ports\n");
    PortInfo_t* pip2=realloc(pip,sizeof(PortInfo_t)*maxports);

    if(pip2!=NULL){
        pip=pip2;
    }
    else{
        do
        {
        pip2=malloc(sizeof(PortInfo_t)*maxports);
        } while (pip2==NULL);
        
        for(int i=0;i<currports;i++){
            /*pip2[i].x=pip[i].x;
            pip2[i].y=pip[i].y;
            pip2[i].out=pip[i].out;
            pip2[i].p=pip[i].p;
            printf("moving port at (%d,%d)\n");
            //I added the two below without thinking. 
            //I'm assuming it works because im just mocing the state around. 
            pip2[i].storedoutput=pip[i].storedoutput;
            pip2[i].notified=pip[i].notified;
            */
           pip2[i]=pip[i];
        }

        printf("The free that is illegal is in boolhports.c\n");
        free(pip);
        pip=pip2;
    }
}


signal_t_array getsigsfromports(){
    //It cant be returning null. I have to make the struct it is returning. 
    //one for loop is for just finding out how many there are. 

    int sigstodoshit=0;
    for(int i=0;i<currports;i++){
        PortInfo_t p=pip[i];
        if(p.notified&&p.storedoutput!=output(p)){//My guess is that this is correct but who knows...
            sigstodoshit++;

        }
    }
    signal_t* sp=malloc(sizeof(signal_t)*sigstodoshit);

    int ind=0;

    for(int i=0;i<currports;i++){
        PortInfo_t p=pip[i];
        if (p.notified && p.storedoutput!= output(p))
        {
            p.storedoutput=output(p);
            p.notified=false;
            xy_t sigplace={p.x+p.out.x,p.y+p.out.y};
            signal_t s = {sigplace.x,sigplace.y,p.out.dir,sameascolor(p.storedoutput)};
            sp[ind++]=s;//notice the ++
            
            }
    }
    return (signal_t_array){sp,sigstodoshit};

}

    // One thing I havent figured out yet is that I only need two of the inputs. I dont need all three at all.
    // This is also something that should be figured out internally in this file.

