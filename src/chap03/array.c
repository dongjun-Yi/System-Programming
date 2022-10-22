#include <stdio.h>
#define N 5

int main()
{
    int sum = 0;
    int a[N];

    for(int i=0; i < N; i++)
        a[i] = i*2;

    for(int i=0; i < N; i++)
           sum += a[i];

    printf("배열 a[]의 합=%d\n", sum);
}
