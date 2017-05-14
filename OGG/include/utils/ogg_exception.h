#ifndef MY__EXCEPTION__HEADER_FILE____
#define MY__EXCEPTION__HEADER_FILE____

#include <setjmp.h>

#define _try \
    switch (__dummy_ret_value) {\
        case 0:
#define _catch(x) \
    break; case (x):
#define _throw(x) \
    longjmp(__exception_jmp_pos[__exception_jmp_cnt], (x))
#define _exception(...) \
    do {\
        if (++__exception_jmp_cnt == __exception_jmp_capacity) {\
            jmp_buf *data = (jmp_buf*)calloc(__exception_jmp_capacity * 2, sizeof(jmp_buf));\
            memcpy(data, __exception_jmp_pos, __exception_jmp_capacity * sizeof(jmp_buf));\
            free(__exception_jmp_pos);\
            __exception_jmp_pos = data;\
            __exception_jmp_capacity *= 2;\
        }\
        int __dummy_ret_value = setjmp(__exception_jmp_pos[__exception_jmp_cnt]);\
        __VA_ARGS__\
        break; default: {\
            --__exception_jmp_cnt; _throw(__dummy_ret_value);\
        }\
        }\
        __exception_jmp_cnt--;\
    } while (0)

extern jmp_buf *__exception_jmp_pos;
extern int __exception_jmp_cnt, __exception_jmp_capacity;

void ogg_initialize_exception(void);
void ogg_finalize_exception(void);

#endif //MY__EXCEPTION__HEADER_FILE____