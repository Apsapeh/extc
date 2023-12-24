#include "extc_rint.h"

#define vector_template_def(name, type)\
    typedef struct vec_##name {\
        size capacity;\
        size size;\
        type* data;\
    } vec_##name;\
\
    vec_##name vec_##name##_init();\
    void vec_##name##_push_back(vec_##name * v, type o);\
    void vec_##name##_free(vec_##name * v);



#define vector_template_impl(name, type)\
    vec_##name vec_##name##_init() {\
        vec_##name res;\
        res.size = 0;\
        res.capacity = 0;\
        res.data = malloc(0);\
        return res;\
    };\
    \
    void vec_##name##_push_back(vec_##name * v, type o) {\
        v->data = realloc(v->data, (v->size+1) * sizeof(type));\
        v->data[v->size] = o;\
    };\
    \
    void vec_##name##_free(vec_##name * v) {\
        free(v->data);\
    }