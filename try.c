#include <stdio.h>

void escape(char s[], char t[]);
void descape(char s[], char t[]);
void expand(char s1[],char s2[]);
void itoa(int n, char s[]);
void KnR_itoa(int n, char s[]);
short itob(int n, char s[], short b);
short fill_itoa(int n, char s[], int fill);

int main(int argc, char *argv[])
{
    const int lng=0x20;
    char a[lng],b[lng],c[lng],d[lng];

    itoa(6, a);
    itoa(20, b);
    itob((~(~0U >> 1)), c, 20);
    itob(100, d, 30);


    printf("%s %s  %s %s\n",a,b,c,d);
    
    return 0;
}
