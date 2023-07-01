#link: https://github.com/OneLoneCoder/olcSoundWaveEngine/

# Asteroids with Sound Effects OK

After struggling to add sound effects to Asteroids in the previous project I started searching the web for ideas and stumbled upon [this video](https://www.youtube.com/watch?v=S8o5hAjE7hk) by OneLoneCoder in which he introduces his `olcSoundWaveEngine` project, which is just for that!

## Configuration

To compile we need to include the single header file [olcSoundWaveEngine.h](https://github.com/OneLoneCoder/olcSoundWaveEngine/blob/main/olcSoundWaveEngine.h) and add dependencies in `tasks.json`:

```json
 "args": [
            "-std=c++17",
            ...
            "-lX11",
            "-lGL",
            "-lpthread",
            "-lpng",
            "-lstdc++fs",
            "-lpulse",
            "-lpulse-simple"
            ...
```

Also seeems to need a placeholder file `oldSoundWaveEngine.cpp` for the compilation to work:

```c++
#define OLC_SOUNDWAVE
#include "olcSoundWaveEngine.h"
```

I added sound effects for the blaster, thrust, asteroid explosion and ship explosion/gameover.
Lacking proper controls for how long sounds will play or ways to manage overlapping sounds I had to make do with playback speeds (not robust).
I also added a new wireframe model for the destroyed ship to match the sound effect.

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
- [x] games
- [x] sounds 