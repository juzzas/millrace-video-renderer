#include <SDL2/SDL.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>

#include "frame_buffer_ace.h"

char *string = "undef";
int integer = 22;
int flag = 0;

#define RESOLUTION_WIDTH  640
#define RESOLUTION_HIGHT  480

#define FRAMEBUFFER_WIDTH  256
#define FRAMEFUFFER_HEIGHT  192

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


int run_loop(void)
{
    FrameBufferStatus status;
    FrameBufferAce frame_buffer;


    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("MillRACE",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RESOLUTION_WIDTH, RESOLUTION_HIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    status = frameBufferAceInit(&frame_buffer, renderer);

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

        frameBufferUpdate(&frame_buffer.base);

        frameBufferRender(&frame_buffer.base);

        frameBufferPresent(&frame_buffer.base);
    }

    frameBufferDestroy(&frame_buffer.base);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


