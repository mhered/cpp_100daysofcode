#ifndef UTILS_H
#define UTILS_H

#pragma once

#include <iostream>
#include <fstream>
#include <algorithm> //all_of

#include <cstring> // strcmp
#include <sstream> //stringstream

#include <cctype>
#include <locale>

std::string LINE_COMMENT = "//";
std::string START_BLOCK_COMMENT = "/*";
std::string END_BLOCK_COMMENT = "*/";

const std::string RED("\033[0;31m");
const std::string GREEN("\033[0;32m");
const std::string BLUE("\033[0;34m");
const std::string YELLOW("\033[0;33m");
const std::string CYAN("\033[0;36m");
const std::string MAGENTA("\033[0;35m");
const std::string RESET("\033[0m");

// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
};

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
};

// trim from both ends (in place)
static inline void trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
};

// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
};

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
};

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
    trim(s);
    return s;
};

bool endswith(std::string s, std::string suffix)
{
    return s.find(suffix, s.length() - suffix.length()) != std::string::npos;
};

bool startswith(std::string s, std::string prefix)
{
    return (s.rfind(prefix, 0) == 0);
};

bool is_blank_line(std::string str)
{
    return std::all_of(str.begin(), str.end(), isspace);
};

bool starts_with_line_comment(std::string str)
{
    ltrim(str);
    return startswith(str, LINE_COMMENT);
};

bool block_comment_starts(std::string str)
{
    ltrim(str);
    return startswith(str, START_BLOCK_COMMENT);
};

bool block_comment_ends(std::string str)
{
    rtrim(str);
    return endswith(str, END_BLOCK_COMMENT);
};

#endif