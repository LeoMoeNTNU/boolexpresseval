#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "wiresetup.h"

#include "constants.h" //Technically this one isn't required because its already in basicdirections. 
#include "basicdirections.h" //I'm not sure that I require this superset of constants.h

Color_t colorsforallblocks[PIXELSPERROW * PIXELSPERROW];

Color_t grey = {40, 40, 40};
Color_t yellow = {220, 255, 70};

Color_t kindablue = {30, 120, 220};

// Returns the color of the tile at x,y
Color_t tile(int x, int y) { return colorsforallblocks[y * PIXELSPERROW + x]; }
// It gets a little bit worse because it returns the color and not the pointer but the abstraction is nice.

void setTile(Color_t clr, int x, int y)
{
    colorsforallblocks[y * PIXELSPERROW + x] = clr;
}

// sets a bunch of points grey.
// I will have horWire for horizontal wire at some point too.
void horiWire(int xstart, int stabley, int xend)
{
    for (int x = xstart; x <= xend; x++)
    {
        setTile(grey, x, stabley);
    }
}
void vertWire(int stablex, int ystart, int yend)
{
    for (int y = ystart; y <= yend; y++)
    {
        setTile(grey, stablex, y);
    }
}

bool sameas(Color_t a, Color_t b)
{
    return ((a.r == b.r) && (a.g == b.g) && (a.g = b.g));
}
bool isWire(int x, int y)
{
    Color_t clr = colorsforallblocks[y * PIXELSPERROW + x];
    return sameas(clr, grey) || sameas(clr, yellow);
}
bool isTrue(int x, int y){
    return sameas(tile(x,y),yellow);
}

Color_t sameascolor(bool b){
    switch (b)
    {
    case true:
        return yellow;
    case false:
        return grey;
    }
    return (Color_t){0,0,0};//Idk if I'm handling error well. 
}

signal_t bothstacks[2 * SIGSTACKSIZE] = {0}; // this one allocks space for each. It doesnt get used again...
bool originalorder = true;
signal_t *signalStack = bothstacks;
int signalindex = -1;
// It gets initialized at -1 because there are none in it.
// Every time I push, one gets added.
signal_t *nextSignalStack = bothstacks + 100;
int nextsignalindex = -1;

void setallblocks(Color_t clr)
{
    for (int i = 0; i < PIXELSPERROW * PIXELSPERROW; i++)
    {
        colorsforallblocks[i] = clr;
    }
}

// I think I have tested this one.



