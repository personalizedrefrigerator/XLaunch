#pragma once

#include "PixelSetter.h"
#include "X11PixelSetter.h"
#include "BaseRenderer.h"
#include "EmptyRenderer.h"

#include <memory>
#include <X11/Xlib.h>

// TODO: Not yet thread safe! Call everything on the UI thread!

class PixelWindow
{
public:
    PixelWindow();
    ~PixelWindow();
    
    void create(int width, int height);
    void render();
    void close();

    void setRenderer(std::shared_ptr<BaseRenderer> newRenderer);
    void startEventListeningLoop();
    void startRenderingLoop(int minimumMillisecondsBetweenCallsToRender);

private:
    void resetBitmapBitsAndGetNewScreenImageIfNeeded(int currentWidth, int currentHeight);
    void cleanupPointers();
    KeyInfo keyInformation;

    bool halt = false;
    Display* display;

    bool resizing = false;
    int windowWidth;
    int windowHeight;
    X11PixelSetter* pixelSetter = nullptr;
    std::shared_ptr<BaseRenderer> renderer;

    // X11 variables.
    Window window;
    int screen;
    XImage* screenImage = nullptr;

    char* bitmapBits = nullptr;
    bool bitmapBitsDefined = false;
    int lastWindowWidth;
    int lastWindowHeight;
};

