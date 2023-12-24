/*#include <stdlib.h>
#include <string.h>
#include <extc_vec.h>



_export vec vec_init(size element_size) {
    vec res;
    res.size = 0;
    res.capacity = 0;
    res.element_size = element_size;
    res.data = malloc(0);
    return res;
};

_export void vec_push_back(vec* v, void* o) {
    v->data = realloc(v->data, v->size);
    //v->data[v->size];
    v->data[v->size] = malloc(v->element_size);
    memcpy(v->data[v->size], o, v->element_size);
    ++v->size;
    ++v->capacity;
}*/