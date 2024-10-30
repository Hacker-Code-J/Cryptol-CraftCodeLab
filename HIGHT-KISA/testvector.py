# List of decimal values
rk = [2,
75,
0,
164,
98,
0,
120,
0,
178,
129,
89,
162,
43,
152,
6,
66,
196,
34,
178,
179,
144,
19,
109,
136,
14,
76,
229,
238,
71,
177,
70,
52,
238,
189,
51,
124,
214,
180,
254,
230,
76,
95,
92,
185,
133,
245,
255,
175,
184,
120,
231,
158,
109,
54,
241,
135,
229,
30,
82,
248,
193,
10,
215,
155,
147,
35,
34,
51,
99,
132,
64,
238,
124,
16,
15,
188,
247,
100,
135,
122,
199,
28,
148,
107,
58,
116,
141,
147,
119,
216,
79,
190,
196,
226,
73,
180,
220,
158,
145,
192,
176,
116,
128,
47,
26,
158,
162,
32,
138,
249,
202,
59,
27,
2,
249,
44,
235,
255,
132,
15,
184,
252,
117,
127,
55,
124,
164,
108,
163,
131,
91,
233,
111,
123,
144,
88]

src = [0, 48, 136, 129, 32, 6, 168, 197]
dst = [0, 0, 0, 0, 0, 0, 0, 0]
# Convert decimal values to hexadecimal
hex_rk = [hex(val)[2:].upper().zfill(2) for val in rk]
hex_src = [hex(val)[2:].upper().zfill(2) for val in src]

# Print as C-style array
print("KISA_RK = {")
for i in range(0, len(hex_rk), 8):
    print("  " + ", ".join(f"0x{hex_rk[j]}" for j in range(i, min(i + 8, len(hex_rk)))) + ",")
print("};")

print("KISA_SRC = {")
for i in range(0, len(hex_src), 8):
    print("  " + ", ".join(f"0x{hex_src[j]}" for j in range(i, min(i + 8, len(hex_src)))) + ",")
print("};")

# Placeholder delta table (should be replaced with the actual table used)
delta_table = [
    0x5A,0x6D,0x36,0x1B,0x0D,0x06,0x03,0x41,
    0x60,0x30,0x18,0x4C,0x66,0x33,0x59,0x2C,
    0x56,0x2B,0x15,0x4A,0x65,0x72,0x39,0x1C,
    0x4E,0x67,0x73,0x79,0x3C,0x5E,0x6F,0x37,
    0x5B,0x2D,0x16,0x0B,0x05,0x42,0x21,0x50,
    0x28,0x54,0x2A,0x55,0x6A,0x75,0x7A,0x7D,
    0x3E,0x5F,0x2F,0x17,0x4B,0x25,0x52,0x29,
    0x14,0x0A,0x45,0x62,0x31,0x58,0x6C,0x76,
    0x3B,0x1D,0x0E,0x47,0x63,0x71,0x78,0x7C,
    0x7E,0x7F,0x3F,0x1F,0x0F,0x07,0x43,0x61,
    0x70,0x38,0x5C,0x6E,0x77,0x7B,0x3D,0x1E,
    0x4F,0x27,0x53,0x69,0x34,0x1A,0x4D,0x26,
    0x13,0x49,0x24,0x12,0x09,0x04,0x02,0x01,
    0x40,0x20,0x10,0x08,0x44,0x22,0x11,0x48,
    0x64,0x32,0x19,0x0C,0x46,0x23,0x51,0x68,
    0x74,0x3A,0x5D,0x2E,0x57,0x6B,0x35,0x5A
];

def encKeySchedule(enc_WK, enc_SK, MK, delta_table):
    # Generate whitening keys
    enc_WK[0] = MK[12]
    enc_WK[1] = MK[13]
    enc_WK[2] = MK[14]
    enc_WK[3] = MK[15]
    enc_WK[4] = MK[0]
    enc_WK[5] = MK[1]
    enc_WK[6] = MK[2]
    enc_WK[7] = MK[3]

    # Generate subkeys
    for i in range(8):
        for j in range(8):
            enc_SK[16 * i + j + 0] = ((MK[((j - i) & 7) + 0] + delta_table[16 * i + j + 0])) & 0xFF
        for j in range(8):
            enc_SK[16 * i + j + 8] = ((MK[((j - i) & 7) + 8] + delta_table[16 * i + j + 8])) & 0xFF

# MK = [ 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
#        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 ]
MK = [ 0x62, 0x00, 0x78, 0x00, 0x73, 0xF1, 0x59, 0x53,
  0xFE, 0x2F, 0x49, 0xFE, 0x02, 0x4B, 0x00, 0xA4 ]
WK = [0] * 8             # Whitening key array
SK = [0] * 128           # Subkey array

encKeySchedule(WK, SK, MK, delta_table)
hex_WK = [hex(val)[2:].upper().zfill(2) for val in WK]
hex_SK = [hex(val)[2:].upper().zfill(2) for val in SK]

