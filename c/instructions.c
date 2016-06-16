#include <string.h>

#define DEBUG
#define CYCLE_MULT 3

#include "instructions.h"
#pragma GCC diagnostic ignored "-Wmissing-noreturn"

#ifdef DEBUG
struct nes_cpu previous_cpu_state;
#endif

void (*instructions[0x100])(struct nes_machine*) = {
    nes_brk, nes_ora, nes_kil, nes_slo, nes_nop, nes_ora, nes_asl, nes_slo,
    nes_php, nes_ora, nes_asl, nes_anc, nes_nop, nes_ora, nes_asl, nes_slo,
    nes_bpl, nes_ora, nes_kil, nes_slo, nes_nop, nes_ora, nes_asl, nes_slo,
    nes_clc, nes_ora, nes_nop, nes_slo, nes_nop, nes_ora, nes_asl, nes_slo,
    nes_jsr, nes_and, nes_kil, nes_rla, nes_bit, nes_and, nes_rol, nes_rla,
    nes_plp, nes_and, nes_rol, nes_anc, nes_bit, nes_and, nes_rol, nes_rla,
    nes_bmi, nes_and, nes_kil, nes_rla, nes_nop, nes_and, nes_rol, nes_rla,
    nes_sec, nes_and, nes_nop, nes_rla, nes_nop, nes_and, nes_rol, nes_rla,
    nes_rti, nes_eor, nes_kil, nes_sre, nes_nop, nes_eor, nes_lsr, nes_sre,
    nes_pha, nes_eor, nes_lsr, nes_alr, nes_jmp, nes_eor, nes_lsr, nes_sre,
    nes_bvc, nes_eor, nes_kil, nes_sre, nes_nop, nes_eor, nes_lsr, nes_sre,
    nes_cli, nes_eor, nes_nop, nes_sre, nes_nop, nes_eor, nes_lsr, nes_sre,
    nes_rts, nes_adc, nes_kil, nes_rra, nes_nop, nes_adc, nes_ror, nes_rra,
    nes_pla, nes_adc, nes_ror, nes_arr, nes_jmp, nes_adc, nes_ror, nes_rra,
    nes_bvs, nes_adc, nes_kil, nes_rra, nes_nop, nes_adc, nes_ror, nes_rra,
    nes_sei, nes_adc, nes_nop, nes_rra, nes_nop, nes_adc, nes_ror, nes_rra,
    nes_nop, nes_sta, nes_nop, nes_sax, nes_sty, nes_sta, nes_stx, nes_sax,
    nes_dey, nes_nop, nes_txa, nes_xaa, nes_sty, nes_sta, nes_stx, nes_sax,
    nes_bcc, nes_sta, nes_kil, nes_ahx, nes_sty, nes_sta, nes_stx, nes_sax,
    nes_tya, nes_sta, nes_txs, nes_tas, nes_shy, nes_sta, nes_shx, nes_ahx,
    nes_ldy, nes_lda, nes_ldx, nes_lax, nes_ldy, nes_lda, nes_ldx, nes_lax,
    nes_tay, nes_lda, nes_tax, nes_lax, nes_ldy, nes_lda, nes_ldx, nes_lax,
    nes_bcs, nes_lda, nes_kil, nes_lax, nes_ldy, nes_lda, nes_ldx, nes_lax,
    nes_clv, nes_lda, nes_tsx, nes_las, nes_ldy, nes_lda, nes_ldx, nes_lax,
    nes_cpy, nes_cmp, nes_nop, nes_dcp, nes_cpy, nes_cmp, nes_dec, nes_dcp,
    nes_iny, nes_cmp, nes_dex, nes_axs, nes_cpy, nes_cmp, nes_dec, nes_dcp,
    nes_bne, nes_cmp, nes_kil, nes_dcp, nes_nop, nes_cmp, nes_dec, nes_dcp,
    nes_cld, nes_cmp, nes_nop, nes_dcp, nes_nop, nes_cmp, nes_dec, nes_dcp,
    nes_cpx, nes_sbc, nes_nop, nes_isc, nes_cpx, nes_sbc, nes_inc, nes_isc,
    nes_inx, nes_sbc, nes_nop, nes_sbc, nes_cpx, nes_sbc, nes_inc, nes_isc,
    nes_beq, nes_sbc, nes_kil, nes_isc, nes_nop, nes_sbc, nes_inc, nes_isc,
    nes_sed, nes_sbc, nes_nop, nes_isc, nes_nop, nes_sbc, nes_inc, nes_isc,
};

