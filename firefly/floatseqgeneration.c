#include<stdio.h>
#include<conio.h>
#include<time.h>

time_t seconds;
struct tm *my_time;

/*float rando(int sec)
{
	int ran,x;
	for(x=1; x<=sec; x++)
		ran = rand();
	return((ran+sec)*.0025);
}*/
float rando(int sec)
{
	int min=0 ,max=1;
	double scaled = (double)rand()/1.0;

    return (max - min +1)*scaled* sec + min ;
}


main()
{
    int i,n,j,temp,l=10,seq[9],p=0;
    float a[10],b[10];

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
        printf("%f\n",a[i]);
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
