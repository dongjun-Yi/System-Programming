#include <stdio.h>
int main() 
{  
    int *p, a[4] = {10,20,30,40};    

    printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);        
    p=a;    
    printf("%d %d %d %d %d\n", *p, *(p+1), p[1], *(p+2), p[2]);
}
