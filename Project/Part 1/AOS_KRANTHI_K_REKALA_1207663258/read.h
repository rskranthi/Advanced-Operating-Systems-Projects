int data_record[100][3],outcome_record[100][2]; // Arrays to hold the data and outcome records
char data_id;
int ROWS=10,COLS=3;
int PENDING=0,COMMITTED=1,ABORTED=-1; //Initializing variables as its easy to deal in numbers
int outcome_temp[100][3],commit_pointer=0;//outcome records for temp and committed values
int outcome_pointer=0,data_pointer=0,new_action_pointer=0;//pointers to handle the above declared arrays

int READ_CURRENT_VALUE(char data_id)//Procedure to Read a Value using data_id
{
int possible_callers[25];//Array to collect the possible caller_ids 
int possible_values[25],k=0,l=0;//Array to collect the possible values for above caller_ids
int i,j,value=-1;				
for(i=0;i<10;i++)
	{
	for(j=0;j<3;j++)
		{
		if(data_record[i][j]==data_id)
			{	
			possible_callers[k]=  data_record[i][j+1];
			possible_values[l] = data_record[i][j+2];
			k++;l++;
			}
		}


	}	
k=0;
	for(i=0;i<10;i++)
		{
		for(j=0;j<2;j++)
			{
			if((possible_callers[k]==outcome_record[i][j]) && (outcome_record[i][j+1]==1))//loop to overwrite the value until latest committed value is found
				{
				 value=possible_values[k];
					k++;
				}
			}
		}
	

return value;		
}

