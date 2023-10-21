#include <iostream>
#include <unistd.h>

#include "chip8.hpp"
#include "platform.hpp"

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
    std::exit(EXIT_FAILURE);
  }

  int videoScale = std::stoi(argv[1]);
  int cycleDelay = std::stoi(argv[2]);
  char const* filename = argv[3];

  Platform platform(
    "chip8emu",
    VIDEO_WIDTH * videoScale,
    VIDEO_HEIGHT * videoScale,
    VIDEO_WIDTH, VIDEO_HEIGHT
  );

  Chip8 chip8;
  chip8.LoadROM(filename);

  int count = 0;

  bool quit = false;
  while (!quit) {
    quit = platform.ProcessInput(&chip8.keypad);

    usleep(cycleDelay * 1000);

    chip8.Cycle();
    platform.Update(chip8.video, videoScale);
  }

  return 0;
}