print("WK = {")
for i in range(0, len(hex_WK), 8):
    print("  " + ", ".join(f"0x{hex_WK[j]}" for j in range(i, min(i + 8, len(hex_WK)))) + ",")
print("};")
print("SK = {")
for i in range(0, len(hex_SK), 8):
    print("  " + ", ".join(f"0x{hex_SK[j]}" for j in range(i, min(i + 8, len(hex_SK)))) + ",")
print("};")

def findMK(enc_WK, enc_SK, delta_table):
    """
    Reconstructs the master key MK from whitening keys (enc_WK), subkeys (enc_SK), and delta_table.

    enc_WK: Array of 8 bytes for whitening keys.
    enc_SK: Array of 128 bytes for subkeys.
    delta_table: Array of 128 bytes (delta values).
    
    Returns:
        MK: Reconstructed master key (16 bytes).
    """
    MK = [0] * 16  # Initialize an array for the master key (16 bytes)

    # Step 1: Recover MK[0:4] and MK[12:16] from whitening keys (enc_WK)
    MK[0:4] = enc_WK[4:8]
    MK[12:16] = enc_WK[0:4]

    # Step 2: Recover MK[4:12] using subkeys and delta_table
    # We already know MK[0:4] and MK[12:16], so we only need to recover MK[4:12].
    
    # For i in range(8), reconstruct MK[((j - i) & 7) + offset] from enc_SK
    for i in range(8):
        for j in range(8):
            # Subkeys for indices 0-7, reconstructing MK[0:8] (first half)
            mk_index = ((j - i) & 7) + 0
            if mk_index >= 4:  # We only need MK[4:8]
                enc_sk_value = enc_SK[16 * i + j + 0]
                delta_value = delta_table[16 * i + j + 0]
                MK[mk_index] = (enc_sk_value - delta_value) & 0xFF

            # Subkeys for indices 8-15, reconstructing MK[8:16] (second half)
            mk_index = ((j - i) & 7) + 8
            if mk_index < 12:  # We only need MK[8:12]
                enc_sk_value = enc_SK[16 * i + j + 8]
                delta_value = delta_table[16 * i + j + 8]
                MK[mk_index] = (enc_sk_value - delta_value) & 0xFF

    return MK

# Example usage for reverse-engineering MK:
re_MK = findMK(WK, SK, delta_table)
hex_MK = [hex(val)[2:].upper().zfill(2) for val in re_MK]
print("MK = {")
for i in range(0, len(hex_MK), 8):
    print("  " + ", ".join(f"0x{hex_MK[j]}" for j in range(i, min(i + 8, len(hex_MK)))) + ",")
print("};")

KISA_WK = [
    0x02, 0x4B, 0x00, 0xA4, 0x62, 0x00, 0x78, 0x00
]

KISA_SK = [
    0xB2, 0x81, 0x59, 0xA2, 0x2B, 0x98, 0x06, 0x42,
    0xC4, 0x22, 0xB2, 0xB3, 0x90, 0x13, 0x6D, 0x88,
    0x0E, 0x4C, 0xE5, 0xEE, 0x47, 0xB1, 0x46, 0x34,
    0xEE, 0xBD, 0x33, 0x7C, 0xD6, 0xB4, 0xFE, 0xE6,
    0x4C, 0x5F, 0x5C, 0xB9, 0x85, 0xF5, 0xFF, 0xAF,
    0xB8, 0x78, 0xE7, 0x9E, 0x6D, 0x36, 0xF1, 0x87,
    0xE5, 0x1E, 0x52, 0xF8, 0xC1, 0x0A, 0xD7, 0x9B,
    0x93, 0x23, 0x22, 0x33, 0x63, 0x84, 0x40, 0xEE,
    0x7C, 0x10, 0x0F, 0xBC, 0xF7, 0x64, 0x87, 0x7A,
    0xC7, 0x1C, 0x94, 0x6B, 0x3A, 0x74, 0x8D, 0x93,
    0x77, 0xD8, 0x4F, 0xBE, 0xC4, 0xE2, 0x49, 0xB4,
    0xDC, 0x9E, 0x91, 0xC0, 0xB0, 0x74, 0x80, 0x2F,
    0x1A, 0x9E, 0xA2, 0x20, 0x8A, 0xF9, 0xCA, 0x3B,
    0x1B, 0x02, 0xF9, 0x2C, 0xEB, 0xFF, 0x84, 0x0F,
    0xB8, 0xFC, 0x75, 0x7F, 0x37, 0x7C, 0xA4, 0x6C,
    0xA3, 0x83, 0x5B, 0xE9, 0x6F, 0x7B, 0x90, 0x58
]

KISA_MK = findMK(KISA_WK, KISA_SK, delta_table)
hex_KISA_MK = [hex(val)[2:].upper().zfill(2) for val in KISA_MK]
print("KISA_MK = {")
for i in range(0, len(hex_KISA_MK), 8):
    print("  " + ", ".join(f"0x{hex_KISA_MK[j]}" for j in range(i, min(i + 8, len(hex_KISA_MK)))) + ",")
print("};")