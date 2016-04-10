struct CPU {
    a: u8,
    x: u8,
    y: u8,
    pc: u16,
    s: u8,
    p: u8,
}


impl std::fmt::Display for CPU {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "Registers
a: \t0x{:02x},
x: \t0x{:02x},
y: \t0x{:02x},
pc: \t0x{:04x},
s: \t0x{:02x},
p: \t0x{:02x}", self.a, self.x, self.y, self.pc, self.s, self.p)
    }
}

fn initialize_cpu() -> CPU {
    // http://wiki.nesdev.com/w/index.php/CPU_power_up_state
    CPU{
        a: 0,
        x: 0,
        y: 0,
        pc: 0,
        s: 0xFD,
        p: 0x34,
    }
}
