//
// Created by justin on 24/01/2022.
//

#ifndef FRAMEBUFFERTEST_H
#define FRAMEBUFFERTEST_H

#include "FrameBuffer.h"

#define FRAME_BUFFER_TEST_WIDTH  256
#define FRAME_BUFFER_TEST_HEIGHT  192

#define FRAME_BUFFER_TEST_RAM_SCREEN_SIZE  (32 * 24)


class FrameBufferTest : public FrameBuffer
{
public:
    FrameBufferTest(SDL_Renderer *renderer);
    virtual ~FrameBufferTest();
    FrameBufferStatus update() override;

private:
    uint8_t m_pixel_buffer[FRAME_BUFFER_TEST_WIDTH * FRAME_BUFFER_TEST_HEIGHT];

    uint8_t m_screen_ram[FRAME_BUFFER_TEST_RAM_SCREEN_SIZE];
};


#endif //FRAMEBUFFERTEST_H
