//
// Created by justin on 24/01/2022.
//
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
