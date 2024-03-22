#include <extc_string.h>
#include <stdio.h>
#include <stdlib.h>

/* Создаем реализации функций
   Первый аргумент - имя вектора, второй - тип, коотрый он хранит
   Этот макрос нужно использовать ТОЛЬКО В ИСХОДНИКАХ */
string_template_impl()

int main() {
    string str = string_from("Text line 1\n");
    printf("%s", str.str);
    printf("%lu %lu\n", str.size, str.cstr_vec.size);

    string_erase(&str, 4);
    printf("%s", str.str);
    string_insert(&str, 4, '$');
    printf("%s", str.str);


    string str3 = string_from("repcatrepcatroeapracatreprep \n");
    string_replace(&str3, "rep", "***");
    printf("Rep str: %s", str3.str);
    vec_string split_str3 = string_split(&str3, "cat");
    size_t i;
    for (i = 0; i < split_str3.size; ++i) {
        printf("Split str: %s\n", split_str3.data[i].str);
    }
    vec_string_free(&split_str3);


    string str2 = string_from("Text line 2\n");
}