char nes_instruction_names[0x100][4] = {
    "BRK", "ORA", "KIL", "SLO", "NOP", "ORA", "ASL", "SLO",
    "PHP", "ORA", "ASL", "ANC", "NOP", "ORA", "ASL", "SLO",
    "BPL", "ORA", "KIL", "SLO", "NOP", "ORA", "ASL", "SLO",
    "CLC", "ORA", "NOP", "SLO", "NOP", "ORA", "ASL", "SLO",
    "JSR", "AND", "KIL", "RLA", "BIT", "AND", "ROL", "RLA",
    "PLP", "AND", "ROL", "ANC", "BIT", "AND", "ROL", "RLA",
    "BMI", "AND", "KIL", "RLA", "NOP", "AND", "ROL", "RLA",
    "SEC", "AND", "NOP", "RLA", "NOP", "AND", "ROL", "RLA",
    "RTI", "EOR", "KIL", "SRE", "NOP", "EOR", "LSR", "SRE",
    "PHA", "EOR", "LSR", "ALR", "JMP", "EOR", "LSR", "SRE",
    "BVC", "EOR", "KIL", "SRE", "NOP", "EOR", "LSR", "SRE",
    "CLI", "EOR", "NOP", "SRE", "NOP", "EOR", "LSR", "SRE",
    "RTS", "ADC", "KIL", "RRA", "NOP", "ADC", "ROR", "RRA",
    "PLA", "ADC", "ROR", "ARR", "JMP", "ADC", "ROR", "RRA",
    "BVS", "ADC", "KIL", "RRA", "NOP", "ADC", "ROR", "RRA",
    "SEI", "ADC", "NOP", "RRA", "NOP", "ADC", "ROR", "RRA",
    "NOP", "STA", "NOP", "SAX", "STY", "STA", "STX", "SAX",
    "DEY", "NOP", "TXA", "XAA", "STY", "STA", "STX", "SAX",
    "BCC", "STA", "KIL", "AHX", "STY", "STA", "STX", "SAX",
    "TYA", "STA", "TXS", "TAS", "SHY", "STA", "SHX", "AHX",
    "LDY", "LDA", "LDX", "LAX", "LDY", "LDA", "LDX", "LAX",
    "TAY", "LDA", "TAX", "LAX", "LDY", "LDA", "LDX", "LAX",
    "BCS", "LDA", "KIL", "LAX", "LDY", "LDA", "LDX", "LAX",
    "CLV", "LDA", "TSX", "LAS", "LDY", "LDA", "LDX", "LAX",
    "CPY", "CMP", "NOP", "DCP", "CPY", "CMP", "DEC", "DCP",
    "INY", "CMP", "DEX", "AXS", "CPY", "CMP", "DEC", "DCP",
    "BNE", "CMP", "KIL", "DCP", "NOP", "CMP", "DEC", "DCP",
    "CLD", "CMP", "NOP", "DCP", "NOP", "CMP", "DEC", "DCP",
    "CPX", "SBC", "NOP", "ISC", "CPX", "SBC", "INC", "ISC",
    "INX", "SBC", "NOP", "SBC", "CPX", "SBC", "INC", "ISC",
    "BEQ", "SBC", "KIL", "ISC", "NOP", "SBC", "INC", "ISC",
    "SED", "SBC", "NOP", "ISC", "NOP", "SBC", "INC", "ISC",
};

