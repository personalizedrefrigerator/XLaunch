#pragma once

/**
 * Main application renderer and event handler.
 *
 * Licensed under v3.0 of the GPL.
 */

#include <memory>
#include <string>
#include <functional>

#include "BaseRenderer.h"

class PixelSetter;

class MainRenderer : public BaseRenderer
{
public:
    using tabCompletionFn_t = std::function<std::string(int, std::string&)>;
    using onSubmitFn_t = std::function<void(std::string)>;

    MainRenderer(tabCompletionFn_t, onSubmitFn_t);
    void render(PixelSetter* pixelSetter, int w, int h) override;
    ~MainRenderer();

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

