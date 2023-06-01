#ifndef FILE_H
#define FILE_H

#pragma once

struct File
{
public:
    File() : filename(""),
             count_total_lines(0),
             count_code_lines(0),
             count_blank_lines(0),
             count_comment_lines(0){};

    File(std::string filename) : filename(filename),
                                 count_total_lines(0),
                                 count_code_lines(0),
                                 count_blank_lines(0),
                                 count_comment_lines(0)
    {
        if (!analyze_file())
        {
            std::cerr << "Could not read file \"" << filename << "\"" << std::endl;
        }
    };

    ~File();

public:
    std::string filename;
    uint count_total_lines;
    uint count_code_lines;
    uint count_blank_lines;
    uint count_comment_lines;

    bool analyze_file();

private:
};

#endif