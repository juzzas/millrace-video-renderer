//
// Created by justins on 14/09/2021.
//

#ifndef FRAMEBUFFER_TEST_H
#define FRAMEBUFFER_TEST_H

#include "frame_buffer_base.h"

#define FRAME_BUFFER_TEST_WIDTH  256
#define FRAME_BUFFER_TEST_HEIGHT  192

#define FRAME_BUFFER_TEST_RAM_SCREEN_SIZE  (32 * 24)

typedef struct FrameBufferTest
{
    FrameBufferBase base;
    uint8_t pixel_buffer[FRAME_BUFFER_TEST_WIDTH * FRAME_BUFFER_TEST_HEIGHT];

    uint8_t screen_ram[FRAME_BUFFER_TEST_RAM_SCREEN_SIZE];
} FrameBufferTest;


/**
 * Create a Frame Buffer for FrameBuffer test screen layout
 *
 * @return FRAMEBUFFER_OK if successful, else failure
 */
FrameBufferStatus frameBufferTestInit(FrameBufferTest *frame_buffer, SDL_Renderer *renderer);


#endif //FRAMEBUFFER_TEST_H
