#include <stdio.h>
#include "libB.h"

void    B_func1(void) {
    puts("B_func1: Hola desde libB!");
}

int B_func2(int a, int b) {
    int s = a + b;
    printf("B_func2: %d + %d = %d\n", a, b, s);
    return s;
}

const char  *B_func3(void) {
    return "B_func3: cadena devuelta por libB";
}
