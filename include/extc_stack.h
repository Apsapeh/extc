#include <stdlib.h>
#include "extc_rint.h"

#define stack_template_def(name, type)\
    typedef struct stack_##name {\
        size capacity;\
        size size;\
        type* data;\
    } stack_##name;\
\
    stack_##name stack_##name##_init(size size, u8* result);\
    u8 stack_##name##_realloc(stack_##name * v, size n);\
    u8 stack_##name##_push(stack_##name * v, type o);\
    type stack_##name##_pop(stack_##name * v);\
    void stack_##name##_free(stack_##name * v);\
    void stack_##name##_clean(stack_##name * v);



#define stack_template_impl(name, type)\
    stack_##name stack_##name##_init(size _size, u8* result) {\
        stack_##name res;\
        res.size = 0;\
        res.capacity = _size;\
        res.data = (type*)malloc(sizeof(type)*_size);\
        if ((void*)result != NULL) {\
            if ((void*)res.data = NULL) *result = 0;\
            else *result = 1;\
        }\
        return res;\
    }\
    \
    u8 stack_##name##_realloc(stack_##name * v, size n){\
        if (v->capacity == n) return false;\
        type* new_data = (type*)realloc(v->data, n * sizeof(type));\
        if ((void*)new_data == NULL) return false;\
        v->data = new_data;\
        v->capacity = n;\
        return true;\
    }\
    \
    u8 stack_##name##_push(stack_##name * v, type o) {\
        if(v->capacity < v->size+1) return false;\
        v->data[v->size++] = o;\
        return true;\
    }\
    \
    type stack_##name##_pop(stack_##name * v) {\
        return v->data[--v->size];\
    }\
    \
    void stack_##name##_free(stack_##name * v) {\
        v->size = 0;\
        v->capacity = 0;\
        free(v->data);\
    }\
    void stack_##name##_clean(stack_##name * v) {\
        stack_##name##_free(v);\
        v->data = (type*)malloc(0);\
    }