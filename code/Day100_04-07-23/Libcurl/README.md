#link: https://www.youtube.com/watch?v=g83kYIQNRwU

# Libcurl
Let's learn about [libcurl](https://curl.se/libcurl/), the C API for the `curl` command, following along the getting started video in the link by Daniel Stenberg himself (founder and maintainer of the library).

## Installing and compiling
Install with:

```bash
$ sudo apt update && sudo apt upgrade.
$ sudo apt install curl
$ curl --version
$ sudo find / -name libcurl*
```


May need to update `"includePath": [` in `c_cpp_properties.json` so vscode can find the library in the path `/usr/lib/x86_64-linux-gnu/libcurl.a`

Link to it updating `"args": [` with `"-lcurl",` in `tasks.json`

(In my system curl was already installed and available)

Only one include needed:
`#include <curl/curl.h>`

See documentation in https://curl.se and https://everything.curl.dev/

Several families of APIs:
`curl_easy_*` -> for synchronous transfers
`curl_multi_*` -> one or more transfers concurrently. More complex.
`curl_share_*` -> share data between multiple transfers
`curl_url_*` -> parser functions

Principles:
- we work on transfers: upload/download data for/from an URL
- The default transfer is the simplest one
curl is protocol agnostic
- you set a handle then change behaviour setting options

`CURL * handle` is a handle to a single transfer
handle reuse is encouraged
options are sticky
options copy data (with one exception)
only mandatory option is `CURLOPT_URL`

Easy interface:
synchronous. May take a loong time. If you dont want to wait you need to use threads. You can set wait limits.

```c++
// Create a handle
CURL *easy = curl_easy_init();
// Set options:
CURLcode rc = curl_easy_setopt(easy, CURLOPT_URL, "https://curl.se");

// perform the transfer. Returns ok or >100 error msgs
CURLcode result = curl_easy_perform(easy);

// Kill handle
curl_easy_cleanup(easy);
```

Some options(>300!):
- CURLOPT_URL url
- CURLOPT_VERBOSE
- CURLOPT_BUFFERSIZE larger for faster transfers, but uses more memory
- CURLOPT_ERRORBUFFER better error messages
- CURLOPT_WRITEFUNCTION callback instead of stdout
- CURLOPT_READFUNCTION callback how to read data to upload
- CURLOPT_TIMEOUT_MS, CURLOPT_CONNECTTIMEOUT_MS to limit timeouts

3 ways to provide data for sending:
- CURLOPT_READFUNCTION callback how to read data to upload
- CURLOPT_POSTFIELDS to post a string
- CURLOPT_MIMEPOST multipart structured data


`curl_easy_info()` to get info after transfer:
- CURLINFO_EFFECTIVE_URL if redirected
- CURLINFO_EFFECTIVE_RESPONSE_CODE 200 if OK, 301 if redirect
- CURLINFO_TOTAL_TIME_T 
- CURLINFO_SPEED_DOWNLOAD_T
- CURLINFO_CONTENT_TYPE
- etc.

# Basic example
[main.cpp](./main.cpp) implements a basic download and a basic upload.

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
- [x] web_scraping: curl
- [ ] OpenCV
