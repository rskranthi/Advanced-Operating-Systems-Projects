WRITE_NEW_VALUE(data_id,new_value,id)
{
int i=0,j=0;
printf("entered write value for id: %d\n",id);
printf("entered write new value for data_id: %c\n",data_id);
printf("entered write new value: %d",new_value);
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

}
