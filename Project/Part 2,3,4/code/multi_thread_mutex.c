#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include "write.h"
#include "read.h"
#include "JSM.h"
#include "global_variables.h"
ROWS=10,COLS=3;
PENDING=0,COMMITTED=1,ABORTED=-1; //Initializing variables as its easy to deal in numbers
commit_pointer=0;//outcome records for temp and committed values
outcome_pointer=0,data_pointer=0,new_action_pointer=0;//pointers to handle the above declared arrays
lock_variable=0;

int main()
{
    int i = 0;
    int err1,err2;
	READ_FROM_LOG();

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

   
    int t1=1;
  //      err = pthread_create(&(tid[i]), NULL, &acquireLock, NULL);
	err1 = pthread_create(&(tid[0]), NULL,&single_main,&t1);
        if (err1 != 0)
            printf("\ncan't create thread :[%s]", strerror(err1));
        
     int t2=2;
	err2 = pthread_create(&(tid[1]), NULL,&single_main,&t2);
        if (err2 != 0)
            printf("\ncan't create thread :[%s]", strerror(err2));
    pthread_join(tid[0],NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&new_action_lock);
    return 0;
}
