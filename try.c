#include <stdio.h>
#include <time.h>
#include "numerals.lb.h"

int main(int argc, char *argv[])
{
    bcd a[]={{7,1},{6,0}}, b[]={{3,0},{5,0}};
    bcd c[3];
    time_t t0=time(NULL);
    for (int i=0;i<999999999;i++)
        binarise(add_single(a[1],b[1],c), 2);
    printf("bin(+): %gs\n",difftime(time(NULL),t0));
    time_t t1=time(NULL);
    for (int i=0;i<999999999;i++)
        binarise_single(a[1])+ binarise_single(b[1]);
    printf("bine() + bin():%gs\n",difftime(time(NULL),t1));
}
/*
output:
99999999 iters:
bin(+): 3s
bine() + bin():0s

999999999 iters:
bin(+): 26s
bine() + bin():4s
>6x
*/
