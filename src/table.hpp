#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <functional>

#include "chip8.hpp"

class Chip8;

class Table {
  public:
    Table(Chip8* chip8);

  private:
    Chip8* chip8;

  public:
    using OpcodeFunction = std::function<void()>;
    OpcodeFunction table[0x10u];
    OpcodeFunction table0[0xFu];
    OpcodeFunction table8[0xFu];
    OpcodeFunction tableE[0xFu];
    OpcodeFunction tableF[0x66u];

    void Table0();
    void Table8();
    void TableE();
    void TableF();
};

#endif
