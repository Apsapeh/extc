#include <extc_vec.h>
#include <extc_rint.h>
#include <stdio.h>
#include <stdlib.h>

/* Создаем определения функций и структру
   Первый аргумент - имя вектора, второй - тип, коотрый он хранит
   Этот макрос можно исплользовать в хедерах(.h) или исходниках*/
vector_template_def(i32, i32)

/* Создаем реализации функций
   Первый аргумент - имя вектора, второй - тип, коотрый он хранит
   Этот макрос нужно использовать ТОЛЬКО В ИСХОДНИКАХ */
vector_template_impl(i32, i32)

int main() {
    vec_i32 a = vec_i32_init();
    printf("Size: %lu\nCapacity: %lu\n", a.size, a.capacity);
    vec_i32_push_back(&a, 1);
    vec_i32_push_back(&a, 2);
    vec_i32_push_back(&a, 3);

    vec_i32 b = vec_i32_init();
    vec_i32_push_back(&b, 4);
    vec_i32_push_back(&b, 5);
    vec_i32_push_back(&b, 6);
    vec_i32_push_back(&b, 7);
    vec_i32_push_back(&b, 8);
    vec_i32_push_back(&b, 9);
    vec_i32_push_back(&b, 10);
    /*vec_i32_erase(&b, 2);
    vec_i32_erase(&b, 4);*/
    vec_i32_erase_range(&b, 2, 3);
    vec_i32_shrink_to_fit(&b);

    {
        int i;
        for (i = 0; i < b.size; ++i) {
            printf("b[%d] - %d\n", i, b.data[i]);
        }
    }
    printf("Size: %lu\nCapacity: %lu\n", b.size, b.capacity);


    

    printf("%d\n", vec_i32_pop_back(&b));
    printf("%d\n", vec_i32_pop_back(&b));
    printf("Size: %lu\nCapacity: %lu\n", b.size, b.capacity);


    vec_i32_append(&a, &b);
    printf("Size: %lu\nCapacity: %lu\n", a.size, a.capacity);
    
    int i;
    for (i = 0; i < a.size; ++i) {
        printf("a[%d] - %d\n", i, a.data[i]);
    }
}