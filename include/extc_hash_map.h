#ifndef EXTC_HASH_MAP_GUARD_H
#define EXTC_HASH_MAP_GUARD_H

#include "extc_vec.h"

#define hash_map_template_def(name, type_key, type_value)\
    typedef struct {\
        type_key key;\
        type_value value;\
        void (*free_function)(type_value*);\
    } hash_map_##name##_pair;\
    vector_template_def(__hash_map_batch_##name, hash_map_##name##_pair)\
    vector_template_def(vec___hash_map_batch_##name, vec___hash_map_batch_##name)\
    typedef struct {\
        unsigned long size;\
        long (*hash_function)(type_key const*);\
        vec_vec___hash_map_batch_##name batches;\
        void (*free_function)(type_value*);\
        unsigned char (*compare_function)(type_key const*, type_key const*);\
    } hash_map_##name;\
    typedef struct {\
        unsigned long batch_idx;\
        unsigned long pair_idx;\
    } hash_map_##name##_iterator;\
    \
    hash_map_##name hash_map_##name##_init(void);\
    void hash_map_##name##_free(hash_map_##name * v);\
    \
    void hash_map_##name##_set_hash_function(hash_map_##name * v, long (*hash_function)(type_key const*));\
    void hash_map_##name##_set_free_function(hash_map_##name * v, void (*free_function)(type_value*));\
    void hash_map_##name##_set_compare_function(hash_map_##name * v, unsigned char (*compare_function)(type_key const*, type_key const*));\
    \
    type_value* hash_map_##name##_insert(hash_map_##name * v, type_key const key, type_value value);\
    type_value* hash_map_##name##_insert_ptr(hash_map_##name * v, type_key const* key, type_value* value);\
    type_value* hash_map_##name##_find(hash_map_##name * v, type_key const key);\
    type_value* hash_map_##name##_find_ptr(hash_map_##name * v, type_key const* key);\
    unsigned char hash_map_##name##_erase(hash_map_##name * v, type_key const key);\
    unsigned char hash_map_##name##_erase_ptr(hash_map_##name * v, type_key const* key);\
    \
    hash_map_##name##_iterator hash_map_##name##_begin(hash_map_##name * v);\
    hash_map_##name##_iterator hash_map_##name##_end(hash_map_##name * v);\
    unsigned char hash_map_##name##_next(hash_map_##name * v, hash_map_##name##_iterator * it);\
    unsigned char hash_map_##name##_iterator_cmp(hash_map_##name##_iterator const * a, hash_map_##name##_iterator const * b);\
    hash_map_##name##_pair * hash_map_##name##_iterator_deref(hash_map_##name * v, hash_map_##name##_iterator const * it);
    /*void hash_map_##name##_prev(hash_map_##name * v, hash_map_##name##_iterator * it);*/



#define hash_map_template_impl(name, type_key, type_value)\
    vector_template_impl(__hash_map_batch_##name, hash_map_##name##_pair)\
    vector_template_impl(vec___hash_map_batch_##name, vec___hash_map_batch_##name)\
    \
    static void vec_vec___hash_map_batch_##name##_free_function(vec___hash_map_batch_##name * v) {\
        vec___hash_map_batch_##name##_free(v);\
    }\
    static void vec___hash_map_batch_##name##_free_function(hash_map_##name##_pair * v) {\
        v->free_function(&v->value);\
    }\
    \
    hash_map_##name hash_map_##name##_init(void) {\
        hash_map_##name res;\
        res.size = 0;\
        res.hash_function = NULL;\
        res.free_function = NULL;\
        res.compare_function = NULL;\
        \
        res.batches = vec_vec___hash_map_batch_##name##_init();\
        vec_vec___hash_map_batch_##name##_set_free_func(&res.batches, vec_vec___hash_map_batch_##name##_free_function);\
        vec_vec___hash_map_batch_##name##_reserve(&res.batches, 5);\
        {\
            unsigned long i;\
            for (i = 0; i < 5; ++i) {\
                vec_vec___hash_map_batch_##name##_push_back(&res.batches, vec___hash_map_batch_##name##_init());\
                vec___hash_map_batch_##name##_set_free_func(&res.batches.data[i], vec___hash_map_batch_##name##_free_function);\
            }\
        }\
        return res;\
    }\
    void hash_map_##name##_free(hash_map_##name * v) {\
        vec_vec___hash_map_batch_##name##_free(&v->batches);\
        v->size = 0;\
        v->hash_function = NULL;\
        v->free_function = NULL;\
        v->compare_function = NULL;\
    }\
    \
    void hash_map_##name##_set_hash_function(hash_map_##name * v, long (*hash_function)(type_key const*)) {\
        v->hash_function = hash_function;\
    }\
    void hash_map_##name##_set_free_function(hash_map_##name * v, void (*free_function)(type_value*)) {\
        v->free_function = free_function;\
        {\
            unsigned long i;\
            for (i = 0; i < v->batches.size; ++i){\
                unsigned long j;\
                for (j = 0; j < v->batches.data[i].size; ++j)\
                    v->batches.data[i].data[j].free_function = free_function;\
            }\
        }\
    }\
    void hash_map_##name##_set_compare_function(hash_map_##name * v, unsigned char (*compare_function)(type_key const*, type_key const*)) {\
        v->compare_function = compare_function;\
    }\
    \
    type_value* hash_map_##name##_insert(hash_map_##name * v, type_key const key, type_value value) {\
        return hash_map_##name##_insert_ptr(v, &key, &value);\
    }\
    type_value* hash_map_##name##_insert_ptr(hash_map_##name * v, type_key const* key, type_value* value) {\
        type_value* finded = hash_map_##name##_find_ptr(v, key);\
        if (finded) {\
            v->free_function(finded);\
            *finded = *value;\
            return finded;\
        }\
        else {\
            /* TODO: Add map size increment */\
            hash_map_##name##_pair p;\
            unsigned long idx;\
            if (v->hash_function == NULL) return NULL;\
            if (v->compare_function == NULL) return NULL;\
            if (v->batches.size < v->size+1) {\
                vec_vec___hash_map_batch_##name new_batches = vec_vec___hash_map_batch_##name##_init();\
                vec_vec___hash_map_batch_##name##_reserve(&new_batches, v->batches.size*2);\
                {\
                    unsigned long i;\
                    for (i = 0; i < v->batches.size*2; ++i) {\
                        vec_vec___hash_map_batch_##name##_push_back(&new_batches, vec___hash_map_batch_##name##_init());\
                        vec___hash_map_batch_##name##_set_free_func(&new_batches.data[i], vec___hash_map_batch_##name##_free_function);\
                    }\
                    \
                    for (i = 0; i < v->batches.size; ++i) {\
                        unsigned long j;\
                        for (j = 0; j < v->batches.data[i].size; ++j) {\
                            const long idx = v->hash_function(&v->batches.data[i].data[j].key) % new_batches.size;\
                            vec___hash_map_batch_##name##_push_back(&new_batches.data[idx], v->batches.data[i].data[j]);\
                        }\
                    }\
                    vec_vec___hash_map_batch_##name##_set_free_func(&v->batches, NULL);\
                    vec_vec___hash_map_batch_##name##_free(&v->batches);\
                    v->batches = new_batches;\
                }\
            }\
            idx = v->hash_function(key) % v->batches.size;\
            p.key = *key;\
            p.value = *value;\
            p.free_function = v->free_function;\
            vec___hash_map_batch_##name##_push_back(&v->batches.data[idx], p);\
            v->size += 1;\
            return &v->batches.data[idx].data[v->batches.data[idx].size - 1].value;\
        }\
        return NULL;\
    }\
    type_value* hash_map_##name##_find(hash_map_##name * v, type_key const key) {\
        return hash_map_##name##_find_ptr(v, &key);\
    }\
    type_value* hash_map_##name##_find_ptr(hash_map_##name * v, type_key const* key) {\
        unsigned long i;\
        unsigned long  idx;\
        if (v->hash_function == NULL) return NULL;\
        if (v->compare_function == NULL) return NULL;\
        idx = v->hash_function(key) % v->batches.size;\
        for (i = 0; i < v->batches.data[idx].size; ++i) {\
            if (v->compare_function(&v->batches.data[idx].data[i].key, key)) \
                return &v->batches.data[idx].data[i].value;\
        }\
        return NULL;\
    }\
    unsigned char hash_map_##name##_erase(hash_map_##name * v, type_key const key) {\
        return hash_map_##name##_erase_ptr(v, &key);\
    }\
    unsigned char hash_map_##name##_erase_ptr(hash_map_##name * v, type_key const* key) {\
        unsigned long i;\
        const unsigned long idx = v->hash_function(key) % v->batches.size;\
        if (v->hash_function == NULL) return 0;\
        if (v->compare_function == NULL) return 0;\
        for (i = 0; i < v->batches.data[idx].size; ++i) {\
            if (v->compare_function(&v->batches.data[idx].data[i].key, key)) {\
                vec___hash_map_batch_##name##_erase(&v->batches.data[idx], i);\
                v->size -= 1;\
                return 1;\
            }\
        }\
        return 0;\
    }\
    \
    hash_map_##name##_iterator hash_map_##name##_begin(hash_map_##name * v) {\
        hash_map_##name##_iterator it;\
        it.batch_idx = 0;\
        it.pair_idx = -1;\
        /*hash_map_##name##_next(v, &it);*/\
        return it;\
    }\
    hash_map_##name##_iterator hash_map_##name##_end(hash_map_##name * v) {\
        hash_map_##name##_iterator it;\
        it.batch_idx = v->batches.size;\
        it.pair_idx = 0;\
        return it;\
    }\
    unsigned char hash_map_##name##_next(hash_map_##name * v, hash_map_##name##_iterator * it) {\
        for (;it->batch_idx < v->batches.size; ++it->batch_idx) {\
            if (++it->pair_idx < v->batches.data[it->batch_idx].size)\
                return 1;\
            it->pair_idx = -1;\
        }\
        return 0;\
    }\
    unsigned char hash_map_##name##_iterator_cmp(hash_map_##name##_iterator const * a, hash_map_##name##_iterator const * b) {\
        return (a->batch_idx == b->batch_idx) && (a->pair_idx == b->pair_idx);\
    }\
    hash_map_##name##_pair * hash_map_##name##_iterator_deref(hash_map_##name * v, hash_map_##name##_iterator const * it) {\
        return &v->batches.data[it->batch_idx].data[it->pair_idx];\
    }


#endif

/*
hash_map_template_def(int, int, int)
hash_map_template_impl(int, int, int)
*/
