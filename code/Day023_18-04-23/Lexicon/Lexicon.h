#ifndef LEXICON_H
#define LEXICON_H

#pragma once
#include <vector>
#include <string>

class Lexicon
{
public:
    Lexicon();
    Lexicon(std::string filename);
    ~Lexicon();
    bool contains(std::string word);

private:
    std::vector<std::string> corpus;
};

#endif