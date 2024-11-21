//It needs to know of signal_t somehow...

#include "wiresetup.h"
#include "basicdirections.h"

//updateeverything is certainly needed. 


void pushSigStack(signal_t sig);
void popSigStack();//Dont actually think we need this one in here. 
void signalto(signal_t sig);
void updateverything();
