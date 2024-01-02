#include "main.h"

/*
This function spawns the player in the correct position and resets the bounding box of the player
*/

void player_position(SDL_Instance instance)
{
    int extra_pixel = square.size - 1;

    /* resets the four corners bounding box using x and y position of the player */
    square.top_left[1] = square.pos_x, square.top_left[0] = square.pos_y;
    square.top_right[1] = square.pos_x + extra_pixel, square.top_right[0] = square.pos_y;
    square.bottom_left[1] = square.pos_x, square.bottom_left[0] = square.pos_y + extra_pixel;
    square.bottom_right[1] = square.pos_x + extra_pixel, square.bottom_right[0] = square.pos_y + extra_pixel;

    /* generates the player using the .bmp file and rendering it */
    SDL_Surface *image = SDL_LoadBMP("player.bmp");
    SDL_Texture *img_texture = SDL_CreateTextureFromSurface(instance.renderer, image);
    SDL_Rect image_rect[1] = {square.pos_x, square.pos_y, square.size, square.size};

    SDL_RenderCopy(instance.renderer, img_texture, NULL, image_rect);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(img_texture);
}

/*
This function checks if the player has made it to the end of tha maze, then it generates the text telling it so
When the game is over the text stays on the window until the game its closed and the player can not move
*/

int win(SDL_Instance instance)
{
    if (map_grid[square.pos_y / 45][square.pos_x / 45] == 3)
    {

        TTF_Init();

        instance.font = TTF_OpenFont("MouldyCheeseRegular-WyMWG.ttf", 40); /*read font file*/
        if (instance.font == NULL)
            printf("font not loaded: %s\n", TTF_GetError()); /*check for errors*/

        SDL_Surface *textSurface = TTF_RenderText_Blended_Wrapped(instance.font, "WIN", (SDL_Color){0, 255, 0, 255}, 210); /*text to print and font color*/
        if (textSurface == NULL)
            printf("texture not created: %s\n", TTF_GetError()); /*check for errors*/

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(instance.renderer, textSurface); /*generate the texture for the font using the surface*/
        if (textTexture == NULL)
            printf("texture not created: %s\n", TTF_GetError());

        SDL_RenderCopy(instance.renderer, textTexture, NULL, NULL); /*prints the font in the window*/

        SDL_RenderPresent(instance.renderer);
        while (1)
        {
            if (poll_events() == 1)
                break;
        }

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        return 1;
    }

    return 0;
}

/*
Start of functions for the movement of the player

This functions utilizes the bounding box to check if the player can move or if its hitting any wall
The positions are divided by 45 because each block measures 45*45px and by dividing it you can check the players position iside the map grid
*/

void move_up(void)
{
    if (map_grid[(square.top_left[0] - square.movement_speed) / 45][square.top_left[1] / 45] != 1 &&
        map_grid[(square.top_right[0] - square.movement_speed) / 45][square.top_right[1] / 45] != 1)
        square.pos_y -= square.movement_speed;
}

void move_down(void)
{
    if (map_grid[(square.bottom_left[0] + square.movement_speed) / 45][square.bottom_left[1] / 45] != 1 &&
        map_grid[(square.bottom_right[0] + square.movement_speed) / 45][square.bottom_right[1] / 45] != 1)
        square.pos_y += square.movement_speed;
}

void move_left(void)
{
    if (map_grid[square.top_left[0] / 45][(square.top_left[1] - square.movement_speed) / 45] != 1 &&
        map_grid[square.bottom_left[0] / 45][(square.bottom_left[1] - square.movement_speed) / 45] != 1)
        square.pos_x -= square.movement_speed;
}

void move_right(void)
{
    if (map_grid[square.top_right[0] / 45][(square.top_right[1] + square.movement_speed) / 45] != 1 &&
        map_grid[square.bottom_right[0] / 45][(square.bottom_right[1] + square.movement_speed) / 45] != 1)
        square.pos_x += square.movement_speed;
}

/*
End of functions for the movement of the player
*/