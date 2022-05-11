#include <string.h>
#include <stdlib.h>
#include "rope.lb.h"


rope rope_get(const char* scroll)
{
    const int total_len=strlen(scroll);
    const int full_cells=total_len / 0x100;
    rope* last = malloc(sizeof(rope));
    const unsigned char last_len = total_len % 0x100;
    *last = (rope) {last_len, NULL, NULL};
    last->str = malloc(last_len+1);
    strncpy(last->str, scroll+(full_cells * 0x100), last_len);
    rope* nxt=last;
    for (int cell=full_cells; cell>0; cell--)
    {   rope* curr =malloc(sizeof(rope));
        *curr = (rope) {0xFF, nxt, NULL};
        curr->str = malloc(0x100);
        strncpy(curr->str, scroll+((cell-1) * 0x100), 0xFF);
        nxt = curr;
    }
    return *nxt;
}
