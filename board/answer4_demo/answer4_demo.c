#include "answer4_demo.h"

static void TaskF01()
{
}

void Answer4_Demo()
{
   char x[10]="sasassss";
    FILE *a = fopen("/Users/gabe/Desktop/a.txt","w");
    fwrite("safdas",10,sizeof(char),a);
    fclose(a);
    a= fopen("/Users/gabe/Desktop/a.txt","r");
    fread(x,10,sizeof (char),a);
    fclose(a);
    printf("%s",x);
   return;
}