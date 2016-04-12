#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "nes.h"


void check_magic_string(FILE* file) {
    char expected_magic_string[] = {'N', 'E', 'S', '\x1A'};
    char magic_string[sizeof(expected_magic_string)];
    fread(&magic_string, sizeof(expected_magic_string), 1, file);
    assert(strncmp(magic_string, expected_magic_string,
                   sizeof(expected_magic_string)) == 0);
}

void check_header_fill(FILE* file) {
    char expected_header_fill[] = {0, 0, 0, 0, 0};
    char header_fill[sizeof(expected_header_fill)];
    fread(&header_fill, sizeof(expected_header_fill), 1, file);
    assert(strncmp(expected_header_fill, header_fill,
                   sizeof(expected_header_fill)) == 0);
}

struct nes_header* read_header(FILE* file) {
    check_magic_string(file);
    struct nes_header* header = calloc(1, sizeof(header));
    fscanf(file, "%c%c%c%c%c%c%c",
           (uint8_t*) &header->prg_rom,
           (uint8_t*) &header->chr_rom, //8KB units, with 0 -> using CHR RAM
           &header->flags_6,
           &header->flags_7,
           (uint8_t*) &header->prg_ram, // 8KB units with 0 -> using 8KB
           &header->flags_9,
           &header->flags_10
          );
    header->prg_rom *= 0x4000;
    if (header->chr_rom != 0) {
        header->chr_rom *= 0x2000;
    }
    if (header->prg_ram == 0) {
        header->prg_ram = 0x2000;
    } else {
        header->prg_ram *= 0x2000;
    }
    check_header_fill(file);
    return header;
}

void print_header(struct nes_header* header) {
    printf("Header information:\n");
    printf("prg_rom: %d\n", header->prg_rom);
    printf("chr_rom: %d\n", header->chr_rom);
    printf("flags_6: %d\n", header->flags_6);
    printf("flags_7: %d\n", header->flags_7);
    printf("prg_ram: %d\n", header->prg_ram);
    printf("flags_9: %d\n", header->flags_9);
    printf("flags_10: %d\n", header->flags_10);
}

void read_prg_rom(FILE* file,
                  __attribute__((unused)) struct nes_header* header,
                  nes_memory* memory) {
    // TODO: two prg rom banks
    fread(*memory + PRG_ROM_UPPER, 1, PRG_ROM_BANK_SIZE, file);
}

void dump_memory(nes_memory* memory, size_t amount, size_t start) {
    uint8_t offset = 16;
    for (size_t i = 0; i < amount; i++) {
        if (i % (offset) == 0) {
            printf("0x%04lx", i + start);
        }
        if (i % (offset >> 1) == 0) {
            printf(" ");
        }
        printf(" %02x", (*memory)[i + start]);
        if (i % (offset) == offset - 1 && i < amount - 1) {
            printf("\n");
        }
    }
    printf("\n");
}

struct nes_machine* nes_create_machine(nes_memory* memory,
                                       struct nes_header* header) {
    struct nes_machine* machine = calloc(1, sizeof(struct nes_machine));
    machine->memory = memory;
    machine->header = header;
    machine->cpu = calloc(1, sizeof(struct nes_cpu));
    machine->cpu->pc = PRG_ROM_UPPER;
    return machine;
}
