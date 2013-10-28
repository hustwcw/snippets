#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int maxlen, maxindex;
/* 输出LCS
 * 在后缀数组方法中，maxindex=0
 * 因为传进来的就是后缀数组suff[]，从0打印maxlen个字符
 */
void outputLCS(char * X)
{
    if(maxlen == 0)
    {
        printf("NULL LCS\n");
        return;
    }
    printf("The len of LCS is %d\n",maxlen);
 
    int i = maxindex;
    while(maxlen--)
    {
        printf("%c",X[i++]);
    }
    printf("\n");
}
 

/* 最长公共子串 后缀数组 */
char * suff[100];
 
int pstrcmp(const void *p, const void *q)
{
    return strcmp(*(char**)p, *(char**)q);
}
 
int comlen_suff(char * p, char * q)
{
    int len = 0;
    while(*p && *q && *p++ == *q++)
    {
        ++len;
        if(*p == '#' || *q == '#')
        {
            break;
        }
    }
    int count = 0;
    while(*p)
    {
        if(*p++ == '#')
        {
            ++count;
            break;
        }
    }
    while(*q)
    {
        if(*q++ == '#')
        {
            ++count;
            break;
        }
    }
    if(count == 1)
        return len;
    return 0;
}
 
void LCS_suffix(char * X, int xlen, char * Y, int ylen)
{
    int suf_index = maxlen = maxindex = 0;
 
    int len_suff = xlen + ylen + 1;
    char * arr = new char [len_suff + 1];  /* 将X和Y连接到一起 */
    strcpy(arr,X);
    arr[xlen] = '#';
    strcpy(arr + xlen + 1, Y);
 
    for(int i = 0; i < len_suff; ++i)  /* 初始化后缀数组 */
    {
        suff[i] = & arr[i];
    }
 
    qsort(suff, len_suff, sizeof(char *), pstrcmp);
 
    for(int i = 0; i < len_suff-1; ++i)
    {
        int len = comlen_suff(suff[i],suff[i+1]);
        if(len > maxlen)
        {
            maxlen = len;
            suf_index = i;
        }
    }
    outputLCS(suff[suf_index]);
}

int main()
{
    char X[] = "aaabacdba";
    char Y[] = "babacabaa";
 
    /* 后缀数组方法 */
    LCS_suffix(X,strlen(X),Y,strlen(Y));
    return 0;
}