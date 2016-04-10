mod cpu;
struct NES {
    cpu: cpu::CPU,
    memory: memory::Memory,
}

fn initialize_nes() -> NES {
    return NES {
        cpu: cpu::initialize_cpu(),
        memory: memory::initialize_memory(),
    }
}

fn step(&mut nes: NES) {
    nes.cpu.pc += 1;
}
