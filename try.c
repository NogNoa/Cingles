#include <stdio.h>
#include "rope.lb.h"

int main(int argc, char *argv[])
{
    rope a = rope_get("hello");
    puts(a.str);
}
