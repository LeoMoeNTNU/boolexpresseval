#include <stdbool.h>
#ifndef COMPILERNODE_H
#define COMPILERNODE_H
typedef struct Node
{
    bool error;
    bool bottom;
    bool value;
    char operand;
    struct Node *leftp;
    struct Node *rightp;
} Node_t;

#endif