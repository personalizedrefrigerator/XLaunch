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

#include "PixelWindow.h"
#include "MainRenderer.h"
#include "WordCompleter.h"

#include <iostream>
#include <chrono>
#include <memory>
#include "Matrix.h"
#include <stdlib.h>

static void print_help();

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        print_help();

        return 1;
    }

    PixelWindow::WindowOptions windowOpts {};
    PixelWindow mainWindow { };

    windowOpts.width = 500;
    windowOpts.height = 80;

    windowOpts.minWidth = windowOpts.width;
    windowOpts.minHeight = windowOpts.height;
    windowOpts.maxWidth = windowOpts.width;
    windowOpts.maxHeight = windowOpts.height;

    mainWindow.create(windowOpts);

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

static void print_help()
{
    std::cerr << " XLaunch: Lets a user enter text." << std::endl <<
        "  Takes no arguments. Tab-completion suggestions should be provided via stdin" <<
        std::endl << std::endl <<
        "License Summary:" << std::endl << std::endl <<
        " This program is free software: you can redistribute it and/or modify" << std::endl <<
        " it under the terms of the GNU General Public License as published by" << std::endl <<
        " the Free Software Foundation, either version 3 of the License, or" << std::endl <<
        " (at your option) any later version." << std::endl <<
        " " << std::endl << std::endl <<
        " This program is distributed in the hope that it will be useful, " << std::endl <<
        " but WITHOUT ANY WARRANTY; without even the implied warranty of " << std::endl <<
        " MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the " << std::endl <<
        " GNU General Public License for more details." << std::endl <<
        " " << std::endl << std::endl <<
        " You should have received a copy of the GNU General Public License " << std::endl <<
        " along with this program.  If not, see <https://www.gnu.org/licenses/>.";
    std::cerr << std::endl;
}

