//
// Created by justins on 14/09/2021.
//

#ifndef FRAMEBUFFER_ACE_H
#define FRAMEBUFFER_ACE_H

#include "frame_buffer_base.h"

#define FRAME_BUFFER_ACE_WIDTH  256
#define FRAME_BUFFER_ACE_HEIGHT  192

#define FRAME_BUFFER_ACE_RAM_SCREEN_SIZE  (32 * 24)
#define FRAME_BUFFER_ACE_RAM_CHARACTER_SIZE  (8 * 128)

typedef struct FrameBufferAce
{
    FrameBufferBase base;
    uint8_t buffer[FRAME_BUFFER_ACE_WIDTH * FRAME_BUFFER_ACE_HEIGHT];

    uint8_t screen_ram[FRAME_BUFFER_ACE_RAM_SCREEN_SIZE];
    uint8_t character_ram[FRAME_BUFFER_ACE_RAM_CHARACTER_SIZE];
} FrameBufferAce;


/**
 * Create a Frame Buffer for Jupiter ACE screen layout
 *
 * @return pointer to FrameBufferBase if successful, else NULL
 */
FrameBufferStatus frameBufferAceInit(FrameBufferAce* frame_buffer, SDL_Renderer* renderer);


#endif //FRAMEBUFFER_ACE_H
