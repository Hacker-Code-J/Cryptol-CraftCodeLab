BINARY_NAME=arithmetic_unit_tests
CC=clang

all: $(BINARY_NAME)

$(BINARY_NAME): arithmetic.c
	$(CC) -o $(BINARY_NAME) arithmetic.c

arithmetic_llvm.bc: arithmetic.c
	$(CC) -g -c -emit-llvm -o arithmetic_llvm.bc arithmetic.c

add_tests: arithmetic_llvm.bc
	saw add_llvm.saw

multiply_tests: arithmetic_llvm.bc
	saw multiply_llvm.saw

clean:
	rm -f *.bc $(BINARY_NAME) *~