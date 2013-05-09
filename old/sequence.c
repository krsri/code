#include<stdio.h>
#include<conio.h>
main()
{
    int i,n,j,temp,l=512;
    int a[512],b[512];
    FILE *fp,*fp1;
    fp=fopen("1.txt","w");
    fp1=fopen("s512.txt","w");
    for(i=0;i<l;i++)
    {
        n= 3 + ( -5.75 - 4) * rand() * -.650;
        //printf("%d\n",n);
        fprintf(fp,"%d",n);
        fprintf(fp,",");
        a[i]=b[i]=n;
    }


   for(i=0;i<l;i++)
    {
      for(j=i+1;j<l;j++)
      {
           if(a[i]>a[j])
           {
               temp=a[i];
              a[i]=a[j];
              a[j]=temp;
           }
      }
    }



    for(i=0;i<l;i++)
    {
        for(j=0;j<l;j++)
        {
            if(b[i]==a[j])
            {
               // printf("%d\t",j);
                fprintf(fp1,"%d,",j);

            }

        }
    }
fprintf(fp1,"\n");
}
