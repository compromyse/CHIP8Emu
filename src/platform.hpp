#ifndef PLATFORM_HPP_
#define PLATFORM_HPP_

#include <cstdint>
#include <bitset>

#include <SDL.h>

class Platform {
  public:
    Platform(
      const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight
    );
    ~Platform();

  public:
    void Update(const std::bitset<2048>& bitset, int videoScale);
    bool ProcessInput(std::bitset<16>* keys);
    void StartBeep();
    void StopBeep();

  private:
    static void AudioCallback(void* userdata, uint8_t* stream, int len);
    bool beepRequested = false;

  private:
    SDL_Window* window {};
    SDL_Renderer* renderer {};
    SDL_AudioDeviceID audioDevice;
    SDL_AudioSpec audioSpec {};
};

#endif
