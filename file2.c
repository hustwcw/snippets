#include "file1.h"

extern int g;

int main()
{
  fun();
  g++;
  fun();
  g++;
  fun();
}
