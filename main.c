#include "main.h"

int map_grid[16][28];

int main(int argc, char *argv[])
{
    generate_map_grid();
    int WIDTH = 1260, HEIGHT = 720;

    SDL_Instance instance;

    if (init_instance(&instance, WIDTH, HEIGHT) != 0)
        return 1;

    while (1)
    {
        SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);
        SDL_RenderClear(instance.renderer);
        if (poll_events() == 1)
            break;
        /*
        draws
        */
        box_struct(instance);
        SDL_RenderPresent(instance.renderer);
    }
    SDL_DestroyRenderer(instance.renderer);
    SDL_DestroyWindow(instance.window);
    SDL_Quit();
    return 0;
}

void box_struct(SDL_Instance instance)
{
    int x, y, w = 45, h = 45;

    for (y = 0; y < 16; ++y)
    {
        for (x = 0; x < 28; ++x)
        {
            if (y % 2 == 0)
            {
                if (x % 2 == 0)
                    SDL_SetRenderDrawColor(instance.renderer, 150, 150, 150, 255); // Set color to red (R, G, B, A)
                else
                    SDL_SetRenderDrawColor(instance.renderer, 120, 120, 120, 255); // Set color to red (R, G, B, A)
            }
            else
            {
                if (x % 2 != 0)
                    SDL_SetRenderDrawColor(instance.renderer, 150, 150, 150, 255); // Set color to red (R, G, B, A)
                else
                    SDL_SetRenderDrawColor(instance.renderer, 120, 120, 120, 255); // Set color to red (R, G, B, A)
            }
            if (map_grid[y][x] == 1)
            {
                SDL_Rect box[1] = {x * 45, y * 45, w, h};
                SDL_RenderFillRect(instance.renderer, &box[0]);
            }
        }
    }
}

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
            key = event.key;
            if (key.keysym.scancode == 0X29)
                return 1;
            break;
        }
    }
}