#ifndef PLATFORM_HPP_
#define PLATFORM_HPP_

#include <cstdint>
#include <SDL.h>

class Platform {
  public:
    Platform(
      const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight
    );
    ~Platform();

  public:
    void Update(const void* buffer, int pitch);
    bool ProcessInput(uint8_t* keys);

  private:
    SDL_Window* window {};
    SDL_Renderer* renderer {};
    SDL_Texture* texture {};
};

#endif
