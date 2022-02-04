#include <string.h>
#include <stdlib.h>
#include "rope.lb.h"


rope rope_get(char* str)
{
    int total_len=strlen(str);
    int n_cells=total_len / 0x100;
    rope* first=malloc(sizeof(rope));
    rope* prev=first;
    for (int i_cl=0;i_cl<n_cells-1;i_cl++)
    {   rope* curr =

    }

}