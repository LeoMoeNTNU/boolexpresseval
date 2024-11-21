#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>


#include "wiresetup.h"
#include "boolports.h"
#include "signalling.h"
#include "compiler.h"
#include "makeVisualTree.h"


///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
int game_is_running = false;
int last_frame_time = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;







//I think I have tested this one. 
void displayallblocks()
{

    for (int i = 0; i < PIXELSPERROW * PIXELSPERROW; i++)
    {
        int x = i % PIXELSPERROW;
        int y = i / PIXELSPERROW;
        Color_t clr = tile(x, y);//should use soon...
        SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, 255);
        SDL_Rect rect = {x*PIXELWIDTH, y*PIXELWIDTH, PIXELWIDTH, PIXELWIDTH};
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_RenderPresent(renderer);
    return;
}








///////////////////////////////////////////////////////////////////////////////
// Function to initialize our SDL window
///////////////////////////////////////////////////////////////////////////////
int initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);
    if (!window)
    {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Function to poll SDL events and process keyboard input
///////////////////////////////////////////////////////////////////////////////
void process_input(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            game_is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                game_is_running = false;
            }
            break;
            // I havent looked at this code yet and I may have to at some point...
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function to destroy SDL window and renderer
///////////////////////////////////////////////////////////////////////////////
void destroy_window(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void setwiresandsignals(){
    vertWire(10,20,25);
    horiWire(25,15,60);
    signal_t startsignal={10,20,UP,yellow};//I will definitely get errors orno behavior now...
    pushSigStack(startsignal);


    horiWire(70,20,40);
    vertWire(50,30,80);
    signal_t startsignal2 = {70, 26, UP, yellow};
    pushSigStack(startsignal2);
}

void setup2(){//not using it right now, can be used for testing. 
    int topy=5;
    int midy=10;
    int boty=15;
    int startx=0;//obviously
    int firstwirx=5;
    int farx=10;

    //ok so everything is weird apparently. 
    
    //How to draw a horizontal wire:
    //horiWire(40,10,100);
    
    //topwire:
    horiWire(startx,topy,firstwirx);


    //botwire:
    horiWire(startx,boty,firstwirx);

    vertWire(firstwirx,topy,boty);

    horiWire(firstwirx,midy,farx);

    makePort(firstwirx,midy,AND);

    signal_t s = {startx, topy, UP, yellow};
    pushSigStack(s);
    signal_t s2={startx+3,boty,RIGHT,yellow};
    pushSigStack(s2);
}


///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *args[])
{
    srand(time(NULL));
    game_is_running = initialize_window();


    setallblocks(kindablue);
    
    //setwiresandsignals();
    //setup2();
    setupboolports();


    printf("true is %d\n",true);
    char a[]="abcd";
    char b[]="1";
    char c[]="(0*1)";
    char d[]="((0+1)*1)";
    char e[] = "((0+1)*1+1)";
    char f[]="(((0+1)*(1+1))+1)";
    if(argc!=2){
        printf("not 2 arguments...\n");
        return ;
    }
    makeSyntaxTree(args[1]);

    

    displayallblocks();

    clock_t prev_time;
    prev_time = clock();

    //time_t starttime=time(NULL);//Idk if this one is being used yet. 

    //time_t current_time=time(NULL);

    while (game_is_running)
    {
        process_input();//I think this one is only used to close the app but I dont know for sure. 

        clock_t current_time=clock();
        int delta_time_millis=current_time-prev_time;

       // time_t tim=time(NULL);
        if(delta_time_millis>600){//This means that another second has passed.
            
            
            displayallblocks();

         //   current_time=tim;
            updateverything(); 
            
            prev_time=current_time;
        }


        // update(); Take this one back to get the ball moving.
        //render(); this one may fuck with my shit but is nice.
    }

    destroy_window();

    return 0;
}
