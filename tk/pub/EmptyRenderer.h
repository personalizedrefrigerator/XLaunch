#pragma once
#include "BaseRenderer.h"

class EmptyRenderer : public BaseRenderer
{
public:
    void render(PixelSetter* pixelSetter, int screenWidth, int screenHeight) {};
    virtual ~EmptyRenderer();
};
