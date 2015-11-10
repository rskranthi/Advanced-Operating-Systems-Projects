#include<stdio.h>
int main()
{
FILE *ptr_file;
int i,j,count=0;
ptr_file =fopen("output.txt", "w");
if (!ptr_file)
return 1;

int yourvalue[3][3]={1,2,3,4,5,6,7,8,9};
for(i=0;i<3;i++)
{
for(j=0;j<3;j++)
   { 
   fprintf(ptr_file,"%d,",yourvalue[i][j]);
   } 
fprintf(ptr_file,"\n");
}

		fclose(ptr_file);

		return  0;
	}
