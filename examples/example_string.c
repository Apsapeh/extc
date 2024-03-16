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

    string str2 = string_from("Text line 2\n");
}