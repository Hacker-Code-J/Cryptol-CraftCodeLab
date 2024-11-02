CC = clang
CFLAGS = -Wall -Wextra -g -O1
LLVM_CC = clang
LLVM_CFLAGS = -g -O1 -c -emit-llvm -Iinclude

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

TARGET = $(BINDIR)/KISA_HIGHT_ECB
BC_FILES = KISA_HIGHT_ECB.bc
SAW_SCRIPT = KISA_HIGHT_VERIFY.saw
CRYPTOL_FILE = KISA_HIGHT_SPEC.cry

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: dir $(TARGET)

dir:
	@mkdir -p $(OBJDIR) $(BINDIR)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(BC_FILES)

rebuild: clean all

# Compile C code to LLVM bitcode
%.bc: $(SRCDIR)/%.c
	$(LLVM_CC) $(LLVM_CFLAGS) $< -o $@

# Run SAWScript
verify: $(BC_FILES) $(SAW_SCRIPT) $(CRYPTOL_FILE)
	saw $(SAW_SCRIPT)

.PHONY: all clean dir rebuild verify