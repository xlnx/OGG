#include "utils/ogg_exception.h"
#include <stdlib.h>

void ogg_initialize_exception(void)
{
    __exception_jmp_capacity = 16;
    __exception_jmp_pos = (jmp_buf*)calloc(__exception_jmp_capacity, sizeof(jmp_buf));
    __exception_jmp_cnt = -1;
}

void ogg_finalize_exception(void)
{
    free(__exception_jmp_pos);
}