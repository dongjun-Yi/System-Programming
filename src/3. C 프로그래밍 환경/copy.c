#include <stdio.h>
#include "copy.h"

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char from[], char to[])
{
   int i;

   i = 0;
   while ((to[i] = from[i]) != '\0')
       ++i;
} 
