#include <stdio.h>
#include <extc_stack.h>
#include <extc_rint.h>

stack_template_def(i32, i32)
stack_template_impl(i32, i32)

int main(void) {
    u8 r;
    stack_i32 s;
    s = stack_i32_init(5, &r);
    if (r != 0) 
        printf("Error\n");

    printf("%d\n", stack_i32_push(&s, 1));
    printf("%d\n", stack_i32_push(&s, 2));
    printf("%d\n", stack_i32_push(&s, 3));
    printf("%d\n", stack_i32_pop(&s, NULL));
    printf("%d\n", stack_i32_push(&s, 4));
    
    {
        int b[3] = {56, 57, 58};
        printf("%d\n\n\n", stack_i32_push_ptr(&s, b, 3));
    }

    {
        int i;
        for(i = 0; i < s.size; ++i) {
            printf("%d\n", s.data[i]);
        }
    }

    return 0;   
}
