// src/lib.rs
pub fn xor(a: bool, b: bool) -> bool {
    (a || b) && !(a && b)
}
