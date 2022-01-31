// Copyright 2022 Justin Skists <justin.skists@juzza.co.uk>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <stdint.h>
#include <SDL2/SDL.h>

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

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


class FrameBuffer
{
public:
    FrameBuffer();
    virtual ~FrameBuffer();

    FrameBufferStatus init(SDL_Renderer* renderer, uint8_t* pixel_buffer, int width, int height,
                           SDL_PixelFormatEnum pixel_format);
    void destroy();
    virtual FrameBufferStatus update();
    FrameBufferStatus render();
    FrameBufferStatus present();

private:
    uint8_t *m_pixel_buffer;

    SDL_Texture *m_pixel_buffer_texture;
    SDL_Renderer *m_renderer;

protected:
    int m_pixel_buffer_height;
    int m_pixel_buffer_width;
};


#endif //FRAMEBUFFER_H
