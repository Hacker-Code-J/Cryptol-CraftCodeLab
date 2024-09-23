# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99 -g -O2 -I./include
LDFLAGS =
LLVM_CC = clang
LLVM_CFLAGS = -c -emit-llvm -I$(INCDIR)

# Directories
OBJDIR = ./obj
BINDIR = ./bin
SRCDIR = ./src
TESTDIR = ./tests
INCDIR = ./include

# Files
OBJS = $(OBJDIR)/hight_core.o $(OBJDIR)/hight_utils.o \
	$(OBJDIR)/main.o

TARGET = $(BINDIR)/hight
BC_FILES = hight_core.bc # $(TESTDIR)/hight_utils.bc $(TESTDIR)/main.bc
SAW_SCRIPT = HIGHT-VERIF.saw
CRYPTOL_FILE = HIGHT.cry

.PHONY: all clean dir rebuild verify

all: dir $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d)

run:
	(cd bin && ./hight)

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(BC_FILES)

dir:
	@mkdir -p $(OBJDIR) $(BINDIR)

rebuild: clean all

# Compile C code to LLVM bitcode
%.bc: $(SRCDIR)/%.c
	$(LLVM_CC) $(LLVM_CFLAGS) $< -o $@

# Run SAWScript
verify: $(BC_FILES) $(SAW_SCRIPT) $(CRYPTOL_FILE)
	saw $(SAW_SCRIPT)
