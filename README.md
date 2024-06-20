# CHIP8Emu
An emulator for CHIP-8 written in C++

![image](https://github.com/compromyse/CHIP8Emu/assets/71056504/495b0590-5635-4832-bb40-88cec0727053)

## Building

### Requirements

* CMake
* SDL2
* Make
* EmSDK (For emscripten)

### Running the build

#### Native

```sh
mkdir build; cd build
cmake ..
make
```

#### Emscripten

```sh
mkdir build; cd build
emcmake cmake ..
emmake make
```

There will be a `chip8emu.html` in `build/`

## Syntax
```sh
./chip8emu <Scale> <Delay> <ROM>
```

# Thanks!
