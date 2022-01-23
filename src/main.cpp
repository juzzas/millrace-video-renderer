
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <SDL2/SDL.h>

#include "frame_buffer_ace.h"
#include "frame_buffer_test.h"

char *string = "undef";
int integer = 22;
int flag = 0;

#define RESOLUTION_WIDTH  1024
#define RESOLUTION_HIGHT  768

union
{
    FrameBufferBase base;
    FrameBufferAce ace;
    FrameBufferTest test;
} S_frame_buffer;

FrameBufferStatus run_loop(void);

int main(int argc, char *argv[])
{
    try {
        // Declare the supported options.
        po::options_description general("General options");
        general.add_options()
            ("help,h", "produce help message")
            ("m_verbose,v", "increase verbosity");

        po::options_description input("Output options");
        input.add_options()
            ("output,o", po::value<std::string>()->value_name("FILE"),
             "output file name")
            ("transport-stream,t", po::value<std::vector<std::string>>()->value_name("FILE"),
             "add transport stream file as dummy frontend");

        // Hidden options, will be allowed both on command line and
        // in config file, but will not be shown to the user.
        po::options_description hidden("Hidden options");
        hidden.add_options()
            ("input-file", po::value< std::vector<std::string> >(), "input file") ;

        po::positional_options_description p;
        p.add("input-file", -1);

        po::options_description all("Allowed options");
        all.add(general).add(input).add(hidden);

        po::variables_map args;
        po::store(po::command_line_parser(argc, argv).options(all).positional(p).run(), args);
        po::notify(args);

        if (args.count("help")) {
            std::cout << "Usage: " << argv[0] << " [OPTION]... [FILE]..." << std::endl
                      << std::endl
                      << general << std::endl
                      << input << std::endl;
            return 1;
        }


    }
    catch (const po::error& ex) {
        std::cerr << ex.what() << '\n';
    }

    return run_loop();
}


FrameBufferStatus run_loop(void)
{
    FrameBufferStatus status;

    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("MillRACE test",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RESOLUTION_WIDTH, RESOLUTION_HIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    status = frameBufferAceInit(&S_frame_buffer.ace, renderer);
    //status = frameBufferTestInit(&S_frame_buffer.test, renderer);
    if (status != FRAMEBUFFER_OK)
        return status;

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

        frameBufferUpdate(&S_frame_buffer.base);

        frameBufferRender(&S_frame_buffer.base);

        frameBufferPresent(&S_frame_buffer.base);
    }

    frameBufferDestroy(&S_frame_buffer.base);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return FRAMEBUFFER_OK;
}


