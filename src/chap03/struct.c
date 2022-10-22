#include <stdio.h>
struct my {
    int a;
    char b;
    float c;
} x = {1,'a',1.5};

int main() 
{
    struct my y = {3,'c',3.5};
    printf("\n x.a=%d x.b=%d x.c=%3.1f", x.a, x.b, x.c);
    printf("\n y.a=%d y.b=%d y.c=%3.1f", y.a, y.b, y.c);
}
