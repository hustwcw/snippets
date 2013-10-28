#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;


char* findsubstring(char* a) {
    int count = 0;
    int maxLen;
    char *start = a;
    char *p = a;
    int ascii[128] = {0};
    while(*a != 0)
    {
        if(ascii[*a] == 0)
        {
        	++count;
        }
        ++ascii[*a];
        if(count < 4 && (a-start+1) > maxLen)
        {
        	p = start;
        	maxLen = a-start+1;
        }
        while(count > 3)
        {
        	--ascii[*start];
        	if(ascii[*start] == 0)
        	{
        		--count;
        	}
        	++start;
        }
        ++a;
    }

    char *result = (char *)malloc(maxLen+1);
    strncpy(result, p, maxLen);
    result[maxLen] = '\0';
    return result;
}


int main()
{
	char *str = "abbeecddedecehfghffhggh";
	cout << findsubstring(str) << endl;

	return 0;
}