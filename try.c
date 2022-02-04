#include <stdio.h>
#include "rope.lb.h"

int main(int argc, char *argv[])
{
    rope a = rope_get("hello");
    puts(a.str);
    char b[0x102];
    for (int i=0;i<0x101;i++)
        b[i]='$';
    b[0x101]='\0';
    rope c = rope_get(b);
}
