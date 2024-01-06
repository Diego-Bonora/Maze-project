#include "main.h"

int map_grid[16 * 28];
int map_grid_floor[16 * 28];
float PI = 3.14159265359, PI2 = 3.14159265359 / 2, PI3 = 3 * 3.14159265359 / 2, DR = 0.0174533;
struct Player square;
int WIDTH = 1260, HEIGHT = 720;

/*
Main function that sets some constant values, calls the initializer function, draws the game and deletes all when closed
*/

int main(int argc, char *argv[])
{
    generate_map_grid();

    /* size and movement speed of the player */
    square.size = 7;
    square.movement_speed = 1;
    square.player_angle = PI / 2;
    square.delta_x = cos(square.player_angle) * square.movement_speed;
    square.delta_y = sin(square.player_angle) * square.movement_speed;

    SDL_Instance instance;

    if (init_instance(&instance, WIDTH, HEIGHT) != 0)
        return 1;

    while (1)
    {
        SDL_SetRenderDrawBlendMode(instance.renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255); /* background color of the window, in this case white */
        SDL_RenderClear(instance.renderer);                            /* clears the screen */
        if (poll_events() == 1)
            break;

        movements();

        /* if you have all 3 lines at once, the view will be buggy */

        // map_struct(instance);      /* if this line is commented out, the 2D map will be disabled */
        // player_position(instance); /* if this line is commented out, the 2D player position will be disabled */

        draw_rays(instance); /* if this line is commented out, 3D raycast will be disabled */

        if (win(instance) == 1)
            break;

        SDL_RenderPresent(instance.renderer);
    }

    SDL_DestroyRenderer(instance.renderer);
    SDL_DestroyWindow(instance.window);

    SDL_Quit();
    return 0;
}

/*
This function initializes the variables for the window and renderer
*/

int init_instance(SDL_Instance *instance, int WIDTH, int HEIGHT)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    instance->window = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (instance->window == NULL)
    {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    instance->renderer = SDL_CreateRenderer(instance->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (instance->renderer == NULL)
    {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(instance->window);
        SDL_Quit();
        return 1;
    }
    return 0;
}

/*
Poll function for reading events
*/

int poll_events()
{
    SDL_Event event;
    SDL_KeyboardEvent key;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return 1;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return 1; // Example: Quit on pressing Escape key
            }
            break;
        }
    }
}