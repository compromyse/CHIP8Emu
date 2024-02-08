#include <iostream>
#include <unistd.h>
#include <thread>

#include "chip8.hpp"
#include "platform.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define WINDOW_TITLE "chip8emu"

Platform platform (
  WINDOW_TITLE,
  VIDEO_WIDTH * 10,
  VIDEO_HEIGHT * 10,
  VIDEO_WIDTH, VIDEO_HEIGHT
);

Chip8* chip8 = new Chip8();

bool quit = false;

void mainLoop() {
    platform.Update(chip8->video, 10);
}

void update() {
  while (true) {
    quit = platform.ProcessInput(&chip8->keypad);

#ifdef __EMSCRIPTEN__
    if (quit) emscripten_cancel_main_loop();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
#else
    usleep(2 * 1000);
#endif
    chip8->Cycle();
  }
}

#ifdef __EMSCRIPTEN__
int main() {
  int videoScale = 10;
  int cycleDelay = 0;
  char const* filename = "roms/rom.ch8";
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

  Table* table = new Table(chip8);

  chip8->SetTable(table);

  chip8->LoadROM(filename);

  std::thread timerThread(&Chip8::TimerUpdateThread, chip8, &platform);
  std::thread updateThread(update);
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(mainLoop, 0, 1);
#else
  while (!quit)
    mainLoop();
  timerThread.detach();
#endif

  return 0;
}
