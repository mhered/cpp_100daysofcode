#ifndef PARSEBODY_H
#define PARSEBODY_H

#pragma once

#include <iostream>
#include <string>

#include <algorithm>

// Function to remove leading and trailing white spaces from a string
std::string trimString(const std::string& input) {
    // Find the first non-space character from the beginning
    size_t startPos = input.find_first_not_of(" \t\n\r");

    // If the string is all spaces, return an empty string
    if (startPos == std::string::npos) {
        return "";
    }

    // Find the first non-space character from the end
    size_t endPos = input.find_last_not_of(" \t\n\r");

    // Extract the substring between startPos and endPos
    return input.substr(startPos, endPos - startPos + 1);
}


std::string extractLink(const std::string &input)
{
    size_t linkPos = input.find("#link:");
    if (linkPos != std::string::npos)
    {
        size_t titlePos = input.find("#title:");
        size_t commentPos = input.find("#comment:");

        size_t endPos = std::min(titlePos>linkPos?titlePos:std::string::npos,
                        commentPos>linkPos?commentPos:std::string::npos);

        size_t startPos = linkPos + 6; // Length of "#link:"
        if (endPos == std::string::npos)
        {
            return trimString(input.substr(startPos));
        }
        else
        {
            return trimString(input.substr(startPos, endPos - startPos));
        }
    }

    return ""; // Return an empty string if the link field is not found
}

std::string extractTitle(const std::string &input)
{
    size_t titlePos = input.find("#title:");
    if (titlePos != std::string::npos)
    {
        size_t linkPos = input.find("#link:");
        size_t commentPos = input.find("#comment:");

        size_t endPos = std::min(linkPos>titlePos?linkPos:std::string::npos,
                        commentPos>titlePos?commentPos:std::string::npos);

        size_t startPos = titlePos + 7; // Length of "#title:"
        if (endPos == std::string::npos)
        {
            return trimString(input.substr(startPos));
        }
        else
        {
            return trimString(input.substr(startPos, endPos - startPos));
        }
    }

    return ""; // Return an empty string if the title field is not found
}

std::string extractComment(const std::string &input)
{
    size_t commentPos = input.find("#comment:");
    if (commentPos != std::string::npos)
    {
        size_t linkPos = input.find("#link:");
        size_t titlePos = input.find("#title:");

        size_t endPos = std::min(linkPos>commentPos?linkPos:std::string::npos,
                        titlePos>commentPos?titlePos:std::string::npos);

        size_t startPos = commentPos + 9; // Length of "#comment:"
        if (endPos == std::string::npos)
        {
            return trimString(input.substr(startPos));
        }
        else
        {
            return trimString(input.substr(startPos, endPos - startPos));
        }
    }

    return ""; // Return an empty string if the comment field is not found
}

/*
int main()
{
    std::string input;

    input = "#link: https://www.youtube.com/watch?v=2eWuYf-aZE4\n"
            "#title: The conspiracy to make AI seem harder than it is\n"
            "#comment: A talk from Spotify on AI and LLMs";

    std::cout << "1 Link: " << extractLink(input) << "\n";
    std::cout << "1 Title: " << extractTitle(input) << "\n";
    std::cout << "1 Comment: " << extractComment(input) << "\n";

    input = "#title: The conspiracy to make AI seem harder than it is\n"
            "#link: https://www.youtube.com/watch?v=2eWuYf-aZE4\n"
            "#comment: A talk from Spotify on AI and LLMs";

    std::cout << "2 Link: " << extractLink(input) << "\n";
    std::cout << "2 Title: " << extractTitle(input) << "\n";
    std::cout << "2 Comment: " << extractComment(input) << "\n";

    input = "#title: The conspiracy to make AI seem harder than it is"
            "#link: https://www.youtube.com/watch?v=2eWuYf-aZE4"
            "#comment: A talk from Spotify on AI and LLMs";

    std::cout << "3 Link: " << extractLink(input) << "\n";
    std::cout << "3 Title: " << extractTitle(input) << "\n";
    std::cout << "3 Comment: " << extractComment(input) << "\n";

    input = "#title: The conspiracy to make AI seem harder than it is\n"
            "#comment: A talk from Spotify on AI and LLMs";

    std::cout << "4 Link: " << extractLink(input) << "\n";
    std::cout << "4 Title: " << extractTitle(input) << "\n";
    std::cout << "4 Comment: " << extractComment(input) << "\n";

    input = "The conspiracy to make AI seem harder than it is"
            "https://www.youtube.com/watch?v=2eWuYf-aZE4"
            "A talk from Spotify on AI and LLMs";

    std::cout << "5 Link: " << extractLink(input) << "\n";
    std::cout << "5 Title: " << extractTitle(input) << "\n";
    std::cout << "5 Comment: " << extractComment(input) << "\n";


    return 0;
}
*/

#endif