#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<math.h>

time_t seconds;
struct tm *my_time;
int Task,**PCM,Mac;
float **MacCostArray;
int G_stack[100],G_tail=0;
int Stack_check(int TaskNum);
void push(int a);
void pop(void);
int Stack_read(void);

float ReadFile(FILE *p);
void ProcAlloc(void);
int CurrentTask;
void Allocate(int endindex);
int Hashed[100];
float MachineSearch(int MachineNum,float TimeConstraint);
int LeastCheck(float *LeastArray);
void BuildStructure(int task ,float endtime);
float TimeStamp(int TaskNum,int MachineNum);
float MaxCheck(float *MaxArray,int endindex);

typedef struct storedata
{
    int seq[10],mkspn;
    double posval[10],np[10];
}Data;
//Data d[10];
typedef struct MacAlloc
{
        int TaskNo;
        float StartTime,EndTime;
        MacAlloc *Next;
}Machine;

Machine **MacAllocationArray;

Machine *StrAll()
{
     Machine *temp;
     temp = (Machine*)malloc(sizeof(Machine));
     temp->Next = NULL;
     temp->StartTime=0;
     temp->EndTime=0;
     return temp;
}

double rando(int sec)
{
	int ran,x;
	double val;
	for(x=1; x<=sec; x++)
		ran = rand();
	val=((ran+sec)%1000);
	return((val/1000));
}

Data d[10],tmp;
static int counter=0;
main()
{

int se=1,nmac=0,k;
for(;counter<10;counter++)
{

    if(se==1)
    {
      for(k=0;k<10;k++)
      {

      printf("now in se1 part\n");
      float temp2;
      int z,k=0;
      int i,j,forswp,l=10,seq[9],q=0,p=0;

      double a[10],b[10],n,temp;
      seconds = time (NULL);
      my_time = localtime(&seconds);
      FILE *fp,*MC;
      fp=fopen("data1.txt","r");
      if(fp==NULL)
     printf("Cannot open");
      Mac=(int)ReadFile(fp);
      Task=(int)ReadFile(fp);
      MacCostArray = ( float ** )(malloc(sizeof(float)*(Task+1)));
      for(i=0;i<Task;i++)
      MacCostArray[i]=(float*)(malloc(sizeof(float)*(Mac+1)));
      MacAllocationArray= (Machine **)(malloc(sizeof(Machine)* Mac));
      for(i=0;i<Mac;i++)
      {
                        MacAllocationArray[i]=StrAll();
      }
    for(i=0;i<l;i++)
    {
        n= rando(my_time->tm_sec) ;
        a[i]=b[i]=n;
        d[k].posval[i]=n;
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
                seq[p++]=j;
                d[k].seq[q++]=j;
            }

        }
    }
      for(i=0;i<Task;i++)

      {
                        j=seq[i];
                         push(j);
      }

      for(i=0;i<Mac;i++)
      {
              for(j=0;j<Task;j++)
              {
                                *(*(MacCostArray+j)+i)=ReadFile(fp);
              }

      }
      for(i=0;i<Task;i++)
      {
                        temp2=0;temp=0;
                         for(j=0;j<Mac;j++)
                         {

                                           temp=*(*(MacCostArray+i)+j);
                                           temp2=temp2+temp;
                         }
                         *(*(MacCostArray+i)+Mac)=(temp2/Mac);
      }
      for(i=0;i<Task/2;i++)
      {
                           j=G_stack[i];
                           G_stack[i]=G_stack[G_tail-1-i];
                           G_stack[G_tail-1-i]=j;
      }
      ProcAlloc();
      int makespan=0;
      Machine *temp5;
      for(i=0;i<Mac;i++)
      {

                        temp5=MacAllocationArray[i];
                        while (temp5!=NULL)
                        {


                              if(makespan<temp5->EndTime)
                              makespan=temp5->EndTime;
                              temp5=temp5->Next;
                        }
      }
                d[k].mkspn=makespan;
                                              MC=fopen("MakespanFA.txt","a");

                                              fprintf(MC,"%d\n",makespan);
                                              printf("%d \n",d[k].mkspn);


      fclose(fp);
      fclose(MC);
    }


    }//se1 ends here

    else
    {
        int dis=50;
        nmac=(Mac*dis)/100;
        printf("%d",nmac);

    }

//check stored values
int k,i,j,t=0,x;
//for(i=0;i<10;i++)
  //      printf("ff no : %d  mkspn %d\n",i,d[i].mkspn);

