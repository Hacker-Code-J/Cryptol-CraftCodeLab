BINARY_NAME=arx
CC=clang

all: $(BINARY_NAME)

$(BINARY_NAME): ARX.c
	$(CC) -o $(BINARY_NAME) ARX.c

arx_llvm.bc: ARX.c
	$(CC) -g -c -emit-llvm -o ARX_llvm.bc ARX.c

add_tests: ARX_llvm.bc
	saw ARX_llvm.saw

# multiply_tests: arithmetic_llvm.bc
# 	saw multiply_llvm.saw

clean:
	rm -f *.bc $(BINARY_NAME) *~