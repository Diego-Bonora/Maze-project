#ifndef Main_h
#define Main_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

extern float PI, PI2, PI3, DR;
extern int map_grid[16 * 28];
extern int All_Textures[4090];

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
    float pos_x;
    float pos_y;
    double player_angle;
    float delta_x;
    float delta_y;
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
void movements(void);
void move_up(void);
void move_down(void);
void rotate_left(void);
void rotate_right(void);
void hitbox(SDL_Instance instance);

/* 3D rendering */
void draw_rays(SDL_Instance instance);
float dist(float ax, float ay, float bx, float by, float ang);
float FixAng(float a);

#endif