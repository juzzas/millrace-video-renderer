//
// Created by justins on 14/09/2021.
//

#include "frame_buffer_ace.h"


static FrameBufferStatus frameBufferAceUpdate(FrameBufferBase *base)
{
    FrameBufferAce *frame_buffer = (FrameBufferAce *)base;
    FrameBufferStatus status;
    int pixel_row, pixel_col;

    for (pixel_row = 0; pixel_row < frame_buffer->base.pixel_buffer_height; pixel_row++)
    {
        for (pixel_col = 0; pixel_col < frame_buffer->base.pixel_buffer_width; pixel_col++)
        {
            int screen_row = pixel_row / 8;
            int screen_col = pixel_col / 8;

            uint8_t screen_char = frame_buffer->screen_ram[(screen_row * 32) + screen_col];

            int screen_row_bit = pixel_row % 8;
            int screen_col_bit = pixel_col % 8;


            uint8_t chr_bitmap_row = 0;

            chr_bitmap_row = frame_buffer->character_ram[((screen_char & 0x7f) * 8) + screen_row_bit];

            if ((screen_char & 0x80) == 0x80)
            {
                chr_bitmap_row = ~chr_bitmap_row;
            }

            if (chr_bitmap_row & (0x80 >> screen_col_bit))
                frame_buffer->pixel_buffer[(pixel_row * frame_buffer->base.pixel_buffer_width) + pixel_col] = 0xff;
            else
                frame_buffer->pixel_buffer[(pixel_row * frame_buffer->base.pixel_buffer_width) + pixel_col] = 0x00;

        }

    }

    status = frameBufferBaseUpdate(base);

    return status;
}


FrameBufferStatus frameBufferAceInit(FrameBufferAce* frame_buffer, SDL_Renderer* renderer)
{
    FrameBufferStatus status = frameBufferBaseInit(&frame_buffer->base, renderer, frame_buffer->pixel_buffer,
            FRAME_BUFFER_ACE_WIDTH,
            FRAME_BUFFER_ACE_HEIGHT,
            SDL_PIXELFORMAT_RGB332);

    int i;

    /* override default methods */
    frame_buffer->base.methods.update = frameBufferAceUpdate;

    for (i = 0; i < FRAME_BUFFER_ACE_RAM_CHARACTER_SIZE; i++)
    {
        frame_buffer->character_ram[i] = (i / 8);
    }

    for (i = 0; i < FRAME_BUFFER_ACE_RAM_SCREEN_SIZE; i++)
    {
        frame_buffer->screen_ram[i] = (i & 0xff);
    }

    return status;
}
