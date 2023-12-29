#include "main.h"

int main(int argc, char *argv[])
{
    SDL_Instance instance;

    if (init_instance(&instance) != 0)
        return 1;

    while (1)
    {
        SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
        SDL_RenderClear(instance.renderer);
        if (poll_events() == 1)
            break;
        /*
        draws
        */
        SDL_RenderPresent(instance.renderer);
    }
    SDL_DestroyRenderer(instance.renderer);
    SDL_DestroyWindow(instance.window);
    SDL_Quit();
    return 0;
}

int init_instance(SDL_Instance *instance)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    instance->window = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1260, 720, SDL_WINDOW_ALLOW_HIGHDPI);
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