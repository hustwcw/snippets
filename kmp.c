#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void compute_prefix(unsigned char *pi, const char *pattern)
{
int i = 0;
int m = strlen(pattern);
int k = 0;
pi[0] = 0;
for(i = 1; i < m; i++)
{
  while(k > 0 && pattern[k] != pattern[i])
  {
    k = pi[k-1];
  }
  if(pattern[k] == pattern[i])
  {
    k++;
  }
  pi[i] = k;
}
for(i = 0; i < m; i++)
{
  printf("%d\t", pi[i]);
}
printf("\n");
}


void kmp_match(const char *text, const char *pattern)
{
int n = strlen(text);
int m = strlen(pattern);
unsigned char *pi = (unsigned char *)malloc(m);
compute_prefix(pi, pattern);
int q = 0;
for(int i = 0; i < n; i++)
{
if(text[i] == pattern[q])
{
q++;
}
else
{
q = pi[q-1];
}

if(q == m)
{
printf("match:%d\n", i-m+1);
}
}

free(pi);

}

int main()
{
char *text = "niskhaoaaakskdfla;askserqoeirsk";
char *pattern = "ababbabbabbababbabb";
kmp_match(text, pattern);

return 0;
}

