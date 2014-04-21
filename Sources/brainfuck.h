#define BF_ERR_NONE 0
#define BF_ERR_MISSING_LOOP_START 1
#define BF_ERR_MISSING_LOOP_END   2

typedef void(*BF_IO)(unsigned char*);
typedef void(*BF_FUNCTION)(unsigned char*,BF_IO,BF_IO);

unsigned short brainfuck_compile(char *in, unsigned short *out);
