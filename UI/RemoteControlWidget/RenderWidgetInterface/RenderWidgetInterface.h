#ifndef _RENDERWIDGETINTERFACE_H
#define _RENDERWIDGETINTERFACE_H

#include "Render.h"

class RenderWidgetInterface
{
public:
    virtual void setCurrent(RenderInterface::VideoFrame frame) = 0;
};


#endif //_RENDERWIDGETINTERFACE_H