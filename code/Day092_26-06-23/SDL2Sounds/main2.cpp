#include "audio.h"
#include <unistd.h> // sleep
#include <string>
int main()
{
    SDL_Init(SDL_INIT_AUDIO);

    std::string path = "/home/mhered/cpp_100daysofcode/code/Day092_26-06-23/SDL/soundclips/";

    Audio fire, explosion, thrust;

    fire.load(path + "/" + "phaser2.wav");
    explosion.load(path + "/" + "explosion.wav");
    thrust.load(path + "/" + "thrust2.wav");
    
    fire.play();
    sleep(1);

    explosion.play();
    sleep(3);

    thrust.play();
    sleep(2);

    SDL_Quit();
}