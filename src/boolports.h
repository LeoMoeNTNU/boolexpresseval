#ifndef BOOLPORTS_H
#define BOOLPORTS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "wiresetup.h"
//TODO: need a -c file and to implement the interface. 
    //I think there is a data structure in there no one else needs to meet ever :)


enum Port
{
    AND,
    OR,
    NAND,
    NOR
};

//This one probably has to be alloced. 
typedef struct {
    signal_t* sP;
    int len;
}signal_t_array;

void setupboolports();
void makePort(int x, int y, enum Port p);
void notifyPort(int x, int y);
bool isPort(int x, int y);
signal_t_array getsigsfromports();

#endif