typedef struct rope{
    unsigned char len;
    struct rope* nxt;
    char* str;
} rope;

rope rope_get(const char*);
rope rope_extend(rope);
rope rope_put(rope);
