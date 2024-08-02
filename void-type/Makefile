.SUFFIXES: .c .bc
.PHONY: all

C_FILES = $(shell find .. -name '*.c')
BC_FILES = $(%.c, %.bc, $(C_FILES))
# BC_FILES = $(patsubst %.c, %.bc, $(C_FILES))

all: $(BC_FILES)

%.bc : %.c
	clang -g -O0 -c -emit-llvm $< -o $@

clean:
	rm -rf *.bc

rebuild: clean all
