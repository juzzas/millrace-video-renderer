//
// Created by justins on 14/09/2021.
//

#include "frame_buffer_base.h"

FrameBufferStatus
frameBufferBaseInit(FrameBufferBase* base, SDL_Renderer* renderer, uint8_t* buffer, int width, int height,
        SDL_PixelFormatEnum pixel_format)
{
    if (!base)
        return FRAMEBUFFER_ERROR_INVALID_PARAMETER;

    base->buffer = buffer;
    base->width = width;
    base->height = height;

    base->framebuffer = SDL_CreateTexture(renderer, pixel_format, SDL_TEXTUREACCESS_STREAMING, width, height);
    base->renderer = renderer;

    base->methods.destroy = frameBufferBaseDestroy;
    base->methods.update = frameBufferBaseUpdate;
    base->methods.render = frameBufferBaseRender;
    base->methods.present = frameBufferBasePresent;

    if (!base->framebuffer)
        return FRAMEBUFFER_ERROR_OUT_OF_RESOURCE;

    return FRAMEBUFFER_OK;
}


void frameBufferBaseDestroy(FrameBufferBase *base)
{
    SDL_DestroyTexture(base->framebuffer);
}

FrameBufferStatus frameBufferBaseUpdate(FrameBufferBase *base)
{
    FrameBufferStatus status = FRAMEBUFFER_OK;
    int rc;

    rc = SDL_UpdateTexture(base->framebuffer, NULL, base->buffer, base->width);
    if (rc < 0)
        status = FRAMEBUFFER_ERROR_UPDATE;

    return status;
}

FrameBufferStatus frameBufferBaseRender(FrameBufferBase *base)
{
    FrameBufferStatus status = FRAMEBUFFER_OK;
    int rc;

    rc = SDL_RenderClear(base->renderer);
    if (rc < 0)
        status = FRAMEBUFFER_ERROR_RENDER_CLEAR;

    if (rc == 0)
    {
        rc = SDL_RenderCopy(base->renderer, base->framebuffer, NULL, NULL);
        if (rc < 0)
            status = FRAMEBUFFER_ERROR_RENDER_COPY;
    }

    return status;
}

FrameBufferStatus frameBufferBasePresent(FrameBufferBase *base)
{
    SDL_RenderPresent(base->renderer);

    return FRAMEBUFFER_OK;
}

