#link: https://github.com/PortAudio/portaudio/blob/master/examples/paex_pink.c

# Pink Noise

I want to add sound effects to my programs and it appears to be ridiculously difficult in C++. No? Check out this 90' talk on audio in C++: https://www.youtube.com/watch?v=UvRU25T_XOg

FMOD is cross-platform and multilanguage audio engine, but it is complicated:
* https://www.gamedev.net/tutorials/_/technical/game-programming/a-quick-guide-to-fmod-r2098/

* http://jerome.jouvie.free.fr/nativefmodex/tutorials/Tutorial01.php?run=Win

I tried and subsequently gave up on a few other alternatives ([ALSA](https://www.linuxjournal.com/article/6735), [libao](https://xiph.org/ao/), OpenAL...) before I settled for Portaudio.

## Installation
Download portaudio http://files.portaudio.com/download.html
Install dependencies: ALSA SDK
```bash
$ sudo apt install libasound-dev
```
Build portaudio:
```bash
$ ./configure && make
```

Make the header file `portaudio.h` and the library `libportaudio.a` accesible e.g. by copying to the project folder: 

```bash
$ cp lib/.libs/libportaudio.a /PROJECTFOLDER
$ cp include/portaudio.h /PROJECTFOLDER
```

Modify `tasks.json` to link to libraries and dependencies  

"-lrt", 
"-lm", 
"-lasound", 
"-ljack", 
"-pthread",

## Usage
Well I spent a lot of time trying to make sense of it and this is way too complicated. I only managed to get to work one of the examples included in the distribution: Copy & pasted 300 lines of code that play... pink noise. 

## What do you mean Pink noise? 

Are there different colors of noise? Well, apparently. I had heard about White noise. It turns out both Pink and White noise contain all of the frequencies perceived by humans (20 - 20K Hz), but in [Pink noise](https://en.wikipedia.org/wiki/Pink_noise) - a.k.a. Fractal noise - the lower frequencies are more prominent. 

Apparently Pink noise is often associated with certain relaxing sounds you might find in nature.  “The best comparison is probably pink noise is the sound of a waterfall,” [says Dr. Drerup](https://health.clevelandclinic.org/why-pink-noise-might-just-help-you-get-a-better-nights-sleep/). “White noise is more like static.” 

There you have it. 

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
- [ ] web_scraping
- [ ] OpenCV
- [x] sound