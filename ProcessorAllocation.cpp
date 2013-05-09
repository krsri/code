#include<stdio.h>

#include<stdlib.h>

#include<conio.h>



int Task,**PCM,Mac;

float **MacCostArray;

//----Stack Functions

int G_stack[100],G_tail=0;

int Stack_check(int TaskNum);

void push(int a);

void pop(void);

int Stack_read(void);

//-----Stack Function Ends here



float ReadFile(FILE *p); //File Reading



//----------------------Processor Allocation specific



void ProcAlloc(void);

int CurrentTask;

int Precedence[100];

void PrecedenceCheck();

void Allocate(int endindex);

int Hashed[100];

float MachineSearch(int MachineNum,float TimeConstraint);

int LeastCheck(float *LeastArray);

void BuildStructure(int task ,float endtime);

float TimeStamp(int TaskNum,int MachineNum);

float MaxCheck(float *MaxArray,int endindex);



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



//---------------------PRocessor Allocation specific ends here



main(int argc,const char *argv[])

{

      int z;



      int i,j;

      float temp,temp2;

      FILE *fp,*sp;

      fp=fopen(argv[1],"r");

      sp=fopen("SeqFA.txt","r");

      /*if(fp==NULL || sp==NULL)

      {

                  printf("Cannot open");

      }*/

      Mac=(int)ReadFile(fp);

      Task=(int)ReadFile(fp);

      //printf(" \n\nMachine: %d \n\nTask : %d \n\n",Mac,Task);



      MacCostArray = ( float ** )(malloc(sizeof(float)*(Task+1)));

      for(i=0;i<Task;i++)

      MacCostArray[i]=(float*)(malloc(sizeof(float)*(Mac+1)));

      //printf(" \n\nOk\n\n");

      //getch();



      MacAllocationArray= (Machine **)(malloc(sizeof(Machine)* Mac));

      for(i=0;i<Mac;i++)

      {

                        MacAllocationArray[i]=StrAll();

                        //MacAllocationArray[i]->StartTime=0;

                        //MacAllocationArray[i]->EndTime=0;

      }

      //--------------------for storing sequence

      //printf(" \n\nInitialization Done ");

      //getch();

      for(i=0;i<Task;i++)

      {

                         j=(int)ReadFile(sp);

                         push(j);

      }

      //Sequence storing ends here---------------

      //-------------------file input for machine cost

      for(i=0;i<Mac;i++)

      {

              for(j=0;j<Task;j++)

              {

                                 *(*(MacCostArray+j)+i)=ReadFile(fp);

              }





      }

      //input ends here--------------------

      //------------------Initializing the path cost matrix

      PCM = (int**)malloc(sizeof(int)*Task);

      for(i=0;i<Task;i++)

      {

                         PCM[i]=(int*)malloc(sizeof(int)*Task);

      }



      //Input for Path Cost Matrix-------------------------

      for(i=0;i<Task;i++)

      {

                         for(j=0;j<Task;j++)

                         {

                                          *(*(PCM+i)+j)=(int)ReadFile(fp);

                         }



      }

      // File reading ends here

      //Calculation of Average Machine Cost and printing

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



      //printf("\n\n-------------------------------------\n\n");

      for(i=0;i<Task/2;i++)

      {

                           j=G_stack[i];

                           G_stack[i]=G_stack[G_tail-1-i];

                           G_stack[G_tail-1-i]=j;

      }

      //printf("\n\nBefore going to  PRocAlloc");

      //getch();

      ProcAlloc();

      //printf("\n\nPrinting Test without dependencies");

      //getch();

      int makespan=0;

      Machine *temp5;

      for(i=0;i<Mac;i++)

      {                // printf("\n\nMachine : %d :\n",i);

                        temp5=MacAllocationArray[i];

                        while (temp5!=NULL)

                        {

                           //   printf("Task No: %d \tStartTime :%f\tEndtime : %f",temp5->TaskNo,temp5->StartTime,temp5->EndTime);

                              if(makespan<temp5->EndTime)

                              makespan=temp5->EndTime;

                              temp5=temp5->Next;

                              //printf("\n");

                        }

      }

      //---------------------for makespan----------------------------



                                  // printf("%d",makespan);



                                              int r,s;

                                              r=makespan;

                                              FILE *MC;

                                              MC=fopen("MakespanFA.txt","w");

                                              if(r>9)

                                              {

                                              int ct=0;

                                              char ftemp[100];

                                              while(r>0)

                                              {

                                              s=r%10;

                                              s=(char)s+'0';

                                              ftemp[ct]=s;

                       //fputc(s,p);

                                              r=r/10;

                                              ct++;

                                              }

                                              while(ct!=0)

                                              {

                                              fputc(ftemp[--ct],MC);

                                              }

                                              //fputc(',',MC);

                                              //continue;

                                              }

                                              /*r=(char)r+'0';

                                              fputc(r,MC);

                                              fputc(',',MC);*/

      //---------------------for makespan----------------------------

      //getch(); */

      fclose(fp);

      fclose(MC);

      fclose(sp);



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

     while(G_tail>0)

     {

                    CurrentTask=Stack_read();

                    pop();

                    PrecedenceCheck();

     }

}

void PrecedenceCheck()

{

     //printf("\\nPRecedenceCheck())");

     //getch();

     int j=0,i;

     int CurrentMachine;

     float least;

     for(i=0;i<Task;i++)

     {

             if(*(*(PCM+i)+CurrentTask)>0)

             Precedence[j++]=i;



     }

     //printf("\n\nPrecedence For Current Machine\n\n");

     //for(i=0;i<j;i++)

     //printf("%d",Precedence[i]);

     //getch();

     Allocate(j);

}

void Allocate(int endindex) //to Allocate to a machine

{

     float StartVal,LeastMacArray[100],MaxArray[100],mm;

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

     if(endindex==1)

     {

         for(int i=0;i<Mac;i++)

         {

                            StartVal=MachineSearch(i,TimeStamp(Precedence[0],i));

                            LeastMacArray[i]=StartVal+*(*(MacCostArray+CurrentTask)+i);

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

                         StartVal=MachineSearch(i,TimeStamp(Precedence[k],i));

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

