//
// Created by justin on 24/01/2022.
//

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
