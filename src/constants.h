#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800


#define PIXELSPERROW 160
#define PIXELWIDTH WINDOW_WIDTH/PIXELSPERROW
#define MAXSIGNALS 100

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

enum direc{UP,DOWN,LEFT,RIGHT};

// stuff for processor...
typedef struct Color
{
    char r;
    char g;
    char b;
} Color_t;



#define SIGSTACKSIZE 100



#endif