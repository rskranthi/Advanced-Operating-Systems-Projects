#include<pthread.h>
int data_record[100][3],outcome_record[100][2]; // Arrays to hold the data and outcome records
char data_id;
int ROWS,COLS;
int PENDING,COMMITTED,ABORTED; //Initializing variables as its easy to deal in numbers
int outcome_temp[100][3],commit_pointer;//outcome records for temp and committed values
int outcome_pointer,data_pointer,new_action_pointer;//pointers to handle the above declared arrays
int lock_variable;
pthread_t tid[2];
pthread_mutex_t lock;
pthread_mutex_t new_action_lock;
pthread_t threadid;
pthread_t cancel_thread;
