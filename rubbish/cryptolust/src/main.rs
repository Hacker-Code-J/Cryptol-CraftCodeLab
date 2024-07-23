// Defining the XOR function according to the Cryptol specification
fn xor(a: bool, b: bool) -> bool {
    (a || b) && !(a && b)
}

#[cfg(test)]
mod tests {
    use super::*;

    // Testing the XOR function with various inputs
    #[test]
    fn test_xor() {
        assert_eq!(xor(false, false), false);
        assert_eq!(xor(false, true), true);
        assert_eq!(xor(true, false), true);
        assert_eq!(xor(true, true), false);
    }

    // Verifying the property: XOR is its own inverse
    #[test]
    fn test_xor_inverse() {
        for a in [false, true] {
            for b in [false, true] {
                assert_eq!(xor(xor(a, b), b), a);
            }
        }
    }
}