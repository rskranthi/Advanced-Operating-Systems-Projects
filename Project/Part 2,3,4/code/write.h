#include "global_variables.h"
#include<stdio.h>

int WRITE_NEW_VALUE(data_id,new_value,id,num)
{
long int i=0,j=0;
printf("\n Thread %d :entered write value for id: %d\n",num,id);
printf("\n Thread %d entered write new value for data_id: %c\n",num,data_id);
printf("\n Thread %d :entered write new value: %d",num,new_value);
threadid=pthread_self();
for(i=0;i<10;i++)

        {
        for(j=0;j<2;j++)
                {
                if((outcome_record[i][j]==id && outcome_record[i][j+1]==PENDING))//loop to write the values to temporary outcome record
                        {
                        outcome_temp[outcome_pointer][0]=data_id;
                        outcome_temp[outcome_pointer][1]=id;
                        outcome_temp[outcome_pointer][2]=new_value;

                        }
                }
        }
/*
if(pthread_equal(threadid,tid[0]))
{
printf("thread 1 is sleeping");
sleep(5);
}
 pthread_mutex_unlock(&lock);
lock_variable=0;
*/
return 0;
}

int FAULTY_WRITE(data_id,new_value,id,num)
{
long int i=0,j=0;
printf("\n Thread %d :entered write value for id: %d\n",num,id);
printf("\n Thread %d entered write new value for data_id: %c\n",num,data_id);
printf("\n Thread %d :entered write new value: %d",num,new_value);
threadid=pthread_self();
for(i=0;i<10;i++)

        {
        for(j=0;j<2;j++)
                {
                if((outcome_record[i][j]==id && outcome_record[i][j+1]==PENDING))//loop to write the values to temporary outcome record
                        {
                        outcome_temp[outcome_pointer][0]=data_id;
                        outcome_temp[outcome_pointer][1]=id;
                        outcome_temp[outcome_pointer][2]=new_value;

                        }
                }
        }
/*if(pthread_equal(threadid,tid[0]))
{
printf("thread 1 is sleeping");
sleep(10);
}*/
// pthread_mutex_unlock(&lock);
lock_variable=0;
//
//}
//}

if(pthread_equal(threadid,tid[0]))
{
printf("thread 1 is sleeping");
sleep(5);
}
 pthread_mutex_unlock(&lock);
lock_variable=0;

return 0;
}

