#include <iostream>
#include <unistd.h>
#include <thread>

#include "chip8.hpp"
#include "platform.hpp"

#define WINDOW_TITLE "chip8emu"

Platform pPlatform(
  WINDOW_TITLE,
  VIDEO_WIDTH * 10,
  VIDEO_HEIGHT * 10,
  VIDEO_WIDTH, VIDEO_HEIGHT
);

Chip8* pChip8;

void mainLoop() {
  Platform* platform = &pPlatform;
  platform->ProcessInput(&pChip8->keypad);

  usleep(2 * 1000);
  platform->ProcessInput(&pChip8->keypad);
  pChip8->Cycle();
  platform->Update(pChip8->video, 10);
}

#ifdef __EMSCRIPTEN__

#include <emscripten.h>
int main() {
  int videoScale = 10;
  int cycleDelay = 0;
  char const* filename = "test_opcode.ch8";

#else

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  int videoScale = std::stoi(argv[1]);
  int cycleDelay = std::stoi(argv[2]);
  char const* filename = argv[3];

#endif

  Chip8* chip8 = new Chip8();
  Table* table = new Table(chip8);

  chip8->SetTable(table);

  chip8->LoadROM(filename);

  pChip8 = chip8;

  /* Platform platform(
    WINDOW_TITLE,
    VIDEO_WIDTH * videoScale,
    VIDEO_HEIGHT * videoScale,
    VIDEO_WIDTH, VIDEO_HEIGHT
  ); */

  // std::thread timerThread(&Chip8::TimerUpdateThread, chip8, &platform);
#ifdef __EMSCRIPTEN__

  emscripten_set_main_loop(mainLoop, 0, 0);

#else
  
  bool quit = false;
  while (!quit)
    mainLoop();

#endif

  // timerThread.detach();
  return 0;
}
