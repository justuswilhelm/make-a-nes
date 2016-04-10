extern crate rand;

use std::io::{self, Write};
mod nes;


fn main() {
    let mut nes = nes::initialize_nes();
    loop {
        let mut prompt = String::new();
        print!("> ");
        io::stdout().flush().unwrap();
        io::stdin().read_line(&mut prompt)
            .expect("Failed to read line");
        match prompt.trim().as_ref() {
            "state" => {
                println!("CPU");
                println!("{}", nes.cpu);
                println!("Memory");
                println!("PC: 0x{:02x}",
                         nes.memory.content[nes.cpu.pc as usize]);
            },
            "step" => nes::step(&mut nes.cpu, &mut nes.memory),
            "quit" => {
                println!("Good bye!");
                break;
            },
            _ => println!("\nUnknown command!"),
        }
    }
}
