#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
   char buffer[30] ;
   char *record,*line;
   int i=0,j=0;
	int temp1=0,temp2=0,temp3=0;
   int mat[10][3];
   FILE *fstream = fopen("journal_log.txt","r");
   if(fstream == NULL)
   {
      printf("\n file opening failed ");
      return -1 ;
   }
for(i=0;i<10;i++)
	{
	fscanf(fstream,"%d %d %d",&temp1,&temp2,&temp3);
    	mat[i][j] = temp1;
	mat[i][j+1]=temp2;
	mat[i][j+2]=temp3;
	}
for(i=0;i<10;i++){
    for(j=0;j<3;j++){
   printf("%d", mat[i][j]);
    }
printf("\n");
}

   return 0 ;
 }
