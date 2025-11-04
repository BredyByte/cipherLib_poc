#include <stdio.h>
#include "libB.h"

int main(void)
{
    printf("Programa principal arrancado.\n");
    B_func1();
    
    int r = B_func2(10,32);
    
    printf("Resultado devuelto por B_func2: %d\n", r);
    printf("%s\\n", B_func3());
    printf("Programa principal finalizado.\n");
    
    return 0;
}