// RUN: clang-format -style=LLVM -i -n %s 2> %t.stderr
// RUN: grep -E "*code should be clang-formatted*" %t.stderr

int a ;
