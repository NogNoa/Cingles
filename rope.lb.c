#include <string.h>
#include <stdlib.h>
#include "rope.lb.h"


rope rope_get(char* scroll)
{
    int total_len=strlen(scroll);
    int n_cells=total_len / 0x100 + 1;
    rope* last = malloc(sizeof(rope));
    *last = {total_len % 0x100, NULL, NULL};
    strncpy(last->str, scroll[(n_cells - 1) * 0x100], total_len % 0x100);
    rope* nxt=last;
    for (int i_cl=0;i_cl<n_cells-1;i_cl++)
    {   rope* curr =malloc(sizeof(rope));

    }

}