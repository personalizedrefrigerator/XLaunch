/**
 *  XLaunch - Dialog for choosing items from a menu.
 *   Copyright (C) 2021  Henry Heino
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "MainRenderer.h"

#include "TextDrawer.h"
#include "PixelSetter.h"
#include "TransformedPixelSetter.h"
#include "TextEditor.h"
#include "Grapher.h"
#include "KeyCodes.h"

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <cmath>
#include <cstring>
#include <cstdlib>

#define TEXT_DEFAULT_R 200
#define TEXT_DEFAULT_G 100
#define TEXT_DEFAULT_B 220

#define TEXT_HI_R 250
#define TEXT_HI_G 200
#define TEXT_HI_B 100

const int CHAR_W = 3;
const int CHAR_H = 4;

class MainRenderer::Impl
{
public:
    Impl(tabCompletionFn_t completer, onSubmitFn_t onSubmit);
    void render(PixelSetter* pixelSetter, int w, int h);
    void handleKeyInput(KeyInfo& keyData);

private:
    TextDrawer textRenderer_;
    TextEditor editor_;

    std::string preCompletionCmd_;
    tabCompletionFn_t completer_;
    int completionIdx = -1;

    std::unique_ptr<TransformedPixelSetter> viewTransformer_ { nullptr };
};

MainRenderer::MainRenderer(MainRenderer::tabCompletionFn_t completer, MainRenderer::onSubmitFn_t onSubmit)
    : pImpl { std::make_unique<Impl>(completer, onSubmit) }
{ }

MainRenderer::~MainRenderer()
{ }

void MainRenderer::render(PixelSetter* out, int w, int h)
{
    pImpl->handleKeyInput(keyData);
    pImpl->render(out, w, h);
}

MainRenderer::Impl::Impl(MainRenderer::tabCompletionFn_t completer, MainRenderer::onSubmitFn_t onSubmit)
    : completer_ { completer }
{
    editor_.setTextSize(CHAR_W, CHAR_H);
    editor_.getContent() = "";

    editor_.setNewLineCallback([=](std::string& text)
    {
        onSubmit(text);
        text = "";
    });
}

void MainRenderer::Impl::render(PixelSetter* pixelSetter, int width, int height)
{
    pixelSetter->setColor(200, 100, 255);

    if(!viewTransformer_)
    {
        viewTransformer_ = std::make_unique<TransformedPixelSetter>(pixelSetter);
    }
    viewTransformer_->setPixelSetter(pixelSetter);

    double theta = 0.0;

    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    unsigned long currentTime = (std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())).count();

    theta = std::sin(currentTime/1000.0) * 3.14159 / 20;

    viewTransformer_->transformMatrix.toIdentity();

    Matrix<double, 2, 2> scaleMatrix;
    scaleMatrix.toIdentity();
    scaleMatrix.setAt(1, 0, (sin(currentTime / 400.0) + 1) / 10);
    scaleMatrix.setAt(0, 1, 0.01);

    viewTransformer_->transformMatrix *= scaleMatrix;

    viewTransformer_->clear(0);
    viewTransformer_->setColor(TEXT_DEFAULT_R, TEXT_DEFAULT_G, TEXT_DEFAULT_B);

    int textX = 22;
    int textY = 3;
    textRenderer_.drawWrapped("> ", 3, textY, *viewTransformer_, CHAR_W, CHAR_H, width);
    
    if (completionIdx >= 0)
    {
        // If we're showing completions, highlight the entry
        viewTransformer_->setColor(TEXT_HI_R, TEXT_HI_G, TEXT_HI_B);
    }

    editor_.render(*viewTransformer_, textX, textY, width);// / 2);

    // If we're showing completions, cover up the part of the entry we're not completing
    if (completionIdx >= 0)
    {
        viewTransformer_->setColor(TEXT_DEFAULT_R, TEXT_DEFAULT_G, TEXT_DEFAULT_B);
        textRenderer_.drawWrapped(preCompletionCmd_, textX, textY, *viewTransformer_, CHAR_W, CHAR_H, width);
    }
}

void MainRenderer::Impl::handleKeyInput(KeyInfo& keyData)
{
    if (!keyData.handledKey)
    {
        keyData.handledKey = true;


        // Tab key
        if (keyData.lastKey == TAB_KEY)
        {
            // Start completions.
            if (completionIdx < 0)
            {
                preCompletionCmd_ = editor_.getContent();
                completionIdx = 0;
                editor_.getContent() = completer_(completionIdx, preCompletionCmd_);
            }
            else
            {
                // Otherwise, we were already completing. Accept the completion.
                completionIdx = -1;
            }
        } // Next completion
        else if (completionIdx >= 0 && keyData.lastKey == DOWN_KEY)
        {
            completionIdx++;
            editor_.getContent() = completer_(completionIdx, preCompletionCmd_);

            if (editor_.getContent() == preCompletionCmd_)
            {
                completionIdx--;
            }
        }
        else if (completionIdx >= 0 && keyData.lastKey == UP_KEY)
        {
            completionIdx--;

            if (completionIdx < 0)
            {
                completionIdx = 0;
            }

            editor_.getContent() = completer_(completionIdx, preCompletionCmd_);
        } // Escape
        else if (completionIdx >= 0 && keyData.lastKey != ENTER_KEY)
        {
            // Cancel completion.

            editor_.getContent() = preCompletionCmd_;
            completionIdx = -1;
        } // Don't handle the escape key. Pass it to the root window.
        else if (keyData.lastKey != ESC_KEY)
        {
            editor_.handleKeyChange(keyData.lastKey);
        }
        else
        {
            keyData.handledKey = false;
        }
    }
}

