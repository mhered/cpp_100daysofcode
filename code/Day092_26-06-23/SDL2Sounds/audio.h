#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <string>
class Audio {

public:
    ~Audio();
    void load(std::string filename);
    void play();

private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
};

Audio::~Audio() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void Audio::load(std::string filename) {
    SDL_LoadWAV(filename.c_str(), &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void Audio::play() {
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}


#endif //AUDIO_H