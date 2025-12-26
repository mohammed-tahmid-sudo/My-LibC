#include <stdio.h>

long syscall(long number, long arg1, long arg2, long arg3) {
  long ret;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(number), "D"(arg1), "S"(arg2), "d"(arg3)
                   : "rcx", "r11", "memory");
  return ret;
}

long write(long fd, const char *buf, long count) {
  long ret;
  syscall(1, fd, (long)buf, count);
  return ret;
}

int main() {
  int a = "123" - 48;
  printf("%d\n", a);

  return 0;
}
