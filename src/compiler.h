#ifndef COMPILER_H
#define COMPILER_H
#include <stdbool.h>

bool parseString(char *arg);

bool isTreeCorrect(char* arg);

void killTree(void* tree);

void *getTree(char *arg);

int depth(void *tree);

void printwholetree(void *tree, int depth);

void analyzeTree(char *arg);
#endif
