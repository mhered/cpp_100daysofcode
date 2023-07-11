#link: https://www.youtube.com/watch?v=UVYPtnWRtNA

# REST API with C++ and Crow

The tutorial in the link describes how to write a simple REST API using [Crow](https://crowcpp.org/master/) - a C++ framework for creating HTTP or Websocket web services - and the [redis](https://github.com/cpp-redis/cpp_redis) database.

Github repo: https://github.com/prince776/yt-projects/tree/master/cppREST


## What is a REST API?

[API](https://en.wikipedia.org/wiki/Web_APIweb api icon
ç) stands for application programming interface: a set of rules that defines how applications and devices communicate with each other.  

REST stands for [representational state transfer](https://en.wikipedia.org/wiki/Representational_state_transfer), and is an architectural style created by computer scientist Roy Fielding and defined by 6 design constraints. 

Therefore a REST API is an application programming interface that conforms to the 6 REST constraints:

1.  A uniform interface between components so that information is transferred in a standardized form (based on uniform resource identifiers or URIs) instead of specific to an application’s needs. This is a central feature of REST. 
2. Client-server decoupling: an architecture composed of clients, servers, and resources.
3. Statelessness: there are no server-side sessions and servers are not allowed to store client data related to a client request. Each request must include all information needed for processing. 
4. Cacheability: resources should be cacheable when possible to reduce the need for client-server interactions and improve performance.
5. Layered system architecture: client-server interactions can be mediated by hierarchical layers.
6. Optionally - Code on demand: allows servers to extend the functionality of a client by transferring executable code.

Put it simply, clients send requests to servers in the form of a web URL as HTTP POST or GET or PUT or PATCH or DELETE requests (also known as CRUD operations: create, read, update, and delete). The servers send responses in the form of a resource which is typically JSON but could be anything like HTML, XML, or and image, for example.

## Crow
To install, download and install the deb package from the repo: https://github.com/CrowCpp/Crow/releases/tag/v1.0+5 

To compile, just include the header file: `#include <crow.h>` and link to the library `-lpthread`

## Redis
These installation instructions failed: https://github.com/cpp-redis/cpp_redis/wiki/Mac-&-Linux-Install,  because they need to be complemented with these: https://github.com/cpp-redis/cpp_redis/issues/105

```bash
$ # Clone the cpp-redis repo in the project directory
$ git clone https://github.com/cpp-redis/cpp_redis.git
$ # move inside the folder just created
$ cd cpp_redis
$ # Get the tacopie submodule
$ git submodule init && git submodule update

$ #apply the fix for issue #105
$ cd tacopie
$ git fetch origin pull/5/head:cmake-fixes
$ git checkout cmake-fixes
$ cd ..

$ # Create a build directory and move inside it
$ mkdir build && cd build
$ # Generate the Makefile using CMake
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ # Build the library
$ make
$ # Install the library. (sudo added by MH)
$ sudo make install
```

To compile:
- include the header file with `#include <cpp_redis/cpp_redis>`
- and in `tasks.json`, link to the library:
```json
"args": [
                ...
                "-lcpp_redis"
                ...
```
Note the compiler won't find the `libcpp_redis.so` library unless you update the `LD_LIBRARY_PATH` environment variable (needed every session) with :
```bash
$ export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

## Install the Redis server
The code compiles but fails to execute with a `connect()` Error:

```bash
terminate called after throwing an instance of 'cpp_redis::redis_error'
  what():  connect() failure
```

This is because the redis server was not running! We need to separately install and start the redis server. We do it in a separate terminal: 

```bash
[Terminal#1]$ # install redis_cli
[Terminal#1]$ sudo apt install redis-tools
[Terminal#1]$ # install redis-server
[Terminal#1]$ sudo apt install redis-server
[Terminal#1]$ # run the redis server (this will block the terminal)
[Terminal#1]$ redis-server
$ redis-server
533433:C 11 Jul 2023 23:05:51.509 # oO0OoO0OoO0Oo Redis is starting oO0OoO0OoO0Oo
533433:C 11 Jul 2023 23:05:51.509 # Redis version=5.0.7, bits=64, commit=00000000, modified=0, pid=533433, just started
533433:C 11 Jul 2023 23:05:51.509 # Warning: no config file specified, using the default config. In order to specify a config file use redis-server /path/to/redis.conf
533433:M 11 Jul 2023 23:05:51.510 * Increased maximum number of open files to 10032 (it was originally set to 1024).
                _._                                                  
           _.-``__ ''-._                                             
      _.-``    `.  `_.  ''-._           Redis 5.0.7 (00000000/0) 64 bit
  .-`` .-```.  ```\/    _.,_ ''-._                                   
 (    '      ,       .-`  | `,    )     Running in standalone mode
 |`-._`-...-` __...-.``-._|'` _.-'|     Port: 6379
 |    `-._   `._    /     _.-'    |     PID: 533433
  `-._    `-._  `-./  _.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |           http://redis.io        
  `-._    `-._`-.__.-'_.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |                                  
  `-._    `-._`-.__.-'_.-'    _.-'                                   
      `-._    `-.__.-'    _.-'                                       
          `-._        _.-'                                           
              `-.__.-'                                               

533433:M 11 Jul 2023 23:05:51.512 # Server initialized
533433:M 11 Jul 2023 23:05:51.512 # WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.
533433:M 11 Jul 2023 23:05:51.512 # WARNING you have Transparent Huge Pages (THP) support enabled in your kernel. This will create latency and memory usage issues with Redis. To fix this issue run the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled' as root, and add it to your /etc/rc.local in order to retain the setting after a reboot. Redis must be restarted after THP is disabled.
533433:M 11 Jul 2023 23:05:51.512 * DB loaded from disk: 0.000 seconds
533433:M 11 Jul 2023 23:05:51.512 * Ready to accept connections
```

Let's check the server is running:

```bash
$ # check redis server running
$ redis-cli ping
PONG
```

## Running the app
Execute the app as usual from vscode .

Send a GET request to the server by opening this endpoint in a web browser: http://0.0.0.0:3000/health or alternatively, from command line: 
```bash
$ curl http://0.0.0.0:3000/health
Working fine...

```
It works!

Post a few dummy posts:
```bash
$ curl -X POST "http://localhost:3000/api/blogs" -H "Content-Type: application/json" -d '{"title": "Post 1", "content":"Hello, world!" }'
$ curl -X POST "http://localhost:3000/api/blogs" -H "Content-Type: application/json" -d '{"title": "new post 2", "content":"Hello again!" }'
$ curl -X POST "http://localhost:3000/api/blogs" -H "Content-Type: application/json" -d '{"title": "new post 3", "content":"Hello for the third time!" }'

```

And check they are all stored:

```bash
$ curl http://localhost:3000/api/blogs | jq
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100   165  100   165    0     0   161k      0 --:--:-- --:--:-- --:--:--  161k
{
  "data": [
    {
      "content": "Hello for the third time!",
      "title": "new post 3"
    },
    {
      "title": "new post 2",
      "content": "Hello again!"
    },
    {
      "content": "Hello, world!",
      "title": "Post 1"
    }
  ]
}
```

Note the use of the [`jq` tool](https://www.digitalocean.com/community/tutorials/how-to-transform-json-data-with-jq) - installed with `sudo apt install jq` - to output JSON in a friendlier format.

To close, just stop the app and kill the redis server in `[Terminal#1]` with `CTRL+C`

## Troubleshooting

At some point I was not able to kill the redis server:

```bash
[Terminal#1] $ ...
^C527302:signal-handler (1689059999) Received SIGINT scheduling shutdown...
527302:M 11 Jul 2023 09:19:59.439 # User requested shutdown...
527302:M 11 Jul 2023 09:19:59.439 * Saving the final RDB snapshot before exiting.
527302:M 11 Jul 2023 09:19:59.439 # Failed opening the RDB file dump.rdb (in server root dir /usr/local/include/cpp_redis) for saving: Permission denied
527302:M 11 Jul 2023 09:19:59.439 # Error trying to save the DB, can't exit.
527302:M 11 Jul 2023 09:19:59.439 # SIGTERM received but errors trying to shut down the server, check the logs for more information
```
I used grep to identify and forcefully kill the server process:
```bash
$ ps aux | grep redis
mhered    527302  0.1  0.0  64852  7004 ?        Sl   09:16   0:00 redis-server *:6379
mhered    528223  0.0  0.0  11880  2552 pts/2    S+   09:25   0:00 grep --color=auto redis
mhered@gram:~$ kill -9 527302
```
## Conclusion

I don't fully understand everything I did there, and I am not sure that I have learnt enough about `crow` and `redis` that I can include these tools in my arsenal. Also I am not sure I could extend this minimal blog application into something a bit more useful by myself.

However I am really proud that I managed to find the several workarounds required to make it work.

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
- [x] databases
- [x] API
- [ ] web_scraping
- [ ] OpenCV