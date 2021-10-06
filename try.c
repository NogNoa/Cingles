#include <stdio.h>
#include "numerals.lb.h"

int main(int argc, char *argv[])
{
    bcd a[]={{1,7},{0,6}}, b[]={{0,3},{0,5}};
    bcd c[3];
    printf("%d\n",binarise(add_single(a[1],b[1],c), 2 ));
}
