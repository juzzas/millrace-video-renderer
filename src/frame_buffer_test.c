//
// Created by justins on 14/09/2021.
//

#include "frame_buffer_test.h"

static const char *S_test_data = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque vehicula lorem "
                                 "a felis auctor pellentesque. Cras pharetra sapien quam, volutpat aliquet magna finibus "
                                 "a. Cras vulputate turpis faucibus nunc sagittis volutpat. Proin vehicula purus neque, "
                                 "vestibulum sagittis ante rutrum pulvinar. Phasellus vulputate, est eu iaculis consequat, "
                                 "augue nunc elementum tellus, quis iaculis turpis mi eget orci. Quisque imperdiet, nibh "
                                 "vitae pharetra aliquet, nisl augue eleifend massa, quis hendrerit eros lacus sit amet "
                                 "dolor. Nam venenatis consequat justo sit amet scelerisque. Vivamus pharetra non diam "
                                 "quis elementum. Nam dignissim, arcu quis feugiat ultricies, odio turpis mollis massa, "
                                 "vitae volutpat ligula sapien sed sem. Vestibulum porta pellentesque efficitur.";

static unsigned char S_test_font[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10,
        0x10, 0x00, 0x10, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x24, 0x7e, 0x24, 0x24, 0x7e, 0x24, 0x00, 0x00, 0x08, 0x3e, 0x28,
        0x3e, 0x0a, 0x3e, 0x08, 0x00, 0x62, 0x64, 0x08, 0x10, 0x26, 0x46, 0x00,
        0x00, 0x10, 0x28, 0x10, 0x2a, 0x44, 0x3a, 0x00, 0x00, 0x08, 0x10, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x00,
        0x00, 0x20, 0x10, 0x10, 0x10, 0x10, 0x20, 0x00, 0x00, 0x00, 0x14, 0x08,
        0x3e, 0x08, 0x14, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00,
        0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00,
        0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x3c, 0x46, 0x4a,
        0x52, 0x62, 0x3c, 0x00, 0x00, 0x18, 0x28, 0x08, 0x08, 0x08, 0x3e, 0x00,
        0x00, 0x3c, 0x42, 0x02, 0x3c, 0x40, 0x7e, 0x00, 0x00, 0x3c, 0x42, 0x0c,
        0x02, 0x42, 0x3c, 0x00, 0x00, 0x08, 0x18, 0x28, 0x48, 0x7e, 0x08, 0x00,
        0x00, 0x7e, 0x40, 0x7c, 0x02, 0x42, 0x3c, 0x00, 0x00, 0x3c, 0x40, 0x7c,
        0x42, 0x42, 0x3c, 0x00, 0x00, 0x7e, 0x02, 0x04, 0x08, 0x10, 0x10, 0x00,
        0x00, 0x3c, 0x42, 0x3c, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x3c, 0x42, 0x42,
        0x3e, 0x02, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00,
        0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x10, 0x20, 0x00, 0x00, 0x04, 0x08,
        0x10, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x00,
        0x00, 0x00, 0x10, 0x08, 0x04, 0x08, 0x10, 0x00, 0x00, 0x3c, 0x42, 0x04,
        0x08, 0x00, 0x08, 0x00, 0x00, 0x3c, 0x4a, 0x56, 0x5e, 0x40, 0x3c, 0x00,
        0x00, 0x3c, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x00, 0x00, 0x7c, 0x42, 0x7c,
        0x42, 0x42, 0x7c, 0x00, 0x00, 0x3c, 0x42, 0x40, 0x40, 0x42, 0x3c, 0x00,
        0x00, 0x78, 0x44, 0x42, 0x42, 0x44, 0x78, 0x00, 0x00, 0x7e, 0x40, 0x7c,
        0x40, 0x40, 0x7e, 0x00, 0x00, 0x7e, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x00,
        0x00, 0x3c, 0x42, 0x40, 0x4e, 0x42, 0x3c, 0x00, 0x00, 0x42, 0x42, 0x7e,
        0x42, 0x42, 0x42, 0x00, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00,
        0x00, 0x02, 0x02, 0x02, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x44, 0x48, 0x70,
        0x48, 0x44, 0x42, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7e, 0x00,
        0x00, 0x42, 0x66, 0x5a, 0x42, 0x42, 0x42, 0x00, 0x00, 0x42, 0x62, 0x52,
        0x4a, 0x46, 0x42, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00,
        0x00, 0x7c, 0x42, 0x42, 0x7c, 0x40, 0x40, 0x00, 0x00, 0x3c, 0x42, 0x42,
        0x52, 0x4a, 0x3c, 0x00, 0x00, 0x7c, 0x42, 0x42, 0x7c, 0x44, 0x42, 0x00,
        0x00, 0x3c, 0x40, 0x3c, 0x02, 0x42, 0x3c, 0x00, 0x00, 0xfe, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00,
        0x00, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00, 0x42, 0x42, 0x42,
        0x42, 0x5a, 0x24, 0x00, 0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00,
        0x00, 0x82, 0x44, 0x28, 0x10, 0x10, 0x10, 0x00, 0x00, 0x7e, 0x04, 0x08,
        0x10, 0x20, 0x7e, 0x00, 0x00, 0x0e, 0x08, 0x08, 0x08, 0x08, 0x0e, 0x00,
        0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00, 0x70, 0x10, 0x10,
        0x10, 0x10, 0x70, 0x00, 0x00, 0x10, 0x38, 0x54, 0x10, 0x10, 0x10, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x1c, 0x22, 0x78,
        0x20, 0x20, 0x7e, 0x00, 0x00, 0x00, 0x38, 0x04, 0x3c, 0x44, 0x3c, 0x00,
        0x00, 0x20, 0x20, 0x3c, 0x22, 0x22, 0x3c, 0x00, 0x00, 0x00, 0x1c, 0x20,
        0x20, 0x20, 0x1c, 0x00, 0x00, 0x04, 0x04, 0x3c, 0x44, 0x44, 0x3c, 0x00,
        0x00, 0x00, 0x38, 0x44, 0x78, 0x40, 0x3c, 0x00, 0x00, 0x0c, 0x10, 0x18,
        0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x3c, 0x44, 0x44, 0x3c, 0x04, 0x38,
        0x00, 0x40, 0x40, 0x78, 0x44, 0x44, 0x44, 0x00, 0x00, 0x10, 0x00, 0x30,
        0x10, 0x10, 0x38, 0x00, 0x00, 0x04, 0x00, 0x04, 0x04, 0x04, 0x24, 0x18,
        0x00, 0x20, 0x28, 0x30, 0x30, 0x28, 0x24, 0x00, 0x00, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x0c, 0x00, 0x00, 0x00, 0x68, 0x54, 0x54, 0x54, 0x54, 0x00,
        0x00, 0x00, 0x78, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00, 0x00, 0x38, 0x44,
        0x44, 0x44, 0x38, 0x00, 0x00, 0x00, 0x78, 0x44, 0x44, 0x78, 0x40, 0x40,
        0x00, 0x00, 0x3c, 0x44, 0x44, 0x3c, 0x04, 0x06, 0x00, 0x00, 0x1c, 0x20,
        0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x38, 0x40, 0x38, 0x04, 0x78, 0x00,
        0x00, 0x10, 0x38, 0x10, 0x10, 0x10, 0x0c, 0x00, 0x00, 0x00, 0x44, 0x44,
        0x44, 0x44, 0x38, 0x00, 0x00, 0x00, 0x44, 0x44, 0x28, 0x28, 0x10, 0x00,
        0x00, 0x00, 0x44, 0x54, 0x54, 0x54, 0x28, 0x00, 0x00, 0x00, 0x44, 0x28,
        0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x3c, 0x04, 0x38,
        0x00, 0x00, 0x7c, 0x08, 0x10, 0x20, 0x7c, 0x00, 0x00, 0x0e, 0x08, 0x30,
        0x08, 0x08, 0x0e, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00,
        0x00, 0x70, 0x10, 0x0c, 0x10, 0x10, 0x70, 0x00, 0x00, 0x14, 0x28, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x99, 0xa1, 0xa1, 0x99, 0x42, 0x3c
};
static unsigned int S_test_font_len = 1024;


