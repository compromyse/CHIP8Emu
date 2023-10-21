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
    bool ProcessInput(uint8_t* keys);

  private:
    SDL_Window* window {};
    SDL_Renderer* renderer {};
};

#endif
