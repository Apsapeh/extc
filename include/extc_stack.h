#include <stdlib.h>
#include "extc_rint.h"

#define stack_template_def(name, type)\
    typedef struct stack_##name {\
        size capacity;\
        size size;\
        type* data;\
    } vec_##name;\
\
    vec_##name vec_##name##_init(size size, u8* result);\
    u8 vec_##name##_realloc(vec_##name * v, size n);\
    u8 vec_##name##_push(vec_##name * v, type o);\
    type vec_##name##_pop(vec_##name * v);\
    void vec_##name##_free(vec_##name * v);\
    void vec_##name##_clean(vec_##name * v);



#define stack_template_impl(name, type)\
    vec_##name vec_##name##_init(size _size, u8* result) {\
        vec_##name res;\
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
    u8 vec_##name##_realloc(vec_##name * v, size n){\
        if (v->capacity == n) return false;\
        type* new_data = (type*)realloc(v->data, n * sizeof(type));\
        if ((void*)new_data == NULL) return false;\
        v->data = new_data;\
        v->capacity = n;\
        return true;\
    }\
    \
    u8 vec_##name##_push(vec_##name * v, type o) {\
        if(v->capacity < v->size+1) return false;\
        v->data[v->size++] = o;\
        return true;\
    }\
    \
    type vec_##name##_pop(vec_##name * v) {\
        return v->data[--v->size];\
    }\
    \
    void vec_##name##_free(vec_##name * v) {\
        v->size = 0;\
        v->capacity = 0;\
        free(v->data);\
    }\
    void vec_##name##_clean(vec_##name * v) {\
        vec_##name##_free(v);\
        v->data = (type*)malloc(0);\
    }