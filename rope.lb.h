typedef struct rope{
    unsigned char len;
    struct rope* nxt;
    char* str;
} rope;

rope rope_get(char*);
rope rope_extend(char*);
rope rope_put(char*);
