//
// Created by justin on 25/01/2022.
//

#ifndef FRAMEBUFFERZ80_H
#define FRAMEBUFFERZ80_H

#include "FrameBuffer.h"
#include "Z80BusExpander.h"

class FrameBufferZ80 : public FrameBuffer
{
public:
    FrameBufferZ80();
    virtual ~FrameBufferZ80();

private:
    Z80BusExpander m_z80;
};


#endif //FRAMEBUFFERZ80_H
