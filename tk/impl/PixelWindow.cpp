/*
 * PixelWindow.cpp
 *
 *  Created on: Jun 29, 2018
 */

#include <PixelWindow.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <thread>
#include <functional>

PixelWindow::PixelWindow()
    : pixelSetter { new X11PixelSetter() }
    , renderer { std::make_shared<EmptyRenderer>() }
{ }

// Create the window, windowWidth, windowHeight.
void PixelWindow::create(int windowWidth, int windowHeight)
{
    // Open the current/default display.
    display = XOpenDisplay(NULL);

    // Get the screen.
    screen = DefaultScreen(display);

    // Create the window.
    window = XCreateSimpleWindow(display, RootWindow(display, screen),
        10, // X
        10, // Y
        windowWidth, windowHeight,
        5, // Border width.
        WhitePixel(display, screen), // Border
        BlackPixel(display, screen)); // Background

    // Be notified for window re-draws, key presses, and mouse button clicks.
    XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask | SubstructureNotifyMask);

    // Display the window.
    XMapWindow(display, window);

    // Configure protocols to be received.
    //Atom deleteWindowIntercept = XInternAtom(display, "WM_DELETE_WINDOW", false);
    //XSetWMProtocols(display, window, &deleteWindowIntercept, 1);

    Visual* defaultVisual = DefaultVisual(display, screen);
    Colormap mainColormap = DefaultColormap(display, DefaultScreen(display));

    XColor foreground;

    foreground.red = 30000;
    foreground.green = 2000;
    foreground.blue = 1000;

    Status colorStatus = XAllocColor(display, mainColormap, &foreground);
}

// Set the current renderer.
void PixelWindow::setRenderer(std::shared_ptr<BaseRenderer> newRenderer)
{
    renderer = newRenderer;
}

// Render the screen's contents.
void PixelWindow::render()
{
    if (halt)
    {
        return;
    }

    GC graphicsContext = DefaultGC(display, screen);

    XWindowAttributes windowProperties;
    XGetWindowAttributes(display, window, &windowProperties);

    int width, height;

    width = windowProperties.width - 10;
    height = windowProperties.height - 10;

    // If needed, reset the bitmap bits and get a new screen image.
    resetBitmapBitsAndGetNewScreenImageIfNeeded(width, height);

    if (!resizing)
    {
        pixelSetter->setData(bitmapBits, width*height*4, width, height);

        renderer->render(pixelSetter, width, height);

        // Draw the image, if the renderer didn't tell us to stop early.
        if (!halt)
        {
            XPutImage(display, window, graphicsContext, screenImage, 0, 0, 0, 0, width, height);
        }
    }
}

void PixelWindow::startRenderingLoop(int minimumMillisecondsBetweenRenders)
{
    if (halt) return;

    // Wait for the 1st event,
    XEvent event;
    XNextEvent(display, &event);

    // Calculate the minimum amount of time between calls to render.
    float deltaTimeBetweenRenderCalls = minimumMillisecondsBetweenRenders/1000.0f;

    // Continue until error. FIX THIS LATER.
    while (!halt)
    {
        // Wait 400 ms.
        sleep(deltaTimeBetweenRenderCalls);

        // Render.
        render();
    }
}

void PixelWindow::startEventListeningLoop()
{
    if (halt) return;

    XEvent event;
    XNextEvent(display, &event);
    bool success = false;
    while (!halt)
    {
        success = XCheckMaskEvent(display, ClientMessage, &event);

        if (success)
        {
            keyInformation.handledKey = false;
            keyInformation.lastKey = XLookupKeysym(&event.xkey, 0);
            renderer->setKeyInfo(keyInformation);
        }

        render();

        // Exit on ESC key
        if (success && keyInformation.lastKey == 65307 && !keyInformation.handledKey)
        {
            halt = true;
            break;
        }
    }

    // Stop.
    cleanupPointers();
}


void PixelWindow::close()
{
    if (!halt)
    {
        XDestroyWindow(display, window);
    }

    halt = true;
}


// Free memory.
void PixelWindow::cleanupPointers()
{
    halt = true;

    // Free the renderer, the bitmap data, and the pixel setter.
    delete[] bitmapBits;
    bitmapBits = nullptr;

    delete pixelSetter;
    pixelSetter = nullptr;

    delete screenImage;
    screenImage = nullptr;

    if (display)
    {
        XCloseDisplay(display);
        display = nullptr;
    }
}

// If needed, reset the bitmap bits.
void PixelWindow::resetBitmapBitsAndGetNewScreenImageIfNeeded(int width, int height)
{
    if (halt) return;

    bool needUpdate = false;
    if (width < lastWindowWidth || height < lastWindowHeight)
    {
        resizing = true;
        lastWindowWidth = width;
        lastWindowHeight = height;
    }
    else if (resizing)
    {
        resizing = false;
        needUpdate = true;
    }

    // If we havn't created a bitmap yet, or the current window size is different from the last,
    if (!bitmapBitsDefined || needUpdate || ((width != lastWindowWidth || height != lastWindowHeight) && !resizing && width > 0 && height > 0))
    {
        if (bitmapBits)
        {
            delete[] bitmapBits;
            bitmapBits = nullptr;
        }

        // We also need to re-create screenImage
        delete screenImage;
        screenImage = nullptr;

        // Create it.
        bitmapBits = new char[width * height * 4];//(char *)malloc(width * height * 4);

        // Generate a new screen image, to be used with the bitmap bits.
        screenImage = XGetImage(display, window, 0, 0, width, height, AllPlanes, ZPixmap);


        // Write the data to the screen.
        screenImage->data = bitmapBits;

        // Initialize the image.
        XInitImage(screenImage);

        // Note that it has been defined.
        bitmapBitsDefined = true;

        // Update the last window size.
        lastWindowWidth = width;
        lastWindowHeight = height;
    }
}

// On deconstruct,
PixelWindow::~PixelWindow()
{
    // Clean-up the pointers.
    cleanupPointers();
}
