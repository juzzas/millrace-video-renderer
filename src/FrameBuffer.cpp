//
// Created by justin on 24/01/2022.
//

#include "FrameBuffer.h"


FrameBuffer::FrameBuffer()
{
}

FrameBuffer::~FrameBuffer()
{

}

FrameBufferStatus
FrameBuffer::init(SDL_Renderer* renderer, uint8_t* pixel_buffer, int width, int height,
                    SDL_PixelFormatEnum pixel_format)
                    {

    m_pixel_buffer = pixel_buffer;
    m_pixel_buffer_width = width;
    m_pixel_buffer_height = height;

    m_pixel_buffer_texture = SDL_CreateTexture(renderer, pixel_format, SDL_TEXTUREACCESS_STREAMING, width, height);
    m_renderer = renderer;

    if (!m_pixel_buffer_texture)
        return FRAMEBUFFER_ERROR_OUT_OF_RESOURCE;

    return FRAMEBUFFER_OK;
}

void FrameBuffer::destroy()
{
    SDL_DestroyTexture(m_pixel_buffer_texture);
}

FrameBufferStatus FrameBuffer::update()
{
    FrameBufferStatus status = FRAMEBUFFER_OK;
    int rc;

    rc = SDL_UpdateTexture(m_pixel_buffer_texture, NULL, m_pixel_buffer, m_pixel_buffer_width);
    if (rc < 0)
        status = FRAMEBUFFER_ERROR_UPDATE;

    return status;
}

FrameBufferStatus FrameBuffer::render()
{
    FrameBufferStatus status = FRAMEBUFFER_OK;
    int rc;

    rc = SDL_RenderClear(m_renderer);
    if (rc < 0)
        status = FRAMEBUFFER_ERROR_RENDER_CLEAR;

    if (rc == 0)
    {
        rc = SDL_RenderCopy(m_renderer, m_pixel_buffer_texture, NULL, NULL);
        if (rc < 0)
            status = FRAMEBUFFER_ERROR_RENDER_COPY;
    }

    return status;
}

FrameBufferStatus FrameBuffer::present()
{
    SDL_RenderPresent(m_renderer);

    return FRAMEBUFFER_OK;
}
