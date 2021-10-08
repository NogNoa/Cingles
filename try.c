#include <stdio.h>
#include <time.h>
#include "numerals.lb.h"

int main(int argc, char *argv[])
{
    bcd a[]={{7,1},{6,0}}, b[]={{3,0},{5,0}};
    bcd c[3];
    printf("%d\n",binarise_single(sub_single(a[0],b[0])));
}
