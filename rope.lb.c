#include <string.h>
#include <stdlib.h>
#include "rope.lb.h"


rope rope_get(char* scroll)
{
    int total_len=strlen(scroll);
    int full_cells=total_len / 0x100;
    rope* last = malloc(sizeof(rope));
    *last = (rope) {total_len % 0x100, NULL, NULL};
    strncpy(last->str, scroll+(full_cells * 0x100), total_len % 0xFF);
    rope* nxt=last;
    for (int cell=full_cells-1; cell>=0; cell--)
    {   rope* curr =malloc(sizeof(rope));
        *last = (rope) {0xFF, nxt, NULL};
        strncpy(last->str, scroll+(cell * 0x100), 0xFF);
        nxt = curr;
    }
    return *last;
}