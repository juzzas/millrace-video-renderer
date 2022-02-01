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

#include "FrameBufferAce.h"
FrameBufferAce::FrameBufferAce(SDL_Renderer *renderer): FrameBufferZ80()
{
    FrameBufferStatus status = init(renderer, pixel_buffer,
                                                   FRAME_BUFFER_ACE_WIDTH,
                                                   FRAME_BUFFER_ACE_HEIGHT,
                                                   SDL_PIXELFORMAT_RGB332);
}


FrameBufferAce::~FrameBufferAce()
{

}


FrameBufferStatus FrameBufferAce::update()
{
    int pixel_row, pixel_col;

    m_z80.read_mem_block(0x9000, screen_ram, 768);
    m_z80.read_mem_block(0x9800, character_ram, 1024);

    for (pixel_row = 0; pixel_row < m_pixel_buffer_height; pixel_row++)
    {
        for (pixel_col = 0; pixel_col < m_pixel_buffer_width; pixel_col++)
        {
            int screen_row = pixel_row / 8;
            int screen_col = pixel_col / 8;

            uint8_t screen_char = screen_ram[(screen_row * 32) + screen_col];

            int screen_row_bit = pixel_row % 8;
            int screen_col_bit = pixel_col % 8;


            uint8_t chr_bitmap_row = character_ram[((screen_char & 0x7f) * 8) + screen_row_bit];

            if ((screen_char & 0x80) == 0x80)
            {
                chr_bitmap_row = ~chr_bitmap_row;
            }

            if (chr_bitmap_row & (0x80 >> screen_col_bit))
            {
                pixel_buffer[(pixel_row * m_pixel_buffer_width) + pixel_col] = 0xff;
            }
            else
            {
                pixel_buffer[(pixel_row * m_pixel_buffer_width) + pixel_col] = 0x00;
            }
        }
    }

    return FrameBuffer::update();
}
