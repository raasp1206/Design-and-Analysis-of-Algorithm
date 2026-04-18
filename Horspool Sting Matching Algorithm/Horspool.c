#include <stdio.h>
#include <string.h>
#define SIZE 256
int table[SIZE];
int i,j;
void shiftTable(char pattern[])
{
    int m = strlen(pattern);
    for(i = 0; i < SIZE; i++)
        table[i] = m;
    for(j = 0; j < m - 1; j++)
        table[(int)pattern[j]] = m - 1 - j;
}
int horspool(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);
    shiftTable(pattern);
    int i = m - 1;
    while(i < n)
    {
        int k = 0;
        while(k < m && pattern[m-1-k] == text[i-k])
            k++;
        if(k == m)
            return i - m + 1;
        else
            i = i + table[(int)text[i]];
    }
    return -1;
}

int main()
{
    char text[100], pattern[100];
    printf("Enter Text: ");
    scanf("%s", text);
    printf("Enter Pattern: ");
    scanf("%s", pattern);
    int pos = horspool(text, pattern);
    if(pos >= 0)
        printf("Pattern found at position %d\n", pos);
    else
        printf("Pattern not found\n");
    return 0;
}
