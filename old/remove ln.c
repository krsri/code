#include<stdio.h>
#include<conio.h>
main()
{
    int i;
    char a[600000];
    FILE *fp ,*fp1;
    fp=fopen("u_s_hihi.0.txt","r");
    fp1=fopen("comma.txt","w");

    for(i=0,(a[i]=getc(fp));!feof(fp);a[++i]=getc(fp));
    a[i]='\0';

    //for(i=0;a[i]!='\0';i++)
       //printf("%c",a[i]);
    for(i=0;a[i]!='\0';i++)
    {
        if(a[i]==' '||a[i]=='\n')

        {
            fprintf(fp1,",");
            i++;
        }

        fprintf(fp1,"%c",a[i]);

    }


   /* for(i=0;(a[i]=getc(fp)!=EOF);i++)
    {
        if(a[i]==' '||a[i]=='\n')
            i++;

            fprintf(fp1,"%c",a[i]);
            fprintf(fp1,",");
    }*/
}
