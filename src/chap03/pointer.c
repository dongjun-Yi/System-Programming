#include <stdio.h>
int main()
{
    int a = 10;
    int *p = &a; 	
    printf("%lu : %d\n", &a, a);
    printf("%lu : %d\n", p, *p);
    *p = *p + 10; 	// a = 20과 동일
    printf("%lu : %d\n", &a, a);
    printf("%lu : %d\n", p, *p);
    a = 30; 	// *p = 30과 동일
    printf("%lu : %d\n", &a, a);
    printf("%lu : %d\n", p, *p);
}
