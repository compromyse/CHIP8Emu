#include <iostream>
#include <unistd.h>
#include <thread>

#include "chip8.hpp"
#include "platform.hpp"

#define WINDOW_TITLE "chip8emu"

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
    std::exit(EXIT_FAILURE);
  }

  int videoScale = std::stoi(argv[1]);
  int cycleDelay = std::stoi(argv[2]);
  char const* filename = argv[3];

  Chip8* chip8 = new Chip8();
  Table* table = new Table(chip8);

  chip8->SetTable(table);

  chip8->LoadROM(filename);

  Platform platform(
    WINDOW_TITLE,
    VIDEO_WIDTH * videoScale,
    VIDEO_HEIGHT * videoScale,
    VIDEO_WIDTH, VIDEO_HEIGHT
  );

  std::thread timerThread(&Chip8::TimerUpdateThread, chip8, &platform);

  bool quit = false;
  while (!quit) {
    quit = platform.ProcessInput(&chip8->keypad);

    usleep(cycleDelay * 1000);

    chip8->Cycle();
    platform.Update(chip8->video, videoScale);
  }

  timerThread.detach();

  return 0;
}
