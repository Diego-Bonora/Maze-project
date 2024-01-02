#ifndef Main_h
#define Main_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

extern int map_grid[16][28];

/*
Struct for the main instance variables
*/

typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
} SDL_Instance;

/*
Struct for all the player data
*/

struct Player
{
    int size;
    int movement_speed;
    int pos_x;
    int pos_y;
    int top_left[2];
    int top_right[2];
    int bottom_left[2];
    int bottom_right[2];
};

extern struct Player square;

/* main.c functions */
int init_instance(SDL_Instance *instance, int WIDTH, int HEIGHT);
int poll_events();

/*map.c functions*/
int **generate_map_grid(void);
void map_struct(SDL_Instance instance);
int wall_color(int num, SDL_Instance instance);

/*player.c functions*/
void player_position(SDL_Instance instance);
int win(SDL_Instance instance);
void move_up(void);
void move_down(void);
void move_left(void);
void move_right(void);

#endif