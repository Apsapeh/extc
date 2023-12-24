#include <stdlib.h>
#include "extc_rint.h"

#define vector_template_def(name, type)\
    typedef struct vec_##name {\
        size capacity;\
        size size;\
        type* data;\
    } vec_##name;\
\
    vec_##name vec_##name##_init();\
    void vec_##name##_reserve(vec_##name * v, size n);\
    void vec_##name##_push_back(vec_##name * v, type o);\
    void vec_##name##_free(vec_##name * v);\
    void vec_##name##_clean(vec_##name * v);



#define vector_template_impl(name, type)\
    vec_##name vec_##name##_init() {\
        vec_##name res;\
        res.size = 0;\
        res.capacity = 0;\
        res.data = malloc(0);\
        return res;\
    };\
    \
    void vec_##name##_reserve(vec_##name * v, size n){\
        if (v->capacity >= n) return;\
        v->data = realloc(v->data, n * sizeof(type));\
        v->capacity = n;\
    }\
    \
    void vec_##name##_push_back(vec_##name * v, type o) {\
        if(v->capacity < v->size+1) \
            vec_##name##_reserve(v, v->size+1);\
        v->data[v->size] = o;\
        ++v->size;\
    };\
    \
    void vec_##name##_free(vec_##name * v) {\
        v->size = 0;\
        v->capacity = 0;\
        free(v->data);\
    }\
    void vec_##name##_clean(vec_##name * v) {\
        vec_##name##_free(v);\
        v->data = malloc(0);\
    }