#include "main.h"

/*
This is the map file, here you will find the grid for the map inside the initial_values variable.
changing the values inside this variable will modifie the map, there are only 3 options for the map creation.
Floor - if the value is 0, in that place in the map there will be a floor
Wall - if the value is 1, in that place in the map there will be a wall inserted
Spawn - if the value is 2, in that place in the map there will be a spawn point
End - if the value is 3, in that place in the map there will be an end point
There can only be one spawn point and end point, and if you put more than 1 it will only spawn the first one it reads
For the player to spawn there must be 1 spawn point
*/

int **generate_map_grid(void)
{
    int flag = 0;

    /* This is the matrix to modify if you want to make your own map */
    int initial_values[16][28] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 3, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    /* Loads the matrix values into the external grid variable */
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 28; x++)
        {
            map_grid[y][x] = initial_values[y][x];

            if (initial_values[y][x] == 2 && flag == 0)
            {
                square.pos_x = x * 45 + 19;
                square.pos_y = y * 45 + 19;
                flag == 1;
            }
        }
    }
}

/*
This function will read the map grid and generate it on the window with all the diferent blocks
Here we also control the dimension of the block, default being 45, a divisible number between 1260 and 720, the dimensions of the window
*/

void map_struct(SDL_Instance instance)
{
    int y, x, block = 45, spawn_point = 0, end_point = 0, colorId;

    for (y = 0; y < 16; ++y)
    {
        for (x = 0; x < 28; ++x)
        {
            /* ternary operators to decide wich color to use in the next wall block generation */
            colorId = (y % 2 == 0) ? ((x % 2 == 0) ? 1 : 2) : ((x % 2 != 0) ? 1 : 2);
            wall_color(colorId, instance);

            SDL_Rect box[1] = {x * block, y * block, block, block};

            if (map_grid[y][x] == 2 && spawn_point == 0) /* spawn point */
            {
                wall_color(3, instance);
                spawn_point = 1;
            }
            else if (map_grid[y][x] == 3 && end_point == 0) /* end point */
            {
                wall_color(4, instance);
                end_point = 1;
            }
            if (map_grid[y][x] != 0) /* if not air generates the block */
                SDL_RenderFillRect(instance.renderer, &box[0]);
        }
    }
}

/*
This function provides all the diferent colors for the map generation
The draw color works like this:
R - RED
G - GREEN
B - BLUE
A - ALPHA
*/

int wall_color(int num, SDL_Instance instance)
{
    switch (num)
    {
    case 1: /* wall color 1*/
        return SDL_SetRenderDrawColor(instance.renderer, 150, 150, 150, 255);
    case 2: /* wall color 2*/
        return SDL_SetRenderDrawColor(instance.renderer, 120, 120, 120, 255);
    case 3: /* spawn color */
        return SDL_SetRenderDrawColor(instance.renderer, 35, 255, 0, 255);
    case 4: /* end color*/
        return SDL_SetRenderDrawColor(instance.renderer, 255, 35, 0, 255);
    default:
        break;
    }
}