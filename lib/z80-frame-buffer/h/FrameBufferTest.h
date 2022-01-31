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
