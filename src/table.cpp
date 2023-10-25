#include "table.hpp"
#include <iostream>

Table::Table(Chip8* chip8) : chip8(chip8) {
  for (size_t i = 0; i < sizeof(table0) / sizeof(table0[0]); i++) {
    table0[i] = [chip8] { chip8->OP_NULL(); };
    table8[i] = [chip8] { chip8->OP_NULL(); };
    tableE[i] = [chip8] { chip8->OP_NULL(); };
  }

  for (size_t i = 0; i < sizeof(tableF) / sizeof(tableF[0]); i++) {
    tableF[i] = [chip8] { chip8->OP_NULL(); };
  }

  table[0x0] = [this] { Table0(); };
  table[0x1] = [chip8] { chip8->OP_1nnn(); };
  table[0x2] = [chip8] { chip8->OP_2nnn(); };
  table[0x3] = [chip8] { chip8->OP_3xkk(); };
  table[0x4] = [chip8] { chip8->OP_4xkk(); };
  table[0x5] = [chip8] { chip8->OP_5xy0(); };
  table[0x6] = [chip8] { chip8->OP_6xkk(); };
  table[0x7] = [chip8] { chip8->OP_7xkk(); };

  table[0x8] = [this] { Table8(); };

  table[0x9] = [chip8] { chip8->OP_9xy0(); };
  table[0xA] = [chip8] { chip8->OP_Annn(); };
  table[0xB] = [chip8] { chip8->OP_Bnnn(); };
  table[0xC] = [chip8] { chip8->OP_Cxkk(); };
  table[0xD] = [chip8] { chip8->OP_Dxyn(); };

  table[0xE] = [this] { TableE(); };
  table[0xF] = [this] { TableF(); };

  table0[0x0] = [chip8] { chip8->OP_00E0(); };
  table0[0xE] = [chip8] { chip8->OP_00EE(); };

  table8[0x0] = [chip8] { chip8->OP_8xy0(); };
  table8[0x1] = [chip8] { chip8->OP_8xy1(); };
  table8[0x2] = [chip8] { chip8->OP_8xy2(); };
  table8[0x3] = [chip8] { chip8->OP_8xy3(); };
  table8[0x4] = [chip8] { chip8->OP_8xy4(); };
  table8[0x5] = [chip8] { chip8->OP_8xy5(); };
  table8[0x6] = [chip8] { chip8->OP_8xy6(); };
  table8[0x7] = [chip8] { chip8->OP_8xy7(); };
  table8[0xE] = [chip8] { chip8->OP_8xyE(); };

  tableE[0x1] = [chip8] { chip8->OP_ExA1(); };
  tableE[0xE] = [chip8] { chip8->OP_Ex9E(); };

  tableF[0x07] = [chip8] { chip8->OP_Fx07(); };
  tableF[0x0A] = [chip8] { chip8->OP_Fx0A(); };
  tableF[0x15] = [chip8] { chip8->OP_Fx15(); };
  tableF[0x18] = [chip8] { chip8->OP_Fx18(); };
  tableF[0x1E] = [chip8] { chip8->OP_Fx1E(); };
  tableF[0x29] = [chip8] { chip8->OP_Fx29(); };
  tableF[0x33] = [chip8] { chip8->OP_Fx33(); };
  tableF[0x55] = [chip8] { chip8->OP_Fx55(); };
  tableF[0x65] = [chip8] { chip8->OP_Fx65(); };
}

void Table::Table0() {
  table0[chip8->opcode & 0x000Fu]();
}

void Table::Table8() {
  table8[chip8->opcode & 0x000Fu]();
}

void Table::TableE() {
  tableE[chip8->opcode & 0x000Fu]();
}

void Table::TableF() {
  tableF[chip8->opcode & 0x00FFu]();
}
