#link: https://stackoverflow.com/a/38004816/15472802

# Logging 1

This is a first attempt at writing a super simple logging facility in C++.
Based on the Stack Overflow reply in the link above, it utilizes `#define` compiler statements to define macros for simplicity of use, and also to report the file and line where the log message was launched via the `__FILE__` and `__LINE__` macros.

Usage:

```
#include "minilogger.hpp";

int main()
{
    INFO << "This is an INFO message" << std::endl;
    ERROR << "This is an ERROR message" << std::endl;
    DEBUG << "This is a DEBUG message" << std::endl;
}
```

Sample output:

```
2023-06-07 10:21:50 [INFO] main.cpp(main:6) >> This is an INFO message
2023-06-07 10:21:50 [ERROR] main.cpp(main:7) >> This is an ERROR message
2023-06-07 10:21:50 [DEBUG] main.cpp(main:8) >> This is a DEBUG message
```

Advantages: 
- standalone header file 
- very easy to use
- quickly provides log level, timestamp, file and line

Disadvantage:
- management of log levels to enable/disable verbose logging ... not easy

# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [x] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV