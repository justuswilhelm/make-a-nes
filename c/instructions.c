#include "instructions.h"

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

void nes_set_carry(struct nes_machine* machine, bool value) {
    machine->cpu->s ^= (-value ^ NES_CARRY) & (1 << NES_CARRY);
}

bool nes_get_carry(__attribute__((unused)) struct nes_machine* machine) {
    return false;
}

void nes_rel_jump(struct nes_machine* machine, uint8_t offset) {
    machine->cpu->pc += offset;
}

void nes_abs_jump(struct nes_machine* machine, uint16_t address) {
    machine->cpu->pc = address;
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
    *(machine->memory[address]) = value;
}

bool pages_differ(uint16_t a, uint16_t b) {
    return (a & 0xFF00) != (b & 0xFF00);
}

void nes_print_cpu_state(struct nes_machine* machine) {
    printf("%04X  ", machine->cpu->pc);
    uint8_t opcode = nes_opcode(machine);
    uint8_t instruction_size = nes_instruction_size(machine);
    char* instruction = nes_instruction_names[opcode];

    for (uint16_t i = 0; i < instruction_size; i++) {
        printf("%02X ", nes_read_memory(machine, machine->cpu->pc + i));
    }
    for (int i = 0; i < 3 - instruction_size; i++) {
        printf("   ");
    }

    printf(" %s ", instruction);
    printf("A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%3d SL:%3d\n",
           machine->cpu->a,
           machine->cpu->x,
           machine->cpu->y,
           machine->cpu->p,
           machine->cpu->s,
           0,
           0);
}

uint16_t nes_address(struct nes_machine* machine) {
    uint8_t x = machine->cpu->x;
    uint8_t y = machine->cpu->y;
    uint16_t pc = machine->cpu->pc;
    uint8_t opcode = nes_opcode(machine);
    enum nes_addressing_mode mode = nes_addressing_modes[opcode];
    uint16_t offset = nes_read_memory(machine, pc + 1);

    uint16_t address = 0;
    bool page_crossed;
    switch (mode) {
    case IMPLICIT:
        address =  0;
        break;
    case ACCUMULATOR:
        address = 0;
        break;
    case IMMEDIATE:
        address = pc + 1;
        break;
    case ZERO_PAGE:
        address = nes_read_memory(machine, pc + 1);
        break;
    case ZERO_PAGE_X:
        address = nes_read_memory(machine, pc + x);
        break;
    case ZERO_PAGE_Y:
        address = nes_read_memory(machine, pc + y);
    case RELATIVE:
        if (offset < 0x80) {
            address = pc + 2 + offset;
        } else {
            address = pc + 2 + offset - 0x100;
        }
        break;
    case ABSOLUTE:
        address = (uint16_t) (nes_read_memory(machine, pc + 1) +
            (nes_read_memory(machine, pc + 2) << 8));
        break;
    case ABSOLUTE_X:
        address = nes_read_memory(machine, pc + 1) + x;
        page_crossed = pages_differ(address - x, address);
        break;
    case ABSOLUTE_Y:
        address = nes_read_memory(machine, pc + 1) + y;
        break;
    case INDIRECT:
        address = nes_read_memory(machine, pc + 1);
        break;
    case INDEXED_INDIRECT:
        address = nes_read_memory(machine, nes_read_memory(machine, pc + 1) + x);
        break;
    case INDIRECT_INDEXED:
        address = nes_read_memory(machine, pc + 1) + y;
        break;
    }
    return address;
}

void nes_adc(struct nes_machine* machine) {
    uint8_t a = machine->cpu->a;
    uint8_t b = nes_read_memory(machine, nes_address(machine));
    uint8_t c = nes_get_carry(machine);
    machine->cpu->a = a + b + c;
}
void nes_ahx(__attribute__((unused)) struct nes_machine* machine) {
    // Illegal opcode
}
void nes_alr(__attribute__((unused)) struct nes_machine* machine) {
    // Illegal opcode
}
void nes_anc(__attribute__((unused)) struct nes_machine* machine) {
    // Illegal opcode
}
void nes_and(struct nes_machine* machine) {
    uint16_t b = nes_address(machine);
    machine->cpu->a = machine->cpu->a & nes_read_memory(machine, b);
}
void nes_arr(__attribute__((unused)) struct nes_machine* machine) {
    // Illegal opcode
}
void nes_asl(struct nes_machine* machine) {
    uint8_t opcode = nes_opcode(machine);
    struct nes_cpu* cpu = machine->cpu;
    enum nes_addressing_mode mode = nes_addressing_modes[opcode];
    if (mode == ACCUMULATOR) {
        nes_set_carry(machine, (cpu->a >> 7) & 1);
        cpu->a <<= 1;
        // TODO set zn flags
    } else {
        uint16_t address = nes_address(machine);
        uint8_t value = nes_read_memory(machine, address);
        nes_set_carry(machine, (value >> 7) & 1);
        value <<= 1;
        nes_write_memory(machine, address, value);
        // TODO set zn flags
    }
}
void nes_axs(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_bcc(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_bcs(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_beq(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_bit(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_bmi(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_bne(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_bpl(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_brk(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_bvc(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_bvs(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_clc(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_cld(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_cli(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_clv(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_cmp(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_cpx(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_cpy(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_dcp(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_dec(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_dex(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_dey(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_eor(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_inc(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_inx(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_iny(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_isc(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_jmp(struct nes_machine* machine) {
    uint16_t address = nes_address(machine);
    printf("Jumping to %04X\n", address);
    if (nes_addressing_modes[nes_opcode(machine)] == RELATIVE) {
        nes_rel_jump(machine, (uint8_t)address);
    } else {
        nes_abs_jump(machine, address);
    }

}
void nes_jsr(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_kil(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_las(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_lax(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_lda(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_ldx(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_ldy(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_lsr(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_nop(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_ora(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_pha(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_php(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_pla(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_plp(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_rla(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_rol(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_ror(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_rra(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_rti(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_rts(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_sax(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_sbc(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_sec(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_sed(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_sei(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_shx(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_shy(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_slo(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_sre(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_sta(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_stx(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_sty(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_tas(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_tax(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_tay(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_tsx(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_txa(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_txs(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_tya(__attribute__((unused)) struct nes_machine* machine) {
}
void nes_xaa(__attribute__((unused)) struct nes_machine* machine) {
}
