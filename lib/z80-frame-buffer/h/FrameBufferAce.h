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

#ifndef FRAMEBUFFERACE_H
#define FRAMEBUFFERACE_H

#include "FrameBufferZ80.h"

#define FRAME_BUFFER_ACE_WIDTH  256
#define FRAME_BUFFER_ACE_HEIGHT  192

#define FRAME_BUFFER_ACE_RAM_SCREEN_SIZE  (32 * 24)
#define FRAME_BUFFER_ACE_RAM_CHARACTER_SIZE  (8 * 128)


class FrameBufferAce : public FrameBufferZ80
{
public:
    FrameBufferAce(SDL_Renderer *renderer);
    virtual ~FrameBufferAce();
    FrameBufferStatus update() override;

private:
    uint8_t pixel_buffer[FRAME_BUFFER_ACE_WIDTH * FRAME_BUFFER_ACE_HEIGHT];

    uint8_t screen_ram[FRAME_BUFFER_ACE_RAM_SCREEN_SIZE];
    uint8_t character_ram[FRAME_BUFFER_ACE_RAM_CHARACTER_SIZE];
};


#endif //FRAMEBUFFERACE_H
