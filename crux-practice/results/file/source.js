var sources = [
{"label":"file.c","name":"/home/hacker-code-j/Desktop/Cryptol-CraftCodeLab/crux-practice/file.c","lines":["#include <stdint.h>","#ifdef CRUCIBLE","#include <crucible.h>","#endif","","int8_t f(int8_t x) {","  return x + 1;","}","#ifdef CRUCIBLE","","int main() {","  int8_t x = crucible_int8_t(\"x\");","  assuming(x < 2 ^ 1024);","  check(f(x) < 2 ^ 1024);","  return 0;","}","#else","","int main(int argc, char **argv) {","  return f(argc);","}","#endif"]},
]
