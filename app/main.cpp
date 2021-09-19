#include "PixelWindow.h"
#include "MainRenderer.h"
#include "WordCompleter.h"

#include <iostream>
#include <chrono>
#include <memory>
#include "Matrix.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    PixelWindow mainWindow { };
    mainWindow.create(500, 80);

    WordCompleter completer
    {
        []()
        {
            std::string out;
            std::getline(std::cin, out);
            return out;
        }
    };
    testMatricies();

    // Display the dialog and get the result.
    std::shared_ptr<BaseRenderer> renderer = std::make_shared<MainRenderer>([&](int idx, const std::string& text)
    {
        return completer.complete(idx, text);
    }, [&](std::string result)
    {
        std::cout << result << std::endl;
        mainWindow.close();
    });

    mainWindow.setRenderer(renderer);
    mainWindow.startEventListeningLoop();

    return 0;
}

