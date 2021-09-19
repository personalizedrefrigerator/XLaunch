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

