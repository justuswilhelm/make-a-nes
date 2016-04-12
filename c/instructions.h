#include "nes.h"

#include <stdbool.h>
enum nes_flags {
    NES_CARRY = 0,
};

enum nes_addressing_mode {
    IMPLICIT,
    ACCUMULATOR,
    IMMEDIATE,
    ZERO_PAGE,
    ZERO_PAGE_X,
    ZERO_PAGE_Y,
    RELATIVE,
    ABSOLUTE,
    ABSOLUTE_X,
    ABSOLUTE_Y,
    INDIRECT,
    INDEXED_INDIRECT,
    INDIRECT_INDEXED,
};

// instruction information
extern void (*instructions[0x100])(struct nes_machine*);
extern enum nes_addressing_mode nes_addressing_modes[0x100];
extern char nes_instruction_names[0x100][4];
extern uint8_t nes_instruction_sizes[0x100];

void nes_set_carry(struct nes_machine* machine, bool value);
bool nes_get_carry(struct nes_machine* machine);
void nes_rel_jump(struct nes_machine* machine, uint8_t offset);
void nes_abs_jump(struct nes_machine* machine, uint16_t address);

uint8_t nes_opcode(struct nes_machine* machine);
uint8_t nes_instruction_size(struct nes_machine* machine);

uint16_t nes_address(struct nes_machine* machine);
uint8_t nes_read_memory(struct nes_machine* machine, uint16_t address);
void nes_write_memory(struct nes_machine* machine, uint16_t address, uint8_t value);
bool pages_differ(uint16_t a, uint16_t b);

void nes_print_cpu_state(struct nes_machine* machine);

void nes_adc(struct nes_machine* machine);
void nes_ahx(struct nes_machine* machine);
void nes_alr(struct nes_machine* machine);
void nes_anc(struct nes_machine* machine);
void nes_and(struct nes_machine* machine);
void nes_arr(struct nes_machine* machine);
void nes_asl(struct nes_machine* machine);
void nes_axs(struct nes_machine* machine);
void nes_bcc(struct nes_machine* machine);
void nes_bcs(struct nes_machine* machine);
void nes_beq(struct nes_machine* machine);
void nes_bit(struct nes_machine* machine);
void nes_bmi(struct nes_machine* machine);
void nes_bne(struct nes_machine* machine);
void nes_bpl(struct nes_machine* machine);
void nes_brk(struct nes_machine* machine);
void nes_bvc(struct nes_machine* machine);
void nes_bvs(struct nes_machine* machine);
void nes_clc(struct nes_machine* machine);
void nes_cld(struct nes_machine* machine);
void nes_cli(struct nes_machine* machine);
void nes_clv(struct nes_machine* machine);
void nes_cmp(struct nes_machine* machine);
void nes_cpx(struct nes_machine* machine);
void nes_cpy(struct nes_machine* machine);
void nes_dcp(struct nes_machine* machine);
void nes_dec(struct nes_machine* machine);
void nes_dex(struct nes_machine* machine);
void nes_dey(struct nes_machine* machine);
void nes_eor(struct nes_machine* machine);
void nes_inc(struct nes_machine* machine);
void nes_inx(struct nes_machine* machine);
void nes_iny(struct nes_machine* machine);
void nes_isc(struct nes_machine* machine);
void nes_jmp(struct nes_machine* machine);
void nes_jsr(struct nes_machine* machine);
void nes_kil(struct nes_machine* machine);
void nes_las(struct nes_machine* machine);
void nes_lax(struct nes_machine* machine);
void nes_lda(struct nes_machine* machine);
void nes_ldx(struct nes_machine* machine);
void nes_ldy(struct nes_machine* machine);
void nes_lsr(struct nes_machine* machine);
void nes_nop(struct nes_machine* machine);
void nes_ora(struct nes_machine* machine);
void nes_pha(struct nes_machine* machine);
void nes_php(struct nes_machine* machine);
void nes_pla(struct nes_machine* machine);
void nes_plp(struct nes_machine* machine);
void nes_rla(struct nes_machine* machine);
void nes_rol(struct nes_machine* machine);
void nes_ror(struct nes_machine* machine);
void nes_rra(struct nes_machine* machine);
void nes_rti(struct nes_machine* machine);
void nes_rts(struct nes_machine* machine);
void nes_sax(struct nes_machine* machine);
void nes_sbc(struct nes_machine* machine);
void nes_sec(struct nes_machine* machine);
void nes_sed(struct nes_machine* machine);
void nes_sei(struct nes_machine* machine);
void nes_shx(struct nes_machine* machine);
void nes_shy(struct nes_machine* machine);
void nes_slo(struct nes_machine* machine);
void nes_sre(struct nes_machine* machine);
void nes_sta(struct nes_machine* machine);
void nes_stx(struct nes_machine* machine);
void nes_sty(struct nes_machine* machine);
void nes_tas(struct nes_machine* machine);
void nes_tax(struct nes_machine* machine);
void nes_tay(struct nes_machine* machine);
void nes_tsx(struct nes_machine* machine);
void nes_txa(struct nes_machine* machine);
void nes_txs(struct nes_machine* machine);
void nes_tya(struct nes_machine* machine);
void nes_xaa(struct nes_machine* machine);
