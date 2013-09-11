#include <stdio.h>


void second_min(int *a, int size, int *min, int *min_s)
{
  if(size < 1)
  {
    return;
  }
  else if (size == 1) {
    *min = *min_s = a[0];
    return;
  }
  else if (size == 2) {
    if (a[0] < a[1]) {
      *min = a[0];
      *min_s = a[1];
    }
    else {
      *min = a[1];
      *min_s = a[0];
    }
    return;
  }

  int min1 = 0;
  int min2 = 0;
  int min_s1 = 0;
  int min_s2 = 0;
  int mid = size/2;
  second_min(a, mid, &min1, &min_s1);
  second_min(a+mid, size-mid, &min2, &min_s2);
  if (min1 < min2) {
    *min = min1;
    if (min2 < min_s1) {
      *min_s = min2;
    }
    else
    {
      *min_s = min_s1;
    }
  }
  else if (min1 > min2) {
    *min = min2;
    if (min1 < min_s2) {
      *min_s = min1;
    }
    else {
      *min_s = min_s2;
    }
  }
  else { // min1 == min2
    *min = min1;
    if (min_s1 < min_s2) {
      *min_s = min_s1;
    }
    else {
      *min_s = min_s2;
    }
  }
}


int main()
{
  int a[] = {24, 12, 1, 2, 15, 5, 6, 13, 11, 8, 17, 19, 9, 7, 16};
  int min, min_s;
  second_min(a, sizeof(a)/sizeof(int), &min, &min_s);
  printf("%d, %d\n", min, min_s);
  return 0;
}
