//
// Created by justins on 14/09/2021.
//

#ifndef FRAME_BUFFER_BASE_H
#define FRAME_BUFFER_BASE_H

#include <SDL2/SDL.h>

#include "frame_buffer.h"


struct FrameBufferBase
{
    FrameBufferMethods  methods;

    uint8_t *pixel_buffer;
    int pixel_buffer_width;
    int pixel_buffer_height;

    SDL_Texture *pixel_buffer_texture;
    SDL_Renderer *renderer;
};


/**
 * Initialise Frame Buffer Base structure
 *
 * @param width
 * @param height
 * @param pixel_format
 *
 * @return pointer to FrameBufferBase if successful, else NULL
 */
FrameBufferStatus
frameBufferBaseInit(FrameBufferBase* base, SDL_Renderer* renderer, uint8_t* pixel_buffer, int width, int height,
        SDL_PixelFormatEnum pixel_format);


/**
 * Free the Frame Buffer base structure
 *
 * @param base
 */
void frameBufferBaseDestroy(FrameBufferBase *base);


FrameBufferStatus frameBufferBaseUpdate(FrameBufferBase *base);

FrameBufferStatus frameBufferBaseRender(FrameBufferBase *base);

FrameBufferStatus frameBufferBasePresent(FrameBufferBase *base);

#endif //FRAME_BUFFER_BASE_H
