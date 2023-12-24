#include <extc_vec.h>
#include <stdio.h>
#include <stdlib.h>

// Создаем определения функций и структру
// Первый аргумент - имя вектора, второй - тип, коотрый он хранит
// Этот макрос можно исплользовать в хедерах(.h) или исходниках
vector_template_def(i32, i32)

// Создаем реализации функций
// Первый аргумент - имя вектора, второй - тип, коотрый он хранит
// Этот макрос нужно использовать ТОЛЬКО В ИСХОДНИКАХ
vector_template_impl(i32, i32)

int main() {
    // Инициализирует вектор
    vec_i32 a = vec_i32_init();
    printf("Size: %d\nCapacity: %d\n", a.size, a.capacity);
    vec_i32_reserve(&a, 268435456);
    printf("Size: %d\nCapacity: %d\n", a.size, a.capacity);
    //vec_i32_clean(&a);
    // Добавляем элемент
    {
        i32 i;
        for(i = 0; i < 26800; ++i) {
            vec_i32_push_back(&a, i * 15); 
            printf("Size: %d\nCapacity: %d\n", a.size, a.capacity);
        }
    }
    printf("Size: %d\nCapacity: %d\n", a.size, a.capacity);
    // Выводим элемнт
    printf("%d\n", a.data[0]);
    // Очищаем вектор, иначе будет утечка памяти 
    while(1) {}
    vec_i32_free(&a);
}