// function for finding distance between two firefly
//int k,i,j,t,x;
double sum=0,r=0,e=0;
//firefly movmentstarts here
while(t<10)
{
    for(i=0;i<10;i++)
    {

        for(j=0;j<10;j++)
        {
            if(d[j].mkspn < d[i].mkspn)
            {

                for(k=0;k<10;k++)
                sum+=(d[j].posval[k]- d[i].posval[k])*(d[j].posval[k]- d[i].posval[k]);
                r=sqrt(sum);
                e=exp(-r);
                for(x=0;x<10;x++)
                    d[i].np[x]= (d[i].posval[x] + 1 * e + .2 * ( rando(my_time->tm_sec) - .5 ))  ;

            }
        }

    }
 //printf("value of e : %f\n %f",e , sum);


 t++;
}//while ends
se++;

int min=0;
for(i=0;i<10;i++)
{
    min=i;
    for(j=i+1;j<10;j++)
    {
        if(d[j].mkspn< d[min].mkspn)
            min=j;
    }
    tmp=d[min];
    d[min]=d[i];
    d[i]=tmp;

}



}//for ends



}



//File Function...............................................................................................

float ReadFile(FILE *fp)

{



      char filetemp;

      filetemp=fgetc(fp);

      int counter;

      float fileb,filec=0,filed=0;

      while(filetemp !=',')

      {

                                      fileb=filetemp-'0';

                                      filec=10*filec+fileb;

                                      filetemp=fgetc(fp);

                                      if(filetemp==EOF)

                                      {

                                                       //printf("Error Reading file\n\n");

                                                       break;

                                      }

                                      if(filetemp=='.')

                                      {              counter=1;

                                                     filetemp=fgetc(fp);

                                                     while(filetemp !=',')

                                                     {

                                                          fileb=filetemp-'0';

                                                          filed=10*filed+fileb;

                                                          counter=counter*10;

                                                          filetemp=fgetc(fp);

                                                          if(filetemp==EOF)

                                                          {

                                                                           //printf("Error Reading file\n\n");

                                                                           break;

                                                          }

                                                     }

                                                     filed=filed/counter;

                                                     filec=filec+filed;

                                      }

      }

      return filec;

}



//stack functions-----------------------------------------------------------

void push(int TaskNum)

{

     G_stack[G_tail]=(TaskNum+1);

     G_tail++;

}

void pop(void)

{

     if(G_tail==0)

     return;

     G_tail-=1;

}

int Stack_check(int TaskNum)

{

     if(G_tail==0)

     {

             return 0;

     }

     for(int i=0;i<G_tail;i++)

     {

             if((TaskNum+1)==G_stack[i])

             {

                  return 1;

             }

     }

     return 0;

}

int Stack_read(void)

{

     if(G_tail==0)

     return -1;

     return (G_stack[G_tail-1]-1);

}

//................................................................................................................



void ProcAlloc(void)

{
    int j=0;
     while(G_tail>0)

     {

                    CurrentTask=Stack_read();

                    pop();

                    Allocate(j);
                    //PrecedenceCheck();

     }

}

void Allocate(int endindex) //to Allocate to a machine

{

     float StartVal,LeastMacArray[1000],MaxArray[1000],mm;

     int find;

     if(endindex==0)

     {

         for(int i=0;i<Mac;i++)

         {

                            StartVal=MachineSearch(i,0);

                            LeastMacArray[i]=MachineSearch(i,0)+ *(*(MacCostArray+CurrentTask)+i);

                            //intf("\n\nCalling build Structure\t TaskNum: %d\tMachine No:%d\t Cost : %f ",CurrentTask,find,LeastMacArray[find]);

         }

         find = LeastCheck(LeastMacArray);

         //printf("\n\nCalling build Structure\t TAskNum: %d\tMachine No:%d\t Cost : %f \n\n",CurrentTask,find,LeastMacArray[find]);

         BuildStructure(find,LeastMacArray[find]);

         return;

     }


     for(int i=0;i<Mac;i++)

     {

             for(int k=0;k<endindex;k++)

             {

                         StartVal=MachineSearch(i,0);

                         //printf("\n\nMAchine %d\tTask: %d \t \tStartval : %f ",i,Precedence[k],StartVal);

                         //getch();

                          MaxArray[k]=StartVal;


                         //float TimeStamp(int TaskNum,int MachineNum)

                         //int MaxCheck(float *MaxArray,int endindex);

             }

             mm = MaxCheck(MaxArray,endindex);

             LeastMacArray[i]=mm+*(*(MacCostArray+CurrentTask)+i);

     }

     find = LeastCheck(LeastMacArray);

     //printf("\n\nCalling build Structure for\t TaskNum: %d\tMachine No:%d\t Cost : %f ",CurrentTask,find,LeastMacArray[find]);

     //printf("\n---------------------------------------------------------\n");

     BuildStructure(find,LeastMacArray[find]);//find is Mac Number

     return;



}