enum nes_addressing_mode nes_addressing_modes[0x100] = {
    IMPLICIT, INDEXED_INDIRECT, IMPLICIT, INDEXED_INDIRECT,
    ZERO_PAGE, ZERO_PAGE, ZERO_PAGE, ZERO_PAGE,
    IMPLICIT, IMMEDIATE, ACCUMULATOR, IMMEDIATE,
    ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE,
    RELATIVE, INDIRECT_INDEXED, IMPLICIT, INDIRECT_INDEXED,
    ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X,
    IMPLICIT, ABSOLUTE_Y, IMPLICIT, ABSOLUTE_Y,
    ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X,
    ABSOLUTE, INDEXED_INDIRECT, IMPLICIT, INDEXED_INDIRECT,
    ZERO_PAGE, ZERO_PAGE, ZERO_PAGE, ZERO_PAGE,
    IMPLICIT, IMMEDIATE, ACCUMULATOR, IMMEDIATE,
    ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE,
    RELATIVE, INDIRECT_INDEXED, IMPLICIT, INDIRECT_INDEXED,
    ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X,
    IMPLICIT, ABSOLUTE_Y, IMPLICIT, ABSOLUTE_Y,
    ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X,
    IMPLICIT, INDEXED_INDIRECT, IMPLICIT, INDEXED_INDIRECT,
    ZERO_PAGE, ZERO_PAGE, ZERO_PAGE, ZERO_PAGE,
    IMPLICIT, IMMEDIATE, ACCUMULATOR, IMMEDIATE,
    ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE,
    RELATIVE, INDIRECT_INDEXED, IMPLICIT, INDIRECT_INDEXED,
    ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X,
    IMPLICIT, ABSOLUTE_Y, IMPLICIT, ABSOLUTE_Y,
    ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X,
    IMPLICIT, INDEXED_INDIRECT, IMPLICIT, INDEXED_INDIRECT,
    ZERO_PAGE, ZERO_PAGE, ZERO_PAGE, ZERO_PAGE,
    IMPLICIT, IMMEDIATE, ACCUMULATOR, IMMEDIATE,
    INDIRECT, ABSOLUTE, ABSOLUTE, ABSOLUTE,
    RELATIVE, INDIRECT_INDEXED, IMPLICIT, INDIRECT_INDEXED,
    ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X,
    IMPLICIT, ABSOLUTE_Y, IMPLICIT, ABSOLUTE_Y,
    ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X,
    IMMEDIATE, INDEXED_INDIRECT, IMMEDIATE, INDEXED_INDIRECT,
    ZERO_PAGE, ZERO_PAGE, ZERO_PAGE, ZERO_PAGE,
    IMPLICIT, IMMEDIATE, IMPLICIT, IMMEDIATE,
    ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE,
    RELATIVE, INDIRECT_INDEXED, IMPLICIT, INDIRECT_INDEXED,
    ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_Y, ZERO_PAGE_Y,
    IMPLICIT, ABSOLUTE_Y, IMPLICIT, ABSOLUTE_Y,
    ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_Y, ABSOLUTE_Y,
    IMMEDIATE, INDEXED_INDIRECT, IMMEDIATE, INDEXED_INDIRECT,
    ZERO_PAGE, ZERO_PAGE, ZERO_PAGE, ZERO_PAGE,
    IMPLICIT, IMMEDIATE, IMPLICIT, IMMEDIATE,
    ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE,
    RELATIVE, INDIRECT_INDEXED, IMPLICIT, INDIRECT_INDEXED,
    ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_Y, ZERO_PAGE_Y,
    IMPLICIT, ABSOLUTE_Y, IMPLICIT, ABSOLUTE_Y,
    ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_Y, ABSOLUTE_Y,
    IMMEDIATE, INDEXED_INDIRECT, IMMEDIATE, INDEXED_INDIRECT,
    ZERO_PAGE, ZERO_PAGE, ZERO_PAGE, ZERO_PAGE,
    IMPLICIT, IMMEDIATE, IMPLICIT, IMMEDIATE,
    ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE,
    RELATIVE, INDIRECT_INDEXED, IMPLICIT, INDIRECT_INDEXED,
    ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X,
    IMPLICIT, ABSOLUTE_Y, IMPLICIT, ABSOLUTE_Y,
    ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X,
    IMMEDIATE, INDEXED_INDIRECT, IMMEDIATE, INDEXED_INDIRECT,
    ZERO_PAGE, ZERO_PAGE, ZERO_PAGE, ZERO_PAGE,
    IMPLICIT, IMMEDIATE, IMPLICIT, IMMEDIATE,
    ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE,
    RELATIVE, INDIRECT_INDEXED, IMPLICIT, INDIRECT_INDEXED,
    ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X, ZERO_PAGE_X,
    IMPLICIT, ABSOLUTE_Y, IMPLICIT, ABSOLUTE_Y,
    ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X
};

uint8_t nes_instruction_sizes[0x100] = {
    1, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    3, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    1, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    1, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 0, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 0, 3, 0, 0,
    2, 2, 2, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
};

uint8_t nes_instruction_cycles[0x100] = {
    7, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    6, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
    2, 6, 2, 6, 4, 4, 4, 4, 2, 5, 2, 5, 5, 5, 5, 5,
    2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
    2, 5, 2, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4,
    2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
};
void nes_set_carry(struct nes_machine* machine, bool value) {
    if (value) {
        machine->cpu->p |= 1 << NES_CARRY;
    } else {
        machine->cpu->p &= ~(1 << NES_CARRY);
    }
}

bool nes_get_carry(struct nes_machine* machine) {
    return ((machine->cpu->p >> NES_CARRY) & 1);
}

