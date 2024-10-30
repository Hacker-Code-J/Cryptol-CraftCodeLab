# # Compiler
# CC = clang

# # Compiler flags
# CFLAGS = -Wall -O2 -Iinclude

# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99 -g -O1 -I./include
LDFLAGS =
LLVM_CC = clang
LLVM_CFLAGS = -g -O1 -c -emit-llvm -I$(INCDIR)

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Target executable
TARGET = $(BINDIR)/hight_ecb
BC_FILES = KISA_HIGHT_ECB.bc
SAW_SCRIPT = HIGHT-KISA-VERIF.saw
CRYPTOL_FILE = HIGHT-KISA.cry

# Source and object files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Default rule: build the executable
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create bin and obj directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean rule to remove the compiled files
clean:
	rm -rf $(OBJDIR) $(BINDIR) *.bc

# Rebuild rule: clean and build again
rebuild: clean all

# Run rule: build and run the program
run: $(TARGET)
	./$(TARGET)

# Compile C code to LLVM bitcode
%.bc: $(SRCDIR)/%.c
	$(LLVM_CC) $(LLVM_CFLAGS) $< -o $@

# Run SAWScript
verify: $(BC_FILES) $(SAW_SCRIPT) $(CRYPTOL_FILE)
	saw $(SAW_SCRIPT)

# Phony targets to prevent conflicts with file names
.PHONY: all clean rebuild run
