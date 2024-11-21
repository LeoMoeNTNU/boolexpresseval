#include "basicdirections.h"
#include "constants.h"

#ifndef WIRESETUP_H
#define WIRESETUP_H

typedef struct sig
{
    int x;
    int y;
    enum direc from;
    Color_t clr;

} signal_t;

//extern Color_t colorsforallblocks[];//I dont love that this one is publically available like this. 

extern Color_t grey;
extern Color_t yellow; 
extern Color_t kindablue;

void horiWire(int stablex, int ystart, int yend);
void vertWire(int xstart, int stabley, int xend);

void setallblocks(Color_t clr);
void setTile(Color_t clr, int x, int y);
Color_t tile(int x, int y); 
//void pushSigStack(signal_t sig);
//void popSigStack();
//My guess is that this one has to be moved to main. It uses specifics in boolports.
//void signalto(signal_t sig);

bool isWire(int x, int y);
bool isTrue(int x, int y);
Color_t sameascolor(bool b);//This one is a very simple converter.
bool sameas(Color_t a, Color_t b);

    // void updateverything();

extern signal_t bothstacks[];
extern bool originalorder;
extern signal_t *signalStack;
extern int signalindex;

extern signal_t *nextSignalStack;
extern int nextsignalindex;


#endif
