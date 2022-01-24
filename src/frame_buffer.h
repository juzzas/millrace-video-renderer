//
// Created by justins on 14/09/2021.
//

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <SDL2/SDL.h>

typedef enum
{
    FRAMEBUFFER_OK,
    FRAMEBUFFER_ERROR_NOT_IMPLEMENTED,
    FRAMEBUFFER_ERROR_INVALID_PARAMETER,
    FRAMEBUFFER_ERROR_OUT_OF_RESOURCE,
    FRAMEBUFFER_ERROR_UPDATE,
    FRAMEBUFFER_ERROR_RENDER_CLEAR,
    FRAMEBUFFER_ERROR_RENDER_COPY
} FrameBufferStatus;

typedef struct FrameBufferBase FrameBufferBase;

typedef void (*FunctionFrameBufferDestroy)(FrameBufferBase *base);
typedef FrameBufferStatus (*FunctionFrameBufferUpdate)(FrameBufferBase *base);
typedef FrameBufferStatus (*FunctionFrameBufferRender)(FrameBufferBase *base);
typedef FrameBufferStatus (*FunctionFrameBufferPresent)(FrameBufferBase *base);


typedef struct FrameBufferMethods
{
    FunctionFrameBufferDestroy destroy;
    FunctionFrameBufferUpdate update;
    FunctionFrameBufferRender render;
    FunctionFrameBufferPresent present;
} FrameBufferMethods;


/**
 * Free the Frame Buffer base structure
 *
 * @param base
 */
void frameBufferDestroy(FrameBufferBase *base);


FrameBufferStatus frameBufferUpdate(FrameBufferBase *base);

FrameBufferStatus frameBufferRender(FrameBufferBase *base);

FrameBufferStatus frameBufferPresent(FrameBufferBase *base);

#endif //FRAME_BUFFER_H
