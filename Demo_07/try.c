#include <stdio.h>
#include <string.h>

int main()
{
char Str[64];
char *chP;


strcpy(Str,"T04S653453");
Str[10] = '\0';
chP = strchr(Str,'S');
printf("chP - %s len - %d\n",chP,strlen(chP));




}
