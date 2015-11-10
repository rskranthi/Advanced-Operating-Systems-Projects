#include<stdio.h>
#include<string.h>
#include "read.h"
#include "write.h"

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

id++;
int j=0;
outcome_record[new_action_pointer][j]=id;
outcome_record[new_action_pointer][j+1]=PENDING;
printf("NEW_ACTION CREATED:%d%d",outcome_record[new_action_pointer][j],outcome_record[new_action_pointer][j+1]);
new_action_pointer++;
printf("\n");
return id;
}


int main()
{
int outcome_record_nonce_id=1001;// id to initialise the transaction ids, this will be incremented everytime a new action is created
int caller_id,read_value,new_value,abort_id;
char operation,iterator,commit_boolean;
READ_CURRENT_VALUE(data_id);
	
do
{
printf("\nENTER THE DATA_ID\n");
scanf(" %c",&data_id);
printf("data id you entered is:%c\n",data_id);
printf("\n a.READ_CURRENT_VALUE \n b.WRITE_NEW_VALUE\n c.NEW_ACTION \n d.COMMIT \n e.ABORT \n f.GET_OUTCOME_RECORDS\n g.COMMIT \n");
printf("enter the transaction you want to perform from above options:\n");
scanf(" %c",&operation);

              switch(operation)
                {
            case 'a':   printf("READING CURRENT VALUE:\n");
                        caller_id=NEW_ACTION(outcome_record_nonce_id);		
                        read_value=READ_CURRENT_VALUE(data_id);
					    if(read_value==-1)
						       printf("no value found");
				    	else
								printf("READ_CURRENT_VALUE=%d",read_value);
				    	break;
		
			case 'b':   printf("ENTER THE VALUE TO WRITE:");
				    	scanf("%d",&new_value);
				    	printf("WRITING NEW VALUE \n");
				    	caller_id=NEW_ACTION(outcome_record_nonce_id);
						printf("caller_id is %d",caller_id);
                        WRITE_NEW_VALUE(data_id,new_value,caller_id);
						printf("DO YOU WANT TO COMMIT THIS VALUE:Y/N");
						scanf(" %c",&commit_boolean);
						if(commit_boolean=='Y')
						COMMIT(caller_id);

						outcome_record_nonce_id++;
						break;
			case 'c': 	printf("Only READ_CURRENT_VALUE or WRITE_NEW_VALUE can create a NEW_ACTION, please exit and start again\n");
						break;
			case 'd': 	printf("Only post using WRITE_NEW_VALUE method you will be asked to COMMIT or not,please exit and start again\n");
						break;
			case 'e': 	printf("Enter the transaction id you want to ABORT");
						scanf("%d",&abort_id);
						ABORT(abort_id);
						break;
			case 'f' : 	GET_OUTCOME_RECORD();
						break;
			case 'g' :  printf("ENTER THE TRANSACTION ID TO BE COMMITTED:\n");
						scanf("%d",&abort_id);
						COMMIT(abort_id);
						break;
						
			default : 	printf("INVALID OPTION, PLEASE INPUT CORRECT OPERATION ID:");
						break;
            	                } 
            	                
printf("\n");
printf("do you  wish to continue Y/N, Enter Y or N:");
scanf(" %c",&iterator);
}while(iterator=='Y');
}
