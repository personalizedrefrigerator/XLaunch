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

#pragma once

#include <functional>
#include <memory>
#include <string>

class WordCompleter
{
public:
    WordCompleter(std::function<std::string()> source);
    ~WordCompleter();

    /// Get the [idx]th word from the completions list
    /// that starts with [key].
    std::string complete(int idx, const std::string& key);
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

