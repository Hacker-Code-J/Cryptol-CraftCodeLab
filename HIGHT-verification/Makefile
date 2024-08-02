# Compiler and flags
CC = clang
CFLAGS = -Iinclude -emit-llvm -c

# Source files and bitcode files
SRC_DIR = src
OBJ_DIR = build
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
BC_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.bc, $(SRC_FILES))

# Output bitcode file
OUT_BC = $(OBJ_DIR)/test_hight_combined.bc

# SAW script and Cryptol file
SAW_SCRIPT = verify.saw
CRYPTOL_FILE = HIGHT.cry

# Default target
all: verify

# Create the build directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile each .c file to .bc
$(OBJ_DIR)/%.bc: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Link all .bc files into one combined .bc file
$(OUT_BC): $(BC_FILES)
	llvm-link $(BC_FILES) -o $(OUT_BC)

# Run SAW-script for verification
verify: $(OUT_BC) $(SAW_SCRIPT) $(CRYPTOL_FILE)
	saw $(SAW_SCRIPT)

# Clean build files
clean:
	rm -rf $(OBJ_DIR)

.PHONY: all verify clean
