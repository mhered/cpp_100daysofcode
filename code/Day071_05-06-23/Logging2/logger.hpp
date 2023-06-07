#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

// based on: https://stackoverflow.com/a/6168353/15472802

/* consider adding boost thread id since we'll want to know whose writting and
 * won't want to repeat it for every single call */

/* consider adding policy class to allow users to redirect logging to specific
 * files via the command line
 */

enum logLevel
{
    logNONE,
    logERROR,
    logWARNING,
    logINFO,
    logDEBUG,
    logDEBUG1,
    logDEBUG2
};

std::vector<std::string> DEBUG_LEVEL = {"[NONE]",
                                        "[ERROR]",
                                        "[WARNING]",
                                        "[INFO]",
                                        "[DEBUG]",
                                        "[DEBUG1]",
                                        "[DEBUG2]"};

static std::time_t time_now = std::time(nullptr);

class logIt
{
public:
    logIt(logLevel _loglevel = logERROR)
    {
        _buffer << std::put_time(std::localtime(&time_now), "%y-%m-%d %OH:%OM:%OS") << " ";
        _buffer << std::setw(10) << std::left << DEBUG_LEVEL[_loglevel] << " >>";
        _buffer << std::string(
            _loglevel > logDEBUG
                ? (_loglevel - logDEBUG) * 4
                : 1,
            ' ');
    }

    template <typename T>
    logIt &operator<<(T const &value)
    {
        _buffer << value;
        return *this;
    }

    ~logIt()
    {
        _buffer << std::endl;
        // This is atomic according to the POSIX standard
        // http://www.gnu.org/s/libc/manual/html_node/Streams-and-Threads.html
        std::cerr << _buffer.str();
    }

private:
    std::ostringstream _buffer;
};

extern logLevel loglevel;

#define log(level)        \
    if (level > loglevel) \
        ;                 \
    else                  \
        logIt(level)

#endif
