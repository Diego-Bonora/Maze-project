#ifndef Main_h
#define Main_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

extern int map_grid[16][28];

typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *instance, int WIDTH, int HEIGHT);
int poll_events();
void box_struct(SDL_Instance instance);
int **generate_map_grid(void);

#endif