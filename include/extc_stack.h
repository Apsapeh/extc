#ifndef EXTC_STACK_GUARD_H
#define EXTC_STACK_GUARD_H

#ifndef STACK_NOSTD
    #include <stdlib.h>
    #include <string.h>

    #define STACK_MALLOC(size) malloc(size)
    #define STACK_REALLOC(ptr, size) realloc(ptr, size)
    #define STACK_FREE(ptr) free(ptr)
    #define STACK_MEMCPY(dest, src, size) memcpy(dest, src, size)
#endif

#define stack_template_def(name, type)\
    typedef struct stack_##name {\
        unsigned long capacity;\
        unsigned long size;\
        type* data;\
    } stack_##name;\
\
    stack_##name stack_##name##_init(unsigned long size, unsigned char* result);\
    unsigned char stack_##name##_realloc(stack_##name * v, unsigned long n);\
    unsigned char stack_##name##_push(stack_##name * v, type o);\
    unsigned char stack_##name##_push_ptr(stack_##name * v, type* o, unsigned long c);\
    unsigned char stack_##name##_pop(stack_##name * v, type* e);\
    unsigned char stack_##name##_pop_ptr(stack_##name * v, unsigned long c, type** e);\
    void stack_##name##_free(stack_##name * v);\
    void stack_##name##_clean(stack_##name * v);



#define stack_template_impl(name, type)\
    stack_##name stack_##name##_init(unsigned long _size, unsigned char* result) {\
        stack_##name res;\
        res.size = 0;\
        res.capacity = _size;\
        res.data = (type*)STACK_MALLOC(sizeof(type)*_size);\
        if ((void*)result != NULL) {\
            if ((void*)res.data == NULL) *result = 1;\
            else *result = 0;\
        }\
        return res;\
    }\
    \
    unsigned char stack_##name##_realloc(stack_##name * v, unsigned long n){\
        type* new_data;\
        if (v->capacity == n) return 0;\
        new_data = (type*)STACK_REALLOC(v->data, n * sizeof(type));\
        if ((void*)new_data == NULL) return 0;\
        v->data = new_data;\
        v->capacity = n;\
        return 1;\
    }\
    \
    unsigned char stack_##name##_push(stack_##name * v, type o) {\
        if(v->capacity < v->size+1) return 0;\
        v->data[v->size++] = o;\
        return 1;\
    }\
    \
    unsigned char stack_##name##_push_ptr(stack_##name * v, type* o, unsigned long c) {\
        if(v->capacity < v->size+c) return 0;\
        STACK_MEMCPY(&v->data[v->size], o, sizeof(type)*c);\
        v->size += c;\
        return 1;\
    }\
    \
    unsigned char stack_##name##_pop(stack_##name * v, type* e) {\
        if(v->size == 0) return 0;\
        if ((void*)e != NULL) *e = v->data[--v->size];\
        return 1;\
    }\
    unsigned char stack_##name##_pop_ptr(stack_##name * v, unsigned long c, type** e) {\
        if(v->size < c) return 0;\
        v->size -= c;\
        if ((void*)e != NULL) *e = &v->data[v->size];\
        return 1;\
    }\
    \
    void stack_##name##_free(stack_##name * v) {\
        v->size = 0;\
        v->capacity = 0;\
        STACK_FREE(v->data);\
    }\
    void stack_##name##_clean(stack_##name * v) {\
        stack_##name##_free(v);\
        v->data = (type*)STACK_MALLOC(0);\
    }

#endif
