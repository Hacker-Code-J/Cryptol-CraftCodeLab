CC = clang
CFLAGS = -Wall -Wextra -g -O1
LLVM_CFLAGS = -g -O1 -fno-threadsafe-statics -fsanitize-trap=undefined -emit-llvm -c

TARGET = KISA_HIGHT_ECB
SRC = KISA_HIGHT_ECB.c
HEADERS = KISA_HIGHT_ECB.h

# Default target
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
# Clean up build files
clean:
	rm -f $(TARGET) *.o *.bc

rebuild: clean all

run: 
	./$(TARGET)

%.bc: $(SRC)
	$(CC) $(LLVM_CFLAGS) $< -o $@

BC_FILES = KISA_HIGHT_ECB.bc
SAW_SCRIPT = KISA_HIGHT_VERIFY.saw
CRYPTOL_FILE = KISA_HIGHT_SPEC.cry
verify: $(BC_FILES) $(SAW_SCRIPT) $(CRYPTOL_FILE)
	saw $(SAW_SCRIPT)

# Phony targets to prevent conflicts with file names
.PHONY: all clean rebuild run