void nes_set_zero(struct nes_machine* machine, uint8_t value) {
    if (value == 0) {
        machine->cpu->p |= 1 << NES_ZERO;
    } else {
        machine->cpu->p &= ~(1 << NES_ZERO);
    }
}

bool nes_get_zero(struct nes_machine* machine) {
    return ((machine->cpu->p >> NES_ZERO) & 1);
}

void nes_set_negative(struct nes_machine* machine, uint8_t value) {
    if ((int8_t) value < 0) {
        machine->cpu->p |= 1 << NES_NEGATIVE;
    } else {
        machine->cpu->p &= ~(1 << NES_NEGATIVE);
    }
}

bool nes_get_negative(struct nes_machine* machine) {
    return ((machine->cpu->p >> NES_NEGATIVE) & 1);
}

void nes_set_overflow(struct nes_machine* machine, bool value) {
    if (value) {
        machine->cpu->p |= 1 << NES_OVERFLOW;
    } else {
        machine->cpu->p &= ~(1 << NES_OVERFLOW);
    }
}

bool nes_get_overflow(struct nes_machine* machine) {
    return ((machine->cpu->p >> NES_OVERFLOW) & 1);
}

void nes_set_interrupt_disable(struct nes_machine* machine, bool value) {
    if (value) {
        machine->cpu->p |= 1 << NES_INTERRUPT_DISABLE;
    } else {
        machine->cpu->p &= ~(1 << NES_INTERRUPT_DISABLE);
    }
}

void nes_set_decimal_mode(struct nes_machine* machine, bool value) {
    if (value) {
        machine->cpu->p |= 1 << NES_DECIMAL_FLAG;
    } else {
        machine->cpu->p &= ~(1 << NES_DECIMAL_FLAG);
    }
}

void nes_rel_jump(struct nes_machine* machine, uint8_t offset) {
    machine->cpu->pc += offset;
}

void nes_abs_jump(struct nes_machine* machine, uint16_t address) {
    machine->cpu->pc = address;
}

void nes_stack_push(struct nes_machine* machine, uint8_t value) {
    nes_write_memory(machine, 0x0100 | machine->cpu->s, value);
    machine->cpu->s -= 1;
}

uint8_t nes_stack_pop(struct nes_machine* machine) {
    uint8_t value = nes_read_memory(machine, 0x0100 | (++machine->cpu->s));
    return value;
}

uint8_t nes_opcode(struct nes_machine* machine) {
    return (*machine->memory)[machine->cpu->pc];
}

uint8_t nes_instruction_size(struct nes_machine* machine) {
    uint8_t opcode = nes_opcode(machine);
    return nes_instruction_sizes[opcode];
}

uint8_t nes_read_memory(struct nes_machine* machine, uint16_t address) {
    return (*machine->memory)[address];
}

void nes_write_memory(struct nes_machine* machine,
                      uint16_t address,
                      uint8_t value) {
    (*machine->memory)[address] = value;
}

bool pages_differ(uint16_t a, uint16_t b) {
    return (a & 0xFF00) != (b & 0xFF00);
}

void nes_cycle(struct nes_machine* machine) {
    machine->cpu->has_jumped = false;
    // we shouldn't go to the next instr if we've jumped!
    uint8_t opcode = nes_opcode(machine);

#ifdef DEBUG
    uint8_t instruction_size = nes_instruction_size(machine);
    printf("%04X  ", machine->cpu->pc);
    for (uint16_t i = 0; i < instruction_size; i++) {
        printf("%02X ", nes_read_memory(machine, machine->cpu->pc + i));
    }
    for (int i = 0; i < 3 - instruction_size; i++) {
        printf("   ");
    }
    char* instruction = nes_instruction_names[opcode];
    printf(" %s ", instruction);
    previous_cpu_state =  *(machine->cpu);
#endif

    instructions[opcode](machine);
    if (!machine->cpu->has_jumped) {
        machine->cpu->pc += nes_instruction_sizes[opcode];
    }
    machine->cpu->cycles += nes_instruction_cycles[opcode] * CYCLE_MULT; // wtf
    if (machine->cpu->cycles >= 341) {
        machine->cpu->sl += 1;
    }
    machine->cpu->cycles %= 341;
    if (machine->cpu->sl > 260) {
        machine->cpu->sl = -1;
    }
#ifdef DEBUG
    printf("A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%3u SL:%d\n",
           previous_cpu_state.a,
           previous_cpu_state.x,
           previous_cpu_state.y,
           previous_cpu_state.p,
           previous_cpu_state.s,
           previous_cpu_state.cycles,
           previous_cpu_state.sl);
#endif
}

