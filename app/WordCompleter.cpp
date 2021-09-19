#include "WordCompleter.h"

#include <vector>
#include <string>

class WordCompleter::Impl
{
public:
    Impl(std::function<std::string()> source);
    std::string complete(int idx, const std::string& key);

private:
    /// Populates words_ from source_.
    void loadWords();

private:
    // TODO: Replace with a more efficient implementation.
    std::unique_ptr<std::vector<std::string>> words_ { nullptr };

    std::function<std::string()> source_;
};


WordCompleter::WordCompleter(std::function<std::string()> source)
    : pImpl { std::make_unique<Impl>(source) }
{ }

WordCompleter::~WordCompleter() { }

std::string WordCompleter::complete(int idx, const std::string& key)
{
    return pImpl->complete(idx, key);
}

WordCompleter::Impl::Impl(std::function<std::string()> source)
    : source_ { source }
{ }

std::string WordCompleter::Impl::complete(int idx, const std::string& key)
{
    loadWords();

    int match = 0;
    for (std::string& word : *words_)
    {
        if (word.rfind(key, 0) == 0)
        {
            if (match >= idx)
            {
                return word;
            }

            match++;
        }
    }

    return key;
}

void WordCompleter::Impl::loadWords()
{
    if (!words_)
    {
        std::unique_ptr<std::vector<std::string>> words
        {
            std::make_unique<std::vector<std::string>>()
        };

        words_.swap(words);

        std::string word;
        while (!(word = source_()).empty())
        {
            words_->push_back(word);
        }
    }
}

