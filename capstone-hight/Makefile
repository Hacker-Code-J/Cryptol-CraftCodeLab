BINARY_NAME=arx
# BINARY_NAME=hight
CC=clang

all: $(BINARY_NAME)

$(BINARY_NAME): ARX.c
	$(CC) -o $(BINARY_NAME) ARX.c

# $(BINARY_NAME): hight.c
# 	$(CC) -o $(BINARY_NAME) hight.c

arx_llvm.bc: ARX.c
	$(CC) -g -c -emit-llvm -o ARX_llvm.bc ARX.c

# hight_llvm.bc: hight.c
# 	$(CC) -g -c -emit-llvm -o hight_llvm.bc hight.c

arx_tests: ARX_llvm.bc
	saw ARX_llvm.saw

# multiply_tests: arithmetic_llvm.bc
# 	saw multiply_llvm.saw

clean:
	rm -f *.bc $(BINARY_NAME) *~