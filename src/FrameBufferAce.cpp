//
// Created by justin on 24/01/2022.
//

#include "FrameBufferAce.h"
FrameBufferAce::FrameBufferAce(SDL_Renderer *renderer): FrameBufferZ80()
{
    FrameBufferStatus status = init(renderer, pixel_buffer,
                                                   FRAME_BUFFER_ACE_WIDTH,
                                                   FRAME_BUFFER_ACE_HEIGHT,
                                                   SDL_PIXELFORMAT_RGB332);

    int i;

    for (i = 0; i < FRAME_BUFFER_ACE_RAM_CHARACTER_SIZE; i++)
    {
        character_ram[i] = (i / 8);
    }

    for (i = 0; i < FRAME_BUFFER_ACE_RAM_SCREEN_SIZE; i++)
    {
        screen_ram[i] = (i & 0xff);
    }

}
FrameBufferAce::~FrameBufferAce()
{

}
FrameBufferStatus FrameBufferAce::update()
{
    FrameBufferStatus status;
    int pixel_row, pixel_col;

    uint8_t z80_status = m_z80.read_status();

    m_z80.read_mem_block(0x0000, screen_ram, 16);

    for (pixel_row = 0; pixel_row < m_pixel_buffer_height; pixel_row++)
    {
        for (pixel_col = 0; pixel_col < m_pixel_buffer_width; pixel_col++)
        {
            int screen_row = pixel_row / 8;
            int screen_col = pixel_col / 8;

            uint8_t screen_char = screen_ram[(screen_row * 32) + screen_col];

            int screen_row_bit = pixel_row % 8;
            int screen_col_bit = pixel_col % 8;


            uint8_t chr_bitmap_row = 0;

            chr_bitmap_row = character_ram[((screen_char & 0x7f) * 8) + screen_row_bit];

            if ((screen_char & 0x80) == 0x80)
            {
                chr_bitmap_row = ~chr_bitmap_row;
            }

            if (chr_bitmap_row & (0x80 >> screen_col_bit))
                pixel_buffer[(pixel_row * m_pixel_buffer_width) + pixel_col] = 0xff;
            else
                pixel_buffer[(pixel_row * m_pixel_buffer_width) + pixel_col] = 0x00;

        }

    }

    return FrameBuffer::update();
}
