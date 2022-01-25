//
// Created by justin on 25/01/2022.
//
#include <memory>
#include <string>

#include "FrameBufferAce.h"
#include "FrameBufferTest.h"


#ifndef FRAMEBUFFERFACTORY_H
#define FRAMEBUFFERFACTORY_H



class FrameBufferFactory
{
public:
    static std::shared_ptr<FrameBuffer> make_frame_buffer(const std::string &type, SDL_Renderer *renderer);
};


#endif //FRAMEBUFFERFACTORY_H
