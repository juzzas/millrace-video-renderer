//
// Created by justin on 25/01/2022.
//

#include "FrameBufferFactory.h"

#include <memory>

std::shared_ptr<FrameBuffer> FrameBufferFactory::make_frame_buffer(const std::string &type, SDL_Renderer *renderer)
{
    if (type == "ace")
    {
        return std::make_shared<FrameBufferAce>(renderer);
    }
    else if (type == "test")
    {
        return std::make_shared<FrameBufferTest>(renderer);
    }

    return {nullptr};
}
