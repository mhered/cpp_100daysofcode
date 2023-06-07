#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

#define NONE(logger, message) logger.log(message, __FILE__, __LINE__, LogLevel::NONE)
#define ERROR(logger, message) logger.log(message, __FILE__, __LINE__, LogLevel::ERROR)
#define WARNING(logger, message) logger.log(message, __FILE__, __LINE__, LogLevel::WARNING)
#define INFO(logger, message) logger.log(message, __FILE__, __LINE__, LogLevel::INFO)
#define DEBUG(logger, message) logger.log(message, __FILE__, __LINE__, LogLevel::DEBUG)

const std::string RED("\033[0;31m");
const std::string GREEN("\033[0;32m");
const std::string YELLOW("\033[0;33m");
const std::string CYAN("\033[0;36m");
const std::string MAGENTA("\033[0;35m");
const std::string RESET("\033[0m");

enum class LogLevel
{
    NONE,
    ERROR,
    WARNING,
    INFO,
    DEBUG
};

class Logger
{
public:
    Logger(const std::string &filename = "") : logLevel(LogLevel::ERROR)
    {
        if (!filename.empty())
        {
            logFile.open(filename, std::ios::app);
            if (!logFile.is_open())
            {
                std::cerr << "Error opening log file: " << filename << std::endl;
            }
        }
    }

    ~Logger()
    {
        std::ostream &output = logFile.is_open() ? logFile : std::cout;
        output << ">>>>>> END OF RUN >>>>>" << std::endl;
        
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    template <typename T>
    void log(const T &message, const char *file, int line, LogLevel level)
    {
        if (level <= logLevel)
        {   // extract filename from full path in __FILE__
            std::string filename = fs::path(file).filename().string();
            
            std::ostream &output = logFile.is_open() ? logFile : std::cout;
            std::time_t currentTime = std::time(nullptr);
            output << "[" << std::put_time(std::localtime(&currentTime), "%F %T") << "] "
                   << "[" << filename << ":" << line << "] " << logLevelToString(level) << ": " << message << std::endl;
        }
    }

    void setLevel(LogLevel level) { logLevel = level; };

private:
    std::ofstream logFile;
    LogLevel logLevel;

    std::string logLevelToString(LogLevel level) const
    {
        std::string str_level, highlight;

        switch (level)
        {
        case LogLevel::ERROR:
            str_level = "ERROR";
            highlight = RED;
            break;
        case LogLevel::WARNING:
            str_level = "WARNING";
            highlight = YELLOW;
            break;
        case LogLevel::INFO:
            str_level = "INFO";
            highlight = CYAN;
            break;
        case LogLevel::DEBUG:
            str_level = "DEBUG";
            highlight = MAGENTA;
            break;
        default:
            str_level = "";
            highlight = "";
        }
        if (logFile.is_open())
            return str_level;
        else
            return highlight + str_level + RESET;
    }
};

#endif