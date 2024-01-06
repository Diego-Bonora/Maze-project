#include "main.h"

/*
This function spawns the player in the correct position and resets the bounding box of the player
*/

void player_position(SDL_Instance instance)
{

    /* generates the player using the .bmp file and rendering it */
    SDL_Surface *image = SDL_LoadBMP("player.bmp");
    SDL_Texture *img_texture = SDL_CreateTextureFromSurface(instance.renderer, image);
    SDL_Rect image_rect[1] = {square.pos_x - square.size / 2, square.pos_y - square.size / 2, square.size, square.size};

    SDL_RenderCopyEx(instance.renderer, img_texture, NULL, image_rect, (square.player_angle * 180 / PI), NULL, SDL_FLIP_NONE);
    hitbox(instance);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(img_texture);
}

/*
This function checks if the player has made it to the end of tha maze, then it generates the text telling it so
When the game is over the text stays on the window until the game its closed and the player can not move
*/

int win(SDL_Instance instance)
{
    if (map_grid[(int)square.pos_y / 45 * 28 + (int)square.pos_x / 45] == 3)
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
const Uint8 *KeyState;

void movements(void)
{
    KeyState = SDL_GetKeyboardState(NULL); /* state checker for the player movement */
    if (KeyState[SDL_SCANCODE_W] || KeyState[SDL_SCANCODE_UP])
        move_up();
    if (KeyState[SDL_SCANCODE_S] || KeyState[SDL_SCANCODE_DOWN])
        move_down();
    if (KeyState[SDL_SCANCODE_A] || KeyState[SDL_SCANCODE_LEFT])
        rotate_left();
    if (KeyState[SDL_SCANCODE_D] || KeyState[SDL_SCANCODE_RIGHT])
        rotate_right();
}

void rotate_left(void)
{
    square.player_angle -= 0.1;
    if (square.player_angle < 0)
        square.player_angle += 2 * PI;
    square.delta_x = cos(square.player_angle) * square.movement_speed;
    square.delta_y = sin(square.player_angle) * square.movement_speed;
}

void rotate_right(void)
{
    square.player_angle += 0.1;
    if (square.player_angle > 2 * PI)
        square.player_angle -= 2 * PI;
    square.delta_x = cos(square.player_angle);
    square.delta_y = sin(square.player_angle);
}

void move_up(void)
{
    int x_offset = (square.delta_x < 0) ? -5 : 5;
    int y_offset = (square.delta_y < 0) ? -5 : 5;

    if (map_grid[(int)(square.pos_y / 45) * 28 + (int)((square.pos_x + x_offset) / 45)] != 1)
        square.pos_x += square.delta_x;
    if (map_grid[(int)((square.pos_y + y_offset) / 45) * 28 + (int)(square.pos_x / 45)] != 1)
        square.pos_y += square.delta_y;
}

void move_down(void)
{
    int x_offset = (square.delta_x < 0) ? -5 : 5;
    int y_offset = (square.delta_y < 0) ? -5 : 5;

    if (map_grid[(int)(square.pos_y / 45) * 28 + (int)((square.pos_x - x_offset) / 45)] != 1)
        square.pos_x -= square.delta_x;
    if (map_grid[(int)((square.pos_y - y_offset) / 45) * 28 + (int)(square.pos_x / 45)] != 1)
        square.pos_y -= square.delta_y;
}

/*
End of functions for the movement of the player
*/

/* this function renders a red box arround the player when playing on 2D map */
void hitbox(SDL_Instance instance)
{
    int distance = 5;
    SDL_SetRenderDrawColor(instance.renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(instance.renderer, square.pos_x - distance, square.pos_y - distance, square.pos_x - distance, square.pos_y + distance);
    SDL_RenderDrawLine(instance.renderer, square.pos_x - distance, square.pos_y - distance, square.pos_x + distance, square.pos_y - distance);
    SDL_RenderDrawLine(instance.renderer, square.pos_x - distance, square.pos_y + distance, square.pos_x + distance, square.pos_y + distance);
    SDL_RenderDrawLine(instance.renderer, square.pos_x + distance, square.pos_y - distance, square.pos_x + distance, square.pos_y + distance);
}