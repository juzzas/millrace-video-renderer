//
// Created by justins on 15/09/2021.
//

#include "frame_buffer.h"
#include "frame_buffer_base.h"


void frameBufferDestroy(FrameBufferBase *base)
{
    if (base && base->methods.destroy)
        base->methods.destroy(base);
}


FrameBufferStatus frameBufferUpdate(FrameBufferBase* base)
{
    FrameBufferStatus status = FRAMEBUFFER_OK;

    if (!base)
        return FRAMEBUFFER_ERROR_INVALID_PARAMETER;

    if (base->methods.update)
        status = base->methods.update(base);

    return status;
}


FrameBufferStatus frameBufferRender(FrameBufferBase *base)
{
    FrameBufferStatus status = FRAMEBUFFER_OK;

    if (!base)
        return FRAMEBUFFER_ERROR_INVALID_PARAMETER;

    if (base->methods.render)
        status = base->methods.render(base);

    return status;
}


FrameBufferStatus frameBufferPresent(FrameBufferBase *base)
{
    FrameBufferStatus status = FRAMEBUFFER_OK;

    if (!base)
        return FRAMEBUFFER_ERROR_INVALID_PARAMETER;

    if (base->methods.present)
        status = base->methods.present(base);

    return status;
}
