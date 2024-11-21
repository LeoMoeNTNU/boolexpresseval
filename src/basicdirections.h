#ifndef BASICDIRECTIONS_H
#define BASICDIRECTIONS_H

#include "constants.h"



typedef struct direction{
    enum direc dir;
    enum direc oppositedir;
    int x;
    int y;
}direction_t;


extern direction_t directions[];

//Needed by boolports so I made it here. 
direction_t dir(enum direc c);

#endif