uint16_t nes_address(struct nes_machine* machine) {
    uint8_t x = machine->cpu->x;
    uint8_t y = machine->cpu->y;
    uint16_t pc = machine->cpu->pc;
    uint8_t opcode = nes_opcode(machine);
    enum nes_addressing_mode mode = nes_addressing_modes[opcode];
    uint8_t offset = nes_read_memory(machine, pc + 1);
#ifdef DEBUG
    char* instruction = nes_instruction_names[opcode];
#endif

    uint16_t address = 0;
    bool page_crossed;
    switch (mode) {
    case IMPLICIT:
        address =  0;
#ifdef DEBUG
        printf("                            ");
#endif
        break;
    case ACCUMULATOR:
        address = 0;
#ifdef DEBUG
        printf("A                           ");
#endif
        break;
    case IMMEDIATE:
        address = pc + 1;
#ifdef DEBUG
        printf("#$%02X                        ", nes_read_memory(machine, address));
#endif
        break;
    case ZERO_PAGE:
        address = nes_read_memory(machine, pc + 1);
#ifdef DEBUG
        printf("$%02X = %02X                    ",
               address & 0xFF,
               nes_read_memory(machine, address));
        break;
#endif
    case ZERO_PAGE_X:
        address = nes_read_memory(machine, pc + x);
#ifdef DEBUG
        printf("#$%02X                        ", nes_read_memory(machine, address));
#endif
        break;
    case ZERO_PAGE_Y:
        address = nes_read_memory(machine, pc + y);
#ifdef DEBUG
        printf("#$%02X                        ", nes_read_memory(machine, address));
#endif
        break;
    case RELATIVE:
        if (offset < 0x80) {
            address = pc + 2 + offset;
        } else {
            address = pc + 2 + offset - 0x100;
        }
#ifdef DEBUG
        printf("$%04X                       ", address);
#endif
        break;
    case ABSOLUTE:
        address = (uint16_t) (nes_read_memory(machine, pc + 1) +
            (nes_read_memory(machine, pc + 2) << 8));
#ifdef DEBUG
        // Hacky way of detecting whether we are in an absolute st or ld method
        if (!strncmp(instruction, "LD", 2) ||
            !strncmp(instruction, "ST", 2)) {
            printf("$%04X = %02X                  ",
                   address,
                   nes_read_memory(machine, address));
        } else { 
            printf("$%04X                       ", address);
        }
#endif
        break;
    case ABSOLUTE_X:
        address = nes_read_memory(machine, pc + 1) + x;
        page_crossed = pages_differ(address - x, address);
#ifdef DEBUG
        printf("$%04X                       ", address);
#endif
        break;
    case ABSOLUTE_Y:
        address = nes_read_memory(machine, pc + 1) + y;
#ifdef DEBUG
        printf("$%04X                       ", address);
#endif
        break;
    case INDIRECT:
        address = nes_read_memory(machine, pc + 1);
#ifdef DEBUG
        printf("$%04X                       ", address);
#endif
        break;
    case INDEXED_INDIRECT:
        if (offset + x == 0xff) {
            offset = offset & 0xff;
            address = (uint16_t)(nes_read_memory(machine, x) << 8) |
                (nes_read_memory(machine, offset + x));
        } else {
            address = (uint16_t)(nes_read_memory(machine, offset + x + 1) << 8) |
                (nes_read_memory(machine, offset + x));
        }
#ifdef DEBUG
        printf("($%02X,X) @ %02X = %04X = %02X    ",
                offset,
                0xff & offset + x,
                address,
                nes_read_memory(machine, address));
#endif
        break;
    case INDIRECT_INDEXED:
        address = nes_read_memory(machine, pc + 1) + y;
#ifdef DEBUG
        printf("$%04X                       ", address);
#endif
        break;
    }
    return address;
}

