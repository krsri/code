#include<stdio.h>
#include<conio.h>
#include<time.h>

time_t seconds;
struct tm *my_time;
main()
{
    int a[10]={0,1,2,3,4,5,6,7,8,9,10};
    int res[4],len=11,i=0,val=0;
    seconds = time (NULL);
      my_time = localtime(&seconds);
    for(i=0;i<5;i++)
    {
        val=my_time->tm_sec %len--;
        res[i]=a[val];
        a[val]=a[len+1];
        //printf("\nlenth=%d , Lenth +1 : %d",len,len+1);
    }
    for(i=0;i<5;i++)
        printf("%d\t",res[i]);
}
