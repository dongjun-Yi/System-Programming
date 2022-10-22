#include <stdio.h>
struct student {
    char name[10];
    int age;
} man[3], *p;

void main() {
    int i;

    for (i=0; i<3; i++ ) {
        printf("이름: "); 
        scanf("%s", man[i].name);
        printf("나이: "); 
        scanf("%d", &man[i].age);
    }

   for (i=0; i<3; i++)
       printf("\n이름=%10s 나이=%3d", man[i].name, man[i].age);

   for (i=0, p=man; i<3; i++, p++)
       printf("\n이름=%10s 나이=%3d", (*p).name, (*p).age);

   for (i=0, p = man; i<3; i++, p++)
       printf("\n이름=%10s 나이=%3d", p->name, p->age);
}