void nes_adc(struct nes_machine* machine) {
    uint8_t a = machine->cpu->a;
    uint8_t b = nes_read_memory(machine, nes_address(machine));
    uint8_t c = nes_get_carry(machine);
    uint16_t result = a + b + c;
    machine->cpu->a = (uint8_t) result;
    nes_set_zero(machine, (uint8_t) result);
    nes_set_negative(machine, (uint8_t) result);

    nes_set_overflow(machine, ((a ^ b) & 0x80) == 0 &&
                               ((result ^ a) & 0x80) != 0 );
    nes_set_carry(machine, result > 0xFF);

}
void nes_ahx(__attribute__((unused)) struct nes_machine* machine) {
    printf("Illegal opcode %s", __func__);
    exit(1);
}
void nes_alr(__attribute__((unused)) struct nes_machine* machine) {
    printf("Illegal opcode %s", __func__);
    exit(1);
}
void nes_anc(__attribute__((unused)) struct nes_machine* machine) {
    printf("Illegal opcode %s", __func__);
    exit(1);
}
void nes_and(struct nes_machine* machine) {
    uint16_t b = nes_address(machine);
    uint8_t value = machine->cpu->a & nes_read_memory(machine, b);
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
    machine->cpu->a = value;
}
void nes_arr(__attribute__((unused)) struct nes_machine* machine) {
    printf("Illegal opcode %s", __func__);
    exit(1);
}
void nes_asl(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    uint8_t old_value;
    uint8_t value;
    if (address == 0) {
        old_value = machine->cpu->a;
        value = old_value * 2;
        machine->cpu->a = value;
    } else {
        old_value = nes_read_memory(machine, address);
        value = old_value * 2;
        nes_write_memory(machine, address, value);
    }
    nes_set_carry(machine, old_value & (1 << 7));
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
}
void nes_axs(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_bcc(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    if (!nes_get_carry(machine)) {
        nes_abs_jump(machine, address);
        machine->cpu->cycles += 1 * CYCLE_MULT;
        machine->cpu->has_jumped = true;
    }
}
void nes_bcs(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    if (nes_get_carry(machine)) {
        nes_abs_jump(machine, address);
        machine->cpu->cycles += 1 * CYCLE_MULT;
        machine->cpu->has_jumped = true;
    }
}
void nes_beq(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    if (nes_get_zero(machine)) {
        nes_abs_jump(machine, address);
        machine->cpu->cycles += 1 * CYCLE_MULT;
        machine->cpu->has_jumped = true;
    }
}
void nes_bit(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    uint8_t value = nes_read_memory(machine, address);
    uint8_t result = value & machine->cpu->a;
    nes_set_zero(machine, result);
// Bits 7 and 6 of the value from memory are copied into the N and V flags.
    if ((value >> NES_OVERFLOW) & 1) {
        nes_set_overflow(machine, true);
    } else {
        nes_set_overflow(machine, false);
    }
    nes_set_negative(machine, value);
}
void nes_bmi(struct nes_machine* machine) {
    uint8_t address = (uint8_t) nes_address(machine);
    if (nes_get_negative(machine)) {
        nes_abs_jump(machine, address);
        machine->cpu->cycles += 1 * CYCLE_MULT;
        machine->cpu->has_jumped = true;
    }
}
void nes_bne(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    if (!nes_get_zero(machine)) {
        nes_abs_jump(machine, address);
        machine->cpu->cycles += 1 * CYCLE_MULT;
        machine->cpu->has_jumped = true;
    }
}
void nes_bpl(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    if (!nes_get_negative(machine)) {
        nes_abs_jump(machine, address);
        machine->cpu->cycles += 1 * CYCLE_MULT;
        machine->cpu->has_jumped = true;
    }
}
void nes_brk(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_bvc(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    if (!nes_get_overflow(machine)) {
        nes_abs_jump(machine, address);
        machine->cpu->cycles += 1 * CYCLE_MULT;
        machine->cpu->has_jumped = true;
    }
}
void nes_bvs(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    if (nes_get_overflow(machine)) {
        nes_abs_jump(machine, address);
        machine->cpu->cycles += 1 * CYCLE_MULT;
        machine->cpu->has_jumped = true;
    }
}
void nes_clc(struct nes_machine* machine) {
    nes_address(machine);
    nes_set_carry(machine, 0);
}
void nes_cld(struct nes_machine* machine) {
    nes_address(machine);
    nes_set_decimal_mode(machine, false);
}
void nes_cli(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_clv(struct nes_machine* machine) {
    nes_address(machine);
    nes_set_overflow(machine, false);
}
void nes_cmp(struct nes_machine* machine) {
    uint8_t m = nes_read_memory(machine, nes_address(machine));
    uint8_t a = machine->cpu->a;
    uint8_t value = a - m;
    nes_set_carry(machine, a >= m);
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
}
void nes_cpx(struct nes_machine* machine) {
    uint8_t m = nes_read_memory(machine, nes_address(machine));
    uint8_t a = machine->cpu->x;
    uint8_t value = a - m;
    nes_set_carry(machine, a >= m);
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
}
void nes_cpy(struct nes_machine* machine) {
    uint8_t m = nes_read_memory(machine, nes_address(machine));
    uint8_t a = machine->cpu->y;
    uint8_t value = a - m;
    nes_set_carry(machine, a >= m);
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
}
void nes_dcp(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_dec(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_dex(struct nes_machine* machine) {
    nes_address(machine);
    uint8_t value = machine->cpu->x - 1;
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
    machine->cpu->x = value;
}
void nes_dey(struct nes_machine* machine) {
    nes_address(machine);
    uint8_t value = machine->cpu->y - 1;
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
    machine->cpu->y = value;
}
void nes_eor(struct nes_machine* machine) {
    uint16_t b = nes_address(machine);
    uint8_t value = machine->cpu->a ^ nes_read_memory(machine, b);
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
    machine->cpu->a = value;
}
void nes_inc(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_inx(struct nes_machine* machine) {
    nes_address(machine);
    uint8_t value = machine->cpu->x + 1;
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
    machine->cpu->x = value;
}
void nes_iny(struct nes_machine* machine) {
    nes_address(machine);
    uint8_t value = machine->cpu->y + 1;
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
    machine->cpu->y = value;
}
void nes_isc(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_jmp(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    if (nes_addressing_modes[nes_opcode(machine)] == RELATIVE) {
        nes_rel_jump(machine, (uint8_t)address);
    } else {
        nes_abs_jump(machine, address);
    }
    machine->cpu->has_jumped = true;

}
void nes_jsr(struct nes_machine* machine) {
    uint16_t current_address = machine->cpu->pc + 2;
    uint16_t address = nes_address(machine);
    nes_stack_push(machine, (uint8_t) (current_address >> 8));
    nes_stack_push(machine, (uint8_t) current_address);
    nes_abs_jump(machine, address);
    machine->cpu->has_jumped = true;
    // XXX this is something endian so most significant address goes ?
    // XXX wat
}

void nes_kil(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_las(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_lax(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_lda(struct nes_machine* machine) {
    uint8_t value = nes_read_memory(machine, nes_address(machine));
    machine->cpu->a = value;
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
}
void nes_ldx(struct nes_machine* machine) {
    uint8_t value = nes_read_memory(machine, nes_address(machine));
    machine->cpu->x = value;
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
}
void nes_ldy(struct nes_machine* machine) {
    uint8_t value = nes_read_memory(machine, nes_address(machine));
    machine->cpu->y = value;
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
}
void nes_lsr(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    uint8_t old_value;
    uint8_t value;
    if (address == 0) {
        old_value = machine->cpu->a;
        value = old_value >> 1;
        machine->cpu->a = value;
    } else {
        old_value = nes_read_memory(machine, address);
        value = old_value >> 1;
        nes_write_memory(machine, address, value);
    }
    nes_set_carry(machine, old_value & 1);
    nes_set_negative(machine, value);
    nes_set_zero(machine, value);
}
void nes_nop(struct nes_machine* machine) {
    nes_address(machine);
}
void nes_ora(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    uint8_t m = nes_read_memory(machine, address);
    uint8_t value = machine->cpu->a | m;
    machine->cpu->a = value;
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
}

void nes_pha(struct nes_machine* machine) {
    nes_address(machine);
    uint8_t value = machine->cpu->a;
    nes_stack_push(machine, value);
}

void nes_php(struct nes_machine* machine) {
    nes_address(machine);
    uint8_t value = machine->cpu->p;
    // why :( why :( go this from 
    // https://github.com/fogleman/nes/blob/master/nes/cpu.go#L775
    nes_stack_push(machine, value | 0x10);
}
void nes_pla(struct nes_machine* machine) {
    // This makes no sense
    nes_address(machine);
    uint8_t value = nes_stack_pop(machine);
    nes_set_zero(machine, value);
    nes_set_negative(machine, value);
    machine->cpu->a = value;
}

void nes_plp(struct nes_machine* machine) {
    nes_address(machine);
    uint8_t value = nes_stack_pop(machine);
    // magic incantation of stack popping
    // total hack. i guess the status register is not a proper register
    machine->cpu->p = (value & 0xEF) | 0x20;
}

void nes_rla(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_rol(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    uint8_t old_value;
    uint8_t value;
    if (address == 0) {
        old_value = machine->cpu->a;
    } else {
        old_value = nes_read_memory(machine, address);
    }
    value = (uint8_t)(old_value << 1) | (uint8_t)(nes_get_carry(machine));
    if (address == 0) {
        machine->cpu->a = value;
    } else {
        nes_write_memory(machine, address, value);
    }
    nes_set_carry(machine, (old_value & 0x80));
    nes_set_negative(machine, value & (1 << NES_NEGATIVE) ? 0xff : 0);
    nes_set_zero(machine, !value ? 0 : 1);
}
void nes_ror(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    uint8_t old_value;
    uint8_t value;
    if (address == 0) {
        old_value = machine->cpu->a;
    } else {
        old_value = nes_read_memory(machine, address);
    }
    value = (uint8_t)(old_value >> 1) | (uint8_t)(nes_get_carry(machine) << 7);
    if (address == 0) {
        machine->cpu->a = value;
    } else {
        nes_write_memory(machine, address, value);
    }
    nes_set_carry(machine, old_value & 1);
    nes_set_negative(machine, value & (1 << NES_NEGATIVE) ? 0xff : 0);
    nes_set_zero(machine, value == 0 ? 0 : 1);
}
void nes_rra(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_rti(struct nes_machine* machine) {
    nes_address(machine);
    uint8_t value = nes_stack_pop(machine);
    // magic incantation of stack popping
    // total hack. i guess the status register is not a proper register
    machine->cpu->p = (value & 0xEF) | 0x20;
    machine->cpu->pc = (uint16_t) ((uint8_t) nes_stack_pop(machine) |
                                  ((uint8_t) nes_stack_pop(machine) << 8)) - 1;
}
void nes_rts(struct nes_machine* machine) {
    nes_address(machine);
    uint16_t new_pc = (uint16_t) ((uint8_t) nes_stack_pop(machine) |
                                  ((uint8_t) nes_stack_pop(machine) << 8)) + 1;
    nes_abs_jump(machine, new_pc);
    machine->cpu->has_jumped = true;
}
void nes_sax(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_sbc(struct nes_machine* machine) {
    uint8_t m = nes_read_memory(machine, nes_address(machine));
    uint8_t a = machine->cpu->a;
    uint8_t c = nes_get_carry(machine);
    uint16_t result = a - m - (1 - c);
    machine->cpu->a = (uint8_t) result;
    nes_set_zero(machine, (uint8_t) result);
    nes_set_negative(machine, (uint8_t) result);
    nes_set_overflow(machine, ((a ^ m) & 0x80) != 0 &&
                               ((a ^ result) & 0x80) != 0 );
    nes_set_carry(machine, a - m - (1 - c) >= 0);
}
void nes_sec(struct nes_machine* machine) {
    nes_address(machine);  // TODO not a clean way to decode/print addr
    nes_set_carry(machine, 1);
}
void nes_sed(struct nes_machine* machine) {
    nes_address(machine);
    nes_set_decimal_mode(machine, true);
}

void nes_sei(struct nes_machine* machine) {
    nes_address(machine);
    nes_set_interrupt_disable(machine, true);
}

void nes_shx(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_shy(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_slo(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_sre(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_sta(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    uint8_t value = machine->cpu->a;
    nes_write_memory(machine, address, value);
}
void nes_stx(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    nes_write_memory(machine, address, machine->cpu->x);
}
void nes_sty(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_tas(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
void nes_tax(struct nes_machine* machine) {
    nes_address(machine);
    machine->cpu->x = machine->cpu->a;
    nes_set_negative(machine, machine->cpu->x);
    nes_set_zero(machine, machine->cpu->x);
}
void nes_tay(struct nes_machine* machine) {
    nes_address(machine);
    machine->cpu->y = machine->cpu->a;
    nes_set_negative(machine, machine->cpu->y);
    nes_set_zero(machine, machine->cpu->y);
}
void nes_tsx(struct nes_machine* machine) {
    nes_address(machine);
    machine->cpu->x = machine->cpu->s;
    nes_set_negative(machine, machine->cpu->x);
    nes_set_zero(machine, machine->cpu->x);
}
void nes_txa(struct nes_machine* machine) {
    nes_address(machine);
    machine->cpu->a = machine->cpu->x;
    nes_set_negative(machine, machine->cpu->a);
    nes_set_zero(machine, machine->cpu->a);
}
void nes_txs(struct nes_machine* machine) {
    nes_address(machine);
    machine->cpu->s = machine->cpu->x;
}
void nes_tya(struct nes_machine* machine) {
    nes_address(machine);
    machine->cpu->a = machine->cpu->y;
    nes_set_negative(machine, machine->cpu->a);
    nes_set_zero(machine, machine->cpu->a);
}
void nes_xaa(__attribute__((unused)) struct nes_machine* machine) {
    printf("Opcode stub %s", __func__);
    exit(1);
}
