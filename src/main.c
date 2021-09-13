#include <SDL2/SDL.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>

char *string = "undef";
int integer = 22;
int flag = 0;

int run_loop(void);

int main(int argc, char *argv[])
{
    int option_index = 0;
    int c;

    struct option long_options[] = {
            { "string",         required_argument,  NULL, 's' },
            { "integer",        required_argument,  NULL, 'i' },
            { "flag",           no_argument,        NULL, 'f' },
            { 0, 0, 0, 0}
    };

    char *optstring = "s:i:f";

    while (1) {
        c = getopt_long(argc, argv, optstring, long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 's': string   = optarg;        break;
        case 'i': integer  = atoi(optarg);  break;
        case 'f': flag     = 1;             break;
        default:
            printf("Usage: %s [...]\n", argv[0]);
            exit(1);
        }
    }

    printf("String:  %s\n", string);
    printf("Integer: %d\n", integer);
    printf("Flag:    %s\n", flag? "yes" : "no");

    if (optind < argc) {
        printf("Non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    return run_loop();
}

static uint8_t buffer[640*480];

int run_loop(void)
{
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL2 Starter Project",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING, 640, 480);

    for (int row = 0; row < 256; row++)
    {
        memset(&buffer[row * 640], row, 640);
    }

    while (!quit)
    {
        SDL_Delay(10);
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }

        SDL_UpdateTexture(framebuffer, NULL, buffer, 640);


        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, framebuffer, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


