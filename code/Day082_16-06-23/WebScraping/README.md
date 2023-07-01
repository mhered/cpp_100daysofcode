#link: https://www.scrapingbee.com/blog/web-scraping-c++/

# Web Scraping

Web scraping is a common technique for harvesting data online, in which an HTTP client, processing a user request for data, uses an HTML parser to comb through that data. 

The tutorial in the link implements a simple scraper in C++ using the `libcurl` and `gumbo` libraries, to obtain from Merriam-Webster's Dictionary the definitions of an English word provided as argument.
Usage:

```bash
$ ./scraper esoteric
"esoteric":
> designed for or understood by the specially initiated alone
> requiring or exhibiting knowledge that is restricted to a small group
> difficult to understand 
> limited to a small circle
> private, confidential
> of special, rare, or unusual interest
> taught to or understood by members of a special group
> hard to understand
> of special or unusual interest

$

```

Github gist: https://gist.github.com/ace411/f7927e2fa9136aa21dc628a1e854dc74


## Installation

Install dependencies `libcurl` and `gumbo`:

```bash
$ sudo apt install libcurl4-openssl-dev libgumbo-dev
```

Include headers:
```c++
#include <gumbo.h>
#include <curl/curl.h>
```

Link to the libraries in `tasks.json`:
```
"args": [
                "-std=c++17",
                "-fdiagnostics-color=always",
                "-I${fileDirname}",
                "-g",
                "${fileDirname}/*.cpp",
                "-o",
                "${fileDirname}/bin/${fileBasenameNoExtension}",
                "-lcurl", 
                "-lgumbo", 
                ...
```



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
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [x] web_scraping
- [ ] OpenCV