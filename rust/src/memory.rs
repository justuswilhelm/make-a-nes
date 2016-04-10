struct Memory {
    content: [u8; 0x10000],
}


fn initialize_memory() -> Memory {
    return Memory {
        content: [0; 0x10000]
    }
}
