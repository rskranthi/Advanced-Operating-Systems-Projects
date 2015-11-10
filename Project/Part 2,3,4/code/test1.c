/* Preprocessor directives */
#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE(x)  (sizeof(x)/sizeof(*(x)))
int main()
{
int i,j;
int array[10][3];
const char filename[] = "journal_log.txt";
   /*
    * Open the file.
    */
   FILE *file = fopen(filename, "r");
   if ( file )
   {
      int array[10][10];
      size_t i, j, k;
      char buffer[BUFSIZ], *ptr;
      /*
       * Read each line from the file.
       */
      for ( i = 0; fgets(buffer, sizeof buffer, file); ++i )
      {
         /*
          * Parse the comma-separated values from each line into 'array'.
          */
         for ( j = 0, ptr = buffer; j < ARRAYSIZE(*array); ++j, ++ptr )
         {
            array[i][j] = (int)strtol(ptr, &ptr, 10);
         }
      }
      fclose(file);
}
for(i=0;i<10;i++)
{
for(j=0;j<3;j++)
{
printf("%d",array[i][j]);
}
}
}
