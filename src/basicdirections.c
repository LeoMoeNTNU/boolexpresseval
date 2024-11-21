#include "basicdirections.h"

#define dirup {UP, DOWN, 0, 1 }
#define dirdown {DOWN, UP, 0, -1 }
#define dirright {RIGHT, LEFT, 1, 0}
#define dirleft {LEFT, RIGHT, -1, 0 }

direction_t directions[] = {dirup, dirdown, dirright, dirleft};

//This one was needed by boolports. 
direction_t dir(enum direc c){
    switch (c)
    {
    case RIGHT:
        return (direction_t)dirright;
    case LEFT:
        return (direction_t)dirleft;
    case UP:
        return (direction_t)dirup;
    case DOWN:
        return (direction_t)dirdown;  
    }
    return (direction_t){0,0,0,0}; //No idea if this works great but also dont give a shit
}