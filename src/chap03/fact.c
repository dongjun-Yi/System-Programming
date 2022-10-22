#include <stdio.h>
int fact(int n);		// 함수 선언

int global = 10;		// 전역 변수 선언

int main() {   
    int a = 4, b;		// 지역 변수 선언
    b = fact(a); 
    printf("b=%d", b);
    global = global + b;
}

int fact(int n) {  	// 함수 정의
    int result = 1;
    for (int i = 1; i < n; i++)
        result = result * i;
    return result;
}
