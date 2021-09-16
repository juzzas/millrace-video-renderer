//
// Created by justins on 14/09/2021.
//

#include "frame_buffer_ace.h"


static FrameBufferStatus frameBufferAceUpdate(FrameBufferBase *base)
{
    FrameBufferAce *frame_buffer = (FrameBufferAce *)base;

    FrameBufferStatus status;

    memset(frame_buffer->pixel_buffer, 0, (FRAME_BUFFER_ACE_WIDTH * FRAME_BUFFER_ACE_HEIGHT));

    status = frameBufferBaseUpdate(base);

    return status;
}


FrameBufferStatus frameBufferAceInit(FrameBufferAce* frame_buffer, SDL_Renderer* renderer)
{
    FrameBufferStatus status = frameBufferBaseInit(&frame_buffer->base, renderer, frame_buffer->pixel_buffer,
            FRAME_BUFFER_ACE_WIDTH,
            FRAME_BUFFER_ACE_HEIGHT,
            SDL_PIXELFORMAT_RGB332);

    /* override default methods */
    frame_buffer->base.methods.update = frameBufferAceUpdate;

    return status;
}
