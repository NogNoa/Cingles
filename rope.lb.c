#include <string.h>
#include <stdlib.h>
#include "rope.lb.h"


rope rope_get(const char* scroll)
{
    const int total_len=strlen(scroll);
    const int full_cells=total_len / 0x100;
    rope* last = malloc(sizeof(rope));
    *last = (rope) {total_len % 0x100, NULL, NULL};
    const int last_len = total_len % 0xFF;
    last->str = malloc(last_len);
    strncpy(last->str, scroll+(full_cells * 0x100), last_len);
    rope* nxt=last;
    for (int cell=full_cells-1; cell>=0; cell--)
    {   rope* curr =malloc(sizeof(rope));
        *curr = (rope) {0xFF, nxt, NULL};
        curr->str = malloc(0xFF);
        strncpy(curr->str, scroll+(cell * 0x100), 0xFF);
        nxt = curr;
    }
    return *last;
}