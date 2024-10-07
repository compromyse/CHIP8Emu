# CHIP8Emu

![image](https://github.com/compromyse/CHIP8Emu/assets/71056504/f87e9e73-f880-4d60-a61b-cdb40791211b)

## About The Project

CHIP8Emu is an emulator for the 1977 interpreter CHIP-8 written in C++. It aims to make games designed for the same playable on modern hardware.

## Compilation & Usage

For compilation, you need Clang, CMake, GNUMake, and SDL2. With them installed, run the following.
```sh
mkdir build; cd build
cmake ..
make
```

Replace `[scale]` with your preferred display scaling, `[delay]` with the your preferred delay, and `[ROM]` with the path to the game you intend to play.
```sh
./chip8emu [scale] [delay] [ROM]
```
<br>

# Thanks!
