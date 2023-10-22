#ifndef CHIP8_H_
#define CHIP8_H_

#include <cstdint>
#include <random>
#include <bitset>
#include <mutex>

#include "platform.hpp"

const uint32_t VIDEO_HEIGHT = 32;
const uint32_t VIDEO_WIDTH = 64;

class Chip8 {
  public:
    Chip8();

  private:
    uint8_t registers[16] {};
    uint8_t memory[4096] {};
    
    uint16_t index {};
    uint16_t pc {};
    uint16_t stack[16] {};
    uint8_t sp {};

    uint8_t delayTimer {};
    uint8_t soundTimer {};

    uint16_t opcode;

  public:
    std::bitset<16> keypad;
    std::bitset<2048> video; 

  private:
    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;
    std::mutex timerMutex;

  public:
    void LoadROM(const char* filename);
    void Cycle();
    void TimerUpdateThread(Platform* platform);

  private:
    void SetupTable();

  private:
    typedef void (Chip8::*OpcodeFunction)();
    OpcodeFunction table[0x10u];
    OpcodeFunction table0[0xFu];
    OpcodeFunction table8[0xFu];
    OpcodeFunction tableE[0xFu];
    OpcodeFunction tableF[0x65u];
    
    void Table0();
    void Table8();
    void TableE();
    void TableF();

    void OP_NULL(); void OP_00E0(); void OP_00EE();
    void OP_1nnn(); void OP_2nnn(); void OP_3xkk();
    void OP_4xkk(); void OP_5xy0(); void OP_6xkk();
    void OP_7xkk(); void OP_8xy0(); void OP_8xy1();
    void OP_8xy2(); void OP_8xy3(); void OP_8xy4();
    void OP_8xy5(); void OP_8xy6(); void OP_8xy7();
    void OP_8xyE(); void OP_9xy0(); void OP_Annn();
    void OP_Bnnn(); void OP_Cxkk(); void OP_Dxyn();
    void OP_Ex9E(); void OP_ExA1(); void OP_Fx07();
    void OP_Fx0A(); void OP_Fx15(); void OP_Fx18();
    void OP_Fx1E(); void OP_Fx29(); void OP_Fx33();
    void OP_Fx55(); void OP_Fx65();
};

#endif
