#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "nes.h"
#include "instructions.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        exit(1);
    }
    FILE* nes_file = fopen(argv[1], "r");
    struct nes_header* header = read_header(nes_file);
    nes_memory* memory = calloc(1, sizeof(nes_memory));
    read_prg_rom(nes_file, header, memory);
    struct nes_machine* machine = nes_create_machine(memory, header);
    machine->running = true;
    while (machine->running) {
        nes_cycle(machine);
    }
    free(header);
    free(memory);
    return 0;
}
