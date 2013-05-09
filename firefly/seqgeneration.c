#include<stdio.h>
#include<conio.h>
#include<time.h>

time_t seconds;
struct tm *my_time;

double rando(int sec)
{
	int ran,x;
	double val;
	for(x=1; x<=sec; x++)
		ran = rand();
	//return(((ran+sec)%10000));
	val=((ran+sec)%1000);
	return((val/1000));
}

main()
{
    int i,j,l=10,seq[9],p=0;
    double a[10],b[10],n,temp;
    seconds = time (NULL);
    my_time = localtime(&seconds);

    for(i=0;i<l;i++)
    {
        //n= 3 + ( -5.75 - 4) * rand() * -.650;
        n= rando(my_time->tm_sec) ;

        a[i]=b[i]=n;
    }
//printf("%d",n);
    for(i=0;i<l;i++)
       printf("%lf\n",a[i]);
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
                seq[p++]=j;
            }

        }
    }
    for(i=0;i<10;i++)
        printf("%d\t",seq[i]);

}
