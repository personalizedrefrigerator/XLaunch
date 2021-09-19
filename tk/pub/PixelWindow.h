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
    struct WindowOptions;

public:
    PixelWindow();
    ~PixelWindow();
    
    void create(WindowOptions opts);
    void render();
    void close();

    void setRenderer(std::shared_ptr<BaseRenderer> newRenderer);
    void startEventListeningLoop();
    void startRenderingLoop(int minimumMillisecondsBetweenCallsToRender);

public:
    struct WindowOptions
    {
        int x = 10;
        int y = 10;
        int width = 500;
        int height = 500;

        int minWidth = 0;
        int minHeight = 0;

        int maxWidth = -1;
        int maxHeight = -1;
    };

protected:
    void configureWindow(Display*, Window, const WindowOptions&) const;

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

