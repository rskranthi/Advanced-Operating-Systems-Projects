#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include "global_variables.h"
int locking=0;
outcome_record_nonce_id=1001;
void READ_FROM_LOG()
{
    FILE *myFile;
    myFile = fopen("journal_log.txt", "r");

    //read file into array
    int numberArray[30];
    int numberArray2[30];
    int i,j,k=0;

    for (i = 0; i < 30; i++)
    {
        fscanf(myFile, "%d,", &numberArray[i]);
    }

    for(i=0;i<10;i++) //initialising to 0 to avoid garbage values
    {
	for(j=0;j<3;j++)
	{
	data_record[i][j]=0;
	outcome_temp[i][j]=0;
	}
     }

      for(i=0;i<10;i++) //initialising to 0 to avoid garbage values
    {
        for(j=0;j<3;j++)
        {
        data_record[i][j]=numberArray[k];
        outcome_temp[i][j]=numberArray[k];
	k++;
        }
     }
	fclose(myFile);;

 myFile = fopen("outcome_record.txt", "r");

    //read file into array
    k=0;

    for (i = 0; i < 30; i++)
    {
        fscanf(myFile, "%d,", &numberArray2[i]);
    }

    for(i=0;i<10;i++) //initialising to 0 to avoid garbage values
    {
        for(j=0;j<2;j++)
        {
        outcome_record[i][j]=0;
        }
     }

      for(i=0;i<10;i++) //initialising to 0 to avoid garbage values
    {
        for(j=0;j<2;j++)
        {
        outcome_record[i][j]=numberArray2[k];
        k++;
        }
     }
        fclose(myFile);



/*
    for (i = 0; i < 16; i++)
    {
        printf("Number is: %d\n\n", numberArray[i]);
    }
*/
}
int WRITE_TO_LOG()	//WRITING TO A LOG FILE FOR PERSISTENCE ACROSS CRASH
{
FILE *log_file;
FILE *outcome_file;
int i,j;
log_file =fopen("journal_log.txt", "w+");
outcome_file=fopen("outcome_record.txt","w+");
if (!log_file)
return 1;
if(!outcome_file)
return 1;

for(i=0;i<commit_pointer;i++)
{
for(j=0;j<3;j++)
   {
   fprintf(log_file,"%d,",outcome_temp[i][j]);
   }
fprintf(log_file,"\n");
}

                fclose(log_file);
for(i=0;i<commit_pointer;i++)
{
for(j=0;j<2;j++)
	{
	fprintf(outcome_file,"%d,",outcome_record[i][j]);
	}
fprintf(outcome_file,"\n");
}
fclose(outcome_file);

                return  0;
        }


void GET_OUTCOME_RECORD()//method to print present outcome record contents
{
		        printf("PENDING=0,COMMITTED=1,ABORTED=-1\n");
                printf("Outcome record values are:\n");
                printf("outcome_record_id outcome_record_status \n");
                int count=0;
                int iter1=0,iter2=0;
                for(iter1=0;iter1<10;iter1++)
                {
                        printf("%d \t\t\t",outcome_record[iter1][0]);
                        printf("%d",outcome_record[iter1][1]);
                        count++;
                                if(count==1)
                                {
                                        printf("\n");
                                        count=0;
                                }
                }
}
void COMMIT(id) //procedure for Commit post a value is written to temp outcome record,this copies 
				//values to permanent outcome record which can be used for reading values
{
        int i=0,j=0,k=0;
	int caller_id=0,new_value;
	char data_id;
	data_record[commit_pointer][0]=outcome_temp[outcome_pointer][0];
    data_record[commit_pointer][1]=outcome_temp[outcome_pointer][1];
    data_record[commit_pointer][2]=outcome_temp[outcome_pointer][2];
	printf("data record committed as below:\n");
	printf("%c\t%d\t %d",data_record[commit_pointer][0],data_record[commit_pointer][1],data_record[commit_pointer][2]);	
    if(outcome_record[commit_pointer][0]==id)
        outcome_record[commit_pointer][1]=1;
	k++;
	data_pointer++;
	outcome_pointer++;
	commit_pointer++;
	printf("\nTRANSACTION COMMITTED\n");

return;
}

void ABORT(id)   //Procedure for Abort
{
int i=0;
for(i=0;i<10;i++)
{
        if(outcome_record[i][0]==id)
        {
			outcome_record[i][1]=-1;
			printf("TRANSACTION ID:%d IS ABORTED\n",id);
		}
		else
			printf("INVALID TRANSACTION ID");		
}
return;
}


