#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NES_H
#define NES_H

#define GAME_RAM          0x0000
#define GAME_RAM_SIZE     0x0800
#define ZERO_PAGE_SIZE    0x0100
#define STACK_MEMORY      0x0100
#define STACK_MEMORY_SIZE 0x0100
#define RAM               0x0200
#define RAM_SIZE          0x0600
#define MIRROR_1          0x0800
#define MIRROR_2          0x1000
#define MIRROR_3          0x1800
#define PRG_ROM_BANK_SIZE 0x4000
#define PRG_ROM_LOWER     0x8000
#define PRG_ROM_UPPER     0xC000

typedef uint8_t nes_memory[0x10000];
struct nes_cpu {
    bool     has_jumped;
    uint8_t  a;      // accumulator
    uint8_t  x;      // x index
    uint8_t  y;      // y index
    uint8_t  s;      // stack pointer
    uint8_t  p;      // status register
    uint16_t pc;     // program counter
    uint16_t cycles; // scanline cycles
    int16_t sl;      // scanline
};
struct nes_header {
    uint16_t prg_rom; // (16384 * x bytes)
    uint16_t chr_rom; // (8192 * y bytes) , with 0 -> using CHR RAM
    uint16_t prg_ram; // 8KB units with 0 -> using 8KB
    uint8_t flags_6;
    uint8_t flags_7;
    uint8_t flags_9;
    uint8_t flags_10;
};
struct nes_machine {
    bool running;
    struct nes_header* header;
    nes_memory* memory;
    struct nes_cpu* cpu;
} __attribute__((packed));

void check_magic_string(FILE* file);
void check_header_fill(FILE* file);
struct nes_header* read_header(FILE* file);
void print_header(struct nes_header* header);
void read_prg_rom(FILE* file, struct nes_header* header, nes_memory* memory);
void dump_memory(nes_memory* memory, size_t amount, size_t start);

struct nes_machine* nes_create_machine(nes_memory* memory,
                                       struct nes_header* header);
#endif // NES_H
