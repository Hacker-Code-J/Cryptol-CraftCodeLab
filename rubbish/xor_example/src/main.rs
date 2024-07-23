fn main() {
    let byte1: u8 = 0xAB; // Example byte 1
    let byte2: u8 = 0x4F; // Example byte 2
    let result = byte1 ^ byte2; // Perform XOR operation

    println!("Result: {:X}", result); // Print the result in hexadecimal
}