static FrameBufferStatus frameBufferTestUpdate(FrameBufferBase *base)
{
    FrameBufferTest *frame_buffer = (FrameBufferTest *)base;
    FrameBufferStatus status;
    int pixel_row, pixel_col;

    for (pixel_row = 0; pixel_row < frame_buffer->base.height; pixel_row++)
    {
        for (pixel_col = 0; pixel_col < frame_buffer->base.width; pixel_col++)
        {
            int screen_row = pixel_row / 8;
            int screen_col = pixel_col / 8;

            uint8_t screen_char = frame_buffer->screen_ram[(screen_row * 32) + screen_col];

            int screen_row_bit = pixel_row % 8;
            int screen_col_bit = pixel_col % 8;


            uint8_t chr_bitmap_row = 0;

            if ((screen_char >= 32) && (screen_char <= 128))
            {
                screen_char -= 32;

                chr_bitmap_row = S_test_font[(screen_char * 8) + screen_row_bit];
            }

            if (chr_bitmap_row & (1 << screen_col_bit))
                frame_buffer->buffer[(pixel_row * frame_buffer->base.width) + pixel_col] = 0xff;
            else
                frame_buffer->buffer[(pixel_row * frame_buffer->base.width) + pixel_col] = 0x00;

        }

    }

    status = frameBufferBaseUpdate(base);

    return status;
}


FrameBufferStatus frameBufferTestInit(FrameBufferTest *frame_buffer, SDL_Renderer *renderer)
{
    FrameBufferStatus status = frameBufferBaseInit(&frame_buffer->base, renderer, frame_buffer->buffer,
            FRAME_BUFFER_TEST_WIDTH,
            FRAME_BUFFER_TEST_HEIGHT,
            SDL_PIXELFORMAT_RGB332);

    /* override default methods */
    frame_buffer->base.methods.update = frameBufferTestUpdate;

    //memset(frame_buffer->screen_ram, 0x40, FRAME_BUFFER_TEST_RAM_SCREEN_SIZE);
    memcpy(frame_buffer->screen_ram, S_test_data, FRAME_BUFFER_TEST_RAM_SCREEN_SIZE);

    return status;
}
