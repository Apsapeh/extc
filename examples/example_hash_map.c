#include <stdio.h>

#include "extc_hash_map.h"

hash_map_template_def(int, int, int)
hash_map_template_impl(int, int, int)

static long hash_int(const int* key) {
    return *key;
}

static unsigned char compare_int(const int* key1, const int* key2) {
    return *key1 == *key2;
}

static void free_int(int* o) {
    printf("Free %d\n", *o);
}



hash_map_template_def(cstr, const char*, long)
hash_map_template_impl(cstr, const char*, long)

long hash_cstr(const char * const* _str) {
    long hash = 0;
    int c;    
    const char* str = *_str;
    while ((c = *str++)) 
        hash = (hash * 31) + c;
    return hash;
}

static unsigned char compare_cstr(const char * const* key1, const char * const* key2) {
    return strcmp(*key1, *key2) == 0;
}

static void free_cstr(long *o) {
    printf("Free cstr %ld\n", *o);
}



int main(void) {
    {
        int *a, *b, *c;
        unsigned char r;
        hash_map_int h = hash_map_int_init();
        hash_map_int_set_hash_function(&h, hash_int);
        hash_map_int_set_free_function(&h, free_int);
        hash_map_int_set_compare_function(&h, compare_int);

        a = hash_map_int_insert(&h, 155, 255);
        printf("%p\n", (void*)a);
        *a = 2556;

        b = hash_map_int_insert(&h, 155, 254145545);
        printf("%p\n", (void*)b);
        printf("%d\n", *b);

        c = hash_map_int_insert(&h, 156, 255);
        printf("%p\n", (void*)c);
        printf("%d\n", *c);
        *c = 3568484;

        r = hash_map_int_erase(&h, 155);
        printf("Remove: %d\n", r);

        {
            unsigned long i;
            for (i = 0; i < h.batches.size; ++i) {
                printf("Batch %lu\n size: %lu\n", i, h.batches.data[i].size);
            }
        }

        hash_map_int_free(&h);
    }


    {
        long *a, *b, *c;
        hash_map_cstr h = hash_map_cstr_init();
        hash_map_cstr_set_hash_function(&h, hash_cstr);
        hash_map_cstr_set_free_function(&h, free_cstr);
        hash_map_cstr_set_compare_function(&h, compare_cstr);

        a = hash_map_cstr_insert(&h, "hello", 255);
        printf("%p\n", (void*)a);
        printf("%ld\n", *a);

        b = hash_map_cstr_insert(&h, "hello_oeuoe", 254145545);
        printf("%p\n", (void*)b);
        printf("%ld\n", *b);

        c = hash_map_cstr_find(&h, "hello");
        printf("%p\n", (void*)c);
        printf("%ld\n", *c);

        hash_map_cstr_free(&h);
    }


    {
        unsigned long i;
        hash_map_int_iterator it;
        hash_map_int h = hash_map_int_init();
        hash_map_int_set_hash_function(&h, hash_int);
        hash_map_int_set_compare_function(&h, compare_int);
        for (i = 0; i < 100; ++i) {
            hash_map_int_insert(&h, i, i);
            printf("Batches size [%lu]: %lu\n", i, h.batches.size);
        }

        it = hash_map_int_begin(&h);
        *hash_map_int_find(&h, 56) = 21548484;
        while (hash_map_int_next(&h, &it)) {
            hash_map_int_pair* pair = hash_map_int_iterator_deref(&h, &it);
            printf("%d: %d\n", pair->key, pair->value);
        }

        hash_map_int_free(&h);
    }
    return 0;
}
