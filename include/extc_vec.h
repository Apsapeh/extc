#include <stdlib.h>
#include <string.h>
#include "extc_rint.h"

#define vector_template_def(name, type)\
    typedef struct vec_##name {\
        usize capacity;\
        usize size;\
        type* data;\
    } vec_##name;\
\
    vec_##name vec_##name##_init();\
    u8 vec_##name##_reserve(vec_##name * v, usize n);\
    u8 vec_##name##_push_back(vec_##name * v, type o);\
    u8 vec_##name##_append(vec_##name * v, vec_##name * v2);\
    u8 vec_##name##_append_data(vec_##name * v, type* d, usize n);\
    type vec_##name##_pop_back(vec_##name * v);\
    u8 vec_##name##_erase(vec_##name * v, usize index);\
    u8 vec_##name##_erase_range(vec_##name * v, usize index, usize cound);\
    u8 vec_##name##_shrink_to_fit(vec_##name * v);\
    void vec_##name##_free(vec_##name * v);\
    void vec_##name##_clean(vec_##name * v);



#define vector_template_impl(name, type)\
    vec_##name vec_##name##_init() {\
        vec_##name res;\
        res.size = 0;\
        res.capacity = 0;\
        res.data = (type*)malloc(0);\
        return res;\
    }\
    \
    u8 vec_##name##_reserve(vec_##name * v, usize n){\
        if (v->capacity == n) return false;\
        type* new_data = (type*)realloc(v->data, n * sizeof(type));\
        if ((void*)new_data == NULL) return false;\
        v->data = new_data;\
        v->capacity = n;\
        return true;\
    }\
    \
    u8 vec_##name##_push_back(vec_##name * v, type o) {\
        if(v->capacity < v->size+1) \
            if (!vec_##name##_reserve(v, v->size+1)) return false;\
        v->data[v->size++] = o;\
        return true;\
    }\
    \
    u8 vec_##name##_append(vec_##name * v, vec_##name * v2) {\
        if (!vec_##name##_reserve(v, v->size+v2->size)) return false;\
        memcpy(v->data + v->size, v2->data, v2->size * sizeof(type));\
        v->size = v->size+v2->size;\
        return true;\
    }\
    u8 vec_##name##_append_data(vec_##name * v, type* d, usize n) {\
        if (!vec_##name##_reserve(v, v->size+n)) return false;\
        memcpy(v->data + v->size, d, n * sizeof(type));\
        v->size = v->size+n;\
        return true;\
    }\
    \
    type vec_##name##_pop_back(vec_##name * v) {\
        return v->data[--v->size];\
    }\
    \
    u8 vec_##name##_erase(vec_##name * v, usize index) {\
        if (index >= v->size) return false;\
        memcpy(v->data+index, v->data+index+1, (v->size-index-1)*sizeof(type));\
        --v->size;\
        return true;\
    }\
    \
    u8 vec_##name##_erase_range(vec_##name * v, usize index, usize count) {\
        if (index+count-1 >= v->size) return false;\
        memcpy(v->data+index, v->data+index+count, (v->size-index-count)*sizeof(type));\
        v->size -= count;\
        return true;\
    }\
    \
    u8 vec_##name##_shrink_to_fit(vec_##name * v) {\
        return vec_##name##_reserve(v, v->size);\
    }\
    \
    void vec_##name##_free(vec_##name * v) {\
        v->size = 0;\
        v->capacity = 0;\
        free(v->data);\
        v = NULL;\
    }\
    void vec_##name##_clean(vec_##name * v) {\
        vec_##name##_free(v);\
        v->data = (type*)malloc(0);\
    }