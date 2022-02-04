#include <stdio.h>
#include "rope.lb.h"

int main(int argc, char *argv[])
{
    rope a = {5,0,"hello"};
    puts(a.str);
}