int NEW_ACTION(id) //procudure for new action which is called by READ and WRITE methods to create an action id 
{
pthread_mutex_trylock(&new_action_lock);
id++;
pthread_mutex_unlock(&new_action_lock);
int j=0;
outcome_record[new_action_pointer][j]=id;
outcome_record[new_action_pointer][j+1]=PENDING;
printf("NEW_ACTION CREATED:%d\t%d and is in PENDING STATE:\n",outcome_record[new_action_pointer][j],outcome_record[new_action_pointer][j+1]);
new_action_pointer++;
printf("\n");
return id;
}


void* single_main(void *p)
{
int* thread_num = (int*)(p);

printf("thread number %d", *thread_num);

int caller_id,read_value,new_value,abort_id;
char operation,iterator,commit_boolean;
	
do
{
printf("\n a.READ_CURRENT_VALUE \n b.WRITE_NEW_VALUE\n c.NEW_ACTION \n d.COMMIT \n e.ABORT \n f.FAULTY_WRITE \n ANYTHING ELSE RETURNS ERROR \n");
printf("\nenter the transaction you want to perform from above options for thread %d:\n",*thread_num);
scanf(" %c",&operation);
              switch(operation)
                {
            case 'a':   printf("\nENTER THE DATA_ID for thread %d\n",*thread_num);
			scanf(" %c",&data_id);
			printf("\ndata id you entered is:%c for thread %d\n",data_id,*thread_num);

			printf("\nREADING CURRENT VALUE  for thread %d:",*thread_num);
                    //    caller_id=NEW_ACTION(outcome_record_nonce_id);		

                        read_value=READ_CURRENT_VALUE(data_id);
					    if(read_value==-1)
						       printf("no value found");
				    	else
								printf("READ_CURRENT_VALUE=%d",read_value);
								printf("\n");
				    	break;
		
			case 'b':  //	pthread_mutex_lock(&lock);
				/*	printf("\nENTER THE DATA_ID for thread %d\n",*thread_num);
					scanf(" %c",&data_id);
					printf("data id you entered is:%c\n for thread %d\n",data_id,*thread_num);

					 printf("ENTER THE VALUE TO WRITE for thread %d\n:",*thread_num);
				    	scanf("%d",&new_value);
				*/
					if( pthread_mutex_trylock(&lock)==0)
					{
					
					 printf("\nENTER THE DATA_ID for thread %d\n",*thread_num);
                                        scanf(" %c",&data_id);
                                        printf("\n data id you entered is:%c for thread %d\n",data_id,*thread_num);

                                         printf("\nENTER THE VALUE TO WRITE for thread %d\n:",*thread_num);
                                        scanf("%d",&new_value);

				    	printf("\nWRITING NEW VALUE \n");
				    	caller_id=NEW_ACTION(outcome_record_nonce_id);
						//printf("caller_id is %d",caller_id);
                       			 WRITE_NEW_VALUE(data_id,new_value,caller_id,*thread_num);
						int sleep_time1=60;
						printf("Thread %d is sleeping for %d time",*thread_num,sleep_time1);
                                                sleep(sleep_time1);
						printf("\nDO YOU WANT TO COMMIT THIS VALUE:Y/N for  thread %d:\n",*thread_num);
						scanf(" %c",&commit_boolean);
						if(commit_boolean=='Y')
						COMMIT(caller_id);
				//		int sleep_time1=30;
					//	printf("Thread %d is sleeping for %d time",*thread_num,sleep_time1);
					//	sleep(sleep_time1);
						outcome_record_nonce_id++;
						WRITE_TO_LOG();
						 pthread_mutex_unlock(&lock);
					}
					else
					{
					printf("\nAnother Thread is writing,Hence sleepin thread %d\n ",*thread_num);
					sleep(70);
					while(!pthread_mutex_trylock(&lock))
					{
					printf("\nENTER THE DATA_ID for thread %d\n",*thread_num);
                                        scanf(" %c",&data_id);
                                        printf("\n data id you entered is:%c for thread %d\n",data_id,*thread_num);

                                         printf("\nENTER THE VALUE TO WRITE for thread %d\n:",*thread_num);
                                        scanf("%d",&new_value);

                                        printf("\nWRITING NEW VALUE \n");
                                        caller_id=NEW_ACTION(outcome_record_nonce_id);
                                                //printf("caller_id is %d",caller_id);
                                         WRITE_NEW_VALUE(data_id,new_value,caller_id,*thread_num);
                                                printf("\nDO YOU WANT TO COMMIT THIS VALUE:Y/N for  thread %d:\n",*thread_num);
                                                scanf(" %c",&commit_boolean);
                                                if(commit_boolean=='Y')
                                                COMMIT(caller_id);

                                                outcome_record_nonce_id++;
						 WRITE_TO_LOG();
					//	pthread_mutex_unlock(&lock);
	
						sleep(10);//to ensure that there is no deadlock
						break;
					}
					 pthread_mutex_unlock(&lock);
					}
				//		pthread_mutex_unlock(&lock);
						break;
			case 'c': 	printf("Only READ_CURRENT_VALUE or WRITE_NEW_VALUE can create a NEW_ACTION, please exit and start again\n");
						break;
			 case 'd' :	  printf("ENTER THE TRANSACTION ID TO BE COMMITTED:\n");
                                                scanf("%d",&abort_id);
                                                COMMIT(abort_id);
			case 'e': 	printf("\n Enter the transaction id you want to ABORT for thread %d:\n",*thread_num);
						scanf("%d",&abort_id);
						ABORT(abort_id);
						break;
			case 'f':       if( pthread_mutex_trylock(&lock)==0)
                                        {
                                         printf("\nENTER THE DATA_ID for thread %d\n",*thread_num);
                                        scanf(" %c",&data_id);
                                        printf("\n data id you entered is:%c for thread %d\n",data_id,*thread_num);

                                         printf("\nENTER THE VALUE TO WRITE for thread %d\n:",*thread_num);
                                        scanf("%d",&new_value);

                                        printf("\nWRITING NEW VALUE \n");
                                        caller_id=NEW_ACTION(outcome_record_nonce_id);
                                                //printf("caller_id is %d",caller_id);
                                         FAULTY_WRITE(data_id,new_value,caller_id,*thread_num);
                                                printf("\nDO YOU WANT TO COMMIT THIS VALUE:Y/N for  thread %d:\n",*thread_num);
                                                scanf(" %c",&commit_boolean);
                                                if(commit_boolean=='Y')
                                                COMMIT(caller_id);
                                                int sleep_time1=30;
                                                printf("Thread %d is sleeping for %d time",*thread_num,sleep_time1);
                                                sleep(sleep_time1);
                                                outcome_record_nonce_id++;
						 int canceller=0;
                                        pthread_t self;
                                        self = pthread_self();
                                        printf("Thread %d has faulted\n",*thread_num);
                                        canceller=pthread_cancel(self);
                                        printf("Thread %d has faulted\n",*thread_num);

                                         WRITE_TO_LOG();  //CRASH OCCURS BEFORE THIS
                                                pthread_mutex_unlock(&lock);
                                                sleep(10);//to ensure that there is no deadlock

                                                WRITE_TO_LOG();
                                                 pthread_mutex_unlock(&lock);
                                        }
                                        else
                                        {
                                        printf("\nAnother Thread is writing,Hence sleepin thread %d\n ",*thread_num);
                                        sleep(30);
                                        while(!pthread_mutex_trylock(&lock))
                                        {
                                        printf("\nENTER THE DATA_ID for thread %d\n",*thread_num);
                                        scanf(" %c",&data_id);
                                        printf("\n data id you entered is:%c for thread %d\n",data_id,*thread_num);

                                         printf("\nENTER THE VALUE TO WRITE for thread %d\n:",*thread_num);
                                        scanf("%d",&new_value);
                                        printf("\nWRITING NEW VALUE \n");
                                        caller_id=NEW_ACTION(outcome_record_nonce_id);
					FAULTY_WRITE(data_id,new_value,caller_id,*thread_num);
                                         printf("\nDO YOU WANT TO COMMIT THIS VALUE:Y/N for  thread %d:\n",*thread_num);
                                                scanf(" %c",&commit_boolean);
                                                if(commit_boolean=='Y')
                                                COMMIT(caller_id);

                                                outcome_record_nonce_id++;
						int canceller=0;
                                        pthread_t self;
                                        self = pthread_self();
                                        printf("Thread %d has faulted\n",*thread_num);
                                        canceller=pthread_cancel(self);
                                        printf("Thread %d has faulted\n",*thread_num);
                                                 WRITE_TO_LOG();
                                                pthread_mutex_unlock(&lock);
                                                sleep(10);//to ensure that there is no deadlock
                                        }
                                        }

					break;	
			default : 	printf("INVALID OPTION, PLEASE INPUT CORRECT OPERATION ID:");
						break;
            	                } 
            	              
printf("\n");
printf("\ndo you  wish to continue the thread %d Y/N, Enter Y or N:\n",*thread_num);
scanf(" %c",&iterator);
}while(iterator=='Y');
}
