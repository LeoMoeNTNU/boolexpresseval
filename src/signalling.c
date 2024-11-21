#include "boolports.h"
#include "basicdirections.h"
#include "wiresetup.h"
#include "signalling.h"

void pushSigStack(signal_t sig)
{
    nextSignalStack[++nextsignalindex] = sig;
}

// This pop will not actually pop anything.
// It will draw stuff.
void popSigStack()
{
    signalto(signalStack[signalindex--]);
}

// TODO: think about and build this function.
// signalto is going to put things in the nextsignalstack.
// The reason it does this: it doesnt actually light up everything, it just puts it in the next one.
// It wont send things backwards though. In my abstraction, light only goes forwards. Its a shitty abstraction.
// My guess:

void signalto(signal_t sig)
{ // I have a strong feeling that this is going to be bad code :(
    setTile(sig.clr, sig.x, sig.y);

    for (int i = 0; i < 4; i++)
    { // 4 directions, declared in basicdirections.
        direction_t dir = directions[i];
        int newx = sig.x + dir.x;
        int newy = sig.y + dir.y;
        if(dir.oppositedir!=sig.from){
            if(isWire(newx,newy)){
                signal_t newsig = {newx, newy, dir.dir, sig.clr}; // split it into two lines because why not.
                pushSigStack(newsig);
            }
            else 
            if(isPort(newx,newy)){
                notifyPort(newx,newy);
            }
        }
        
    }

    // This one will have lots.
    // check grey/yellow
    // send around recursively.
    // I probably have to implement a timer first and some wait esque stuff.
    // This I need to wait for.
}

void updateverything()
{

    if (originalorder)
    {
        signalStack += SIGSTACKSIZE;
        nextSignalStack -= SIGSTACKSIZE;
    }
    else
    {
        signalStack -= SIGSTACKSIZE;
        nextSignalStack += SIGSTACKSIZE;
    }
    originalorder = !originalorder;

    // swap procedure for signalindex, nextsignalindex:
    int tempindex;
    tempindex = signalindex;
    signalindex = nextsignalindex;
    nextsignalindex = tempindex;
    // we probably know that one of them is zero and most of the swap is useless.
    //  :(

    while (signalindex >= 0)
    {
        popSigStack();
    }

    signal_t_array sa=getsigsfromports();//This whole segment should probably be before the one above. 
    for(int i=0;i<sa.len;i++){
        pushSigStack(sa.sP[i]);
    }
    free(sa.sP);//This line is important because I am malloc-ing from somewhere else. 


    /*
    REMINDER FOR HOW THE CODE FUNCTION FOR THE FUTURE.
    */
    // boolports.c is going to do a little fancy trick here.
    // It has a list of ports that have been modified and as such they need to send a signal.
    // In this system, I use pushSigStack.
    // This works because signalindex and nextsignal index have already been built.
}