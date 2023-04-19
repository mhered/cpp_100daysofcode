#include <iostream>
#include <string>

#include "Lexicon.h"

int main()
{
    Lexicon lex("wordlist.10000.txt");

    std::vector<std::string> words = {
        "yesterday",
        "Zimbabwe",
        "wrestling",
        "vulnerability",
    };
    for (auto word : words)
        lex.contains(word);

    std::vector<std::string> not_words = {
        "abcd",
        "wierd",
        "beleive",
        "entrepenur",
        "priviledge",
    };
    for (auto not_word : not_words)
        lex.contains(not_word);

    return 0;
}