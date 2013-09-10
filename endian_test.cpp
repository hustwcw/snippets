#include <stdio.h>

int main()
{
  int *p1 = new int[10];
  int *p2 = new int[10]();
  int a = 0x12345678;
  int *p = &a;
  printf("%x:%x:%x:%x\n", char(*(char *)(p)), char(*((char *)p+1)), char(*((char *)p+2)), char(*((char *)p+3)));

  return 0;
}
