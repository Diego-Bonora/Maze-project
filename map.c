#include "main.h"

/*
This is the map file. Inside the 'map_layout' variable, you'll find the grid for the map.
Changing the values within this variable will modify the map.
There are four options for map creation:
Floor: If the value is 0, a floor will be placed in that map location.
Wall: If the value is 1, a wall will be inserted in that map location.
Spawn: If the value is 2, a spawn point will be created in that location.
End: If the value is 3, an endpoint will be placed in that location.

Note that there can only be one spawn point and one endpoint. If you include more than one, the game will use the first one it reads.
It's crucial to include at least one spawn point. If no spawn points are placed, the game will be bugged, and you won't be able to move or play.
*/

int **generate_map_grid(void)
{
    int flag = 0;

    /* This is the matrix to modify if you want to make your own map */

    int map_layout[16][28] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 2, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1},
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
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    /* Loads the matrix values into the external grid variable */
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 28; x++)
        {
            map_grid[y * 28 + x] = map_layout[y][x];

            if (map_layout[y][x] == 2 && flag == 0)
            {
                square.pos_x = x * 45 + 45 / 2;
                square.pos_y = y * 45 + 45 / 2;
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

    for (y = 0; y < 16; y++)
    {
        for (x = 0; x < 28; x++)
        {
            /* ternary operators to decide wich color to use in the next wall block generation */
            colorId = (y % 2 == 0) ? ((x % 2 == 0) ? 1 : 2) : ((x % 2 != 0) ? 1 : 2);
            wall_color(colorId, instance);

            SDL_Rect box[1] = {x * block, y * block, block, block};

            if (map_grid[y * 28 + x] == 2 && spawn_point == 0) /* spawn point */
            {
                wall_color(3, instance);
                spawn_point = 1;
            }
            else if (map_grid[y * 28 + x] == 3 && end_point == 0) /* end point */
            {
                wall_color(4, instance);
                end_point = 1;
            }
            if (map_grid[y * 28 + x] != 0) /* if not air generates the block */
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