float MachineSearch(int MachineNum,float TimeConstraint) // returns possible start time on machine

{

      Machine *CurrentPtr,*PrevPtr;

      float least=0,time[100];

      int count=0;

      CurrentPtr=MacAllocationArray[MachineNum];

     /* if(CurrentPtr->Next==NULL && CurrentPtr->EndTime<TimeConstraint)

      {

             return (TimeConstraint);

      }*/

      if(CurrentPtr->Next==NULL)

      {if(CurrentPtr->EndTime<TimeConstraint)

      {

             return (TimeConstraint);

      }}

      PrevPtr=CurrentPtr;

      CurrentPtr=CurrentPtr->Next;

      while(CurrentPtr!=NULL)

      {

             if(PrevPtr->EndTime >= TimeConstraint && (CurrentPtr->StartTime-PrevPtr->EndTime)>=*(*(MacCostArray+CurrentTask)+MachineNum))

             return PrevPtr->EndTime;

             if(TimeConstraint > PrevPtr->EndTime && TimeConstraint+ *(*(MacCostArray+CurrentTask)+MachineNum)<=CurrentPtr->StartTime)

             {

             //printf("\n\n\n--------Returning time constraint : %f ",TimeConstraint);

             //getch();

             return TimeConstraint;

             }



             PrevPtr=CurrentPtr;

             CurrentPtr=CurrentPtr->Next;

             count++;

      }

      if(PrevPtr->EndTime<TimeConstraint  && MachineNum!=CurrentTask)

      return TimeConstraint;

      return PrevPtr->EndTime;



}



float TimeStamp(int PrecedenceTask,int MachineToAllocate)//Not the precedence machine

{

      float sval;

      Machine *temp=MacAllocationArray[Hashed[PrecedenceTask]];

      while(temp!=NULL)

      {

                       //printf("\n\nTimestamp once");

                       //getch();

                       if(temp->TaskNo==PrecedenceTask)

                       sval=temp->EndTime;

                       temp=temp->Next;

      }

      if(MachineToAllocate==Hashed[PrecedenceTask])

      return sval;

      else return (sval+*(*(PCM+PrecedenceTask)+CurrentTask));

}

int LeastCheck(float *LeastArray)

{

    int temp;

    float least=100000000;

    for (int i=0;i<Mac;i++)

    {

        if(LeastArray[i]<=least)

        {

                                least=LeastArray[i];

                                temp=i;

        }

    }

    return temp;

}



void BuildStructure(int find,float Endtime)

{

     Machine *temp,*box,*prev;

     float begin;

     int counter=0;

     begin = Endtime-(*(*(MacCostArray+CurrentTask)+find));

     //printf("\nTest BEgin : %f ",begin);

     //getch();

     temp = MacAllocationArray[find];

     if(temp->Next==NULL)

     {

                         box=StrAll();

                         box->StartTime=begin;

                         box->EndTime = Endtime;

                         box->TaskNo = CurrentTask;

                         if(temp==MacAllocationArray[find] && temp->EndTime==0)

                         {

                             MacAllocationArray[find]=box;

                             Hashed[CurrentTask]=find;

                             return;

                         }

                         /*else

                         {

                             temp->Next=box;

                         }*/

     }

     prev=temp;

     temp=temp->Next;

     while(temp!=NULL)

     {



                            if(begin>=prev->EndTime)

                            {

                                             if(temp->StartTime>Endtime)

                                             {box=StrAll();

                                             box->StartTime=begin;

                                             box->EndTime = Endtime;

                                             box->Next=temp;

                                             box->TaskNo=CurrentTask;

                                             prev->Next=box;

                                             //printf("\nI'm here Structure written");

                                             Hashed[CurrentTask]=find;

                                             return;}

                            }

                            prev=temp;

                            temp=temp->Next;



     }

     box=StrAll();

     box->StartTime=begin;

     box->EndTime = Endtime;

     box->TaskNo=CurrentTask;

     prev->Next=box;

     //printf("\n---------Structure written");

     Hashed[CurrentTask]=find;

     return;

}

float MaxCheck(float *MaxArray,int endindex)

{

    int temp;

    float max=0;

    for (int i=0;i<endindex;i++)

    {

        if(MaxArray[i]>=max)

        {

                                max=MaxArray[i];

                                temp=i;

        }

    }

    return max;

}

