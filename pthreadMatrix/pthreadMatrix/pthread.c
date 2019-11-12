//**************************************************************

// Assignment #4

// Name: Evan Jackson

// Parallel Programming Date: Date of Submission (11/12/2019)

//***************************************************************

// This goal of the program is to take 2 arrays of length
// 1,000,000, and create 4 more arrays, also of size 1,000,000
// holding the sum, difference, product, and quotient of the
// other 2 arrays respecitvely. This take is done in parallel.
// with each thread handeling one of the functions.

// TO RUN IN STAMPEDE:
// gcc pthreads.exe -o JacksonA4YesThreads.c -lpthreads
// sbatch pthreadsScript
// (result will show 5 times for 5 runs)

//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define LENGTH 1000000
#define THREADCNT 4
//define struct with global variables
typedef struct {
    int *a;
    int *b;
    int *addition;
    int *subtraction;
    int *multiplication;
    int *division;
} ARRAY;
pthread_t threads[THREADCNT];// define threads
ARRAY mil;//million size array

void * addArray(void * arg){
    //create local array
    int * addition = (int *) malloc(LENGTH * sizeof(int));
    int i;
    int *x, *y;
    //create its own pointer so that it is not accessing
    //at the same time
    x = mil.a;
    y = mil.b;
    
    //add array into local array
    for(i = 0; i < LENGTH; i++)
        addition[i] = x[i] + y[i];
    
    //set global pointer to array that was just created
    mil.addition = addition;
    pthread_exit((void*) 0);
}

void * subArray(void * arg){
    int * subtraction = (int *) malloc(LENGTH * sizeof(int));
    int i;
    int *x, *y;
    x = mil.a;
    y = mil.b;
    
    for(i = 0; i < LENGTH; i++)
        subtraction[i] = x[i] - y[i];
    
    mil.subtraction = subtraction;
    pthread_exit((void*) 0);
}

void * multpArray(void * arg){
    int * multiplication = (int *) malloc(LENGTH * sizeof(int));
    int i;
    int *x, *y;
    x = mil.a;
    y = mil.b;
    
    for(i = 0; i < LENGTH; i++)
        multiplication[i] = x[i] * y[i];
    
    mil.multiplication = multiplication;
    pthread_exit((void*) 0);
}

void * divArray(void * arg){
    int * division = (int *) malloc(LENGTH * sizeof(int));
    int i;
    int *x, *y;
    x = mil.a;
    y = mil.b;
    
    for(i = 0; i < LENGTH; i++)
        division[i] = x[i] / y[i];
    
    mil.division = division;
    pthread_exit((void*) 0);
}


int main(int argc, const char * argv[]) {
    int i;
    //create attribute & status
    pthread_attr_t attr;
    void * status;
    
    struct timeval start, end;
    
    mil.a = (int *) malloc(LENGTH * sizeof(int));
    mil.b = (int *) malloc(LENGTH * sizeof(int));
    //fill arrays a & b
    for(i = 0; i < LENGTH; i++){
        mil.a[i] = 1;
        mil.b[i] = 2;
    }
    //Create and send threads
    pthread_attr_init(&attr);
    //arrays set as joinable to that they can be organized later
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    gettimeofday(&start, NULL);
    
    //send each thread to their own routine. No arguments are needed
    //since it is creating a local version and then writing it to
    //global version.
    pthread_create(&threads[0], &attr, addArray, (void*) 0);
    pthread_create(&threads[1], &attr, subArray, (void*) 0);
    pthread_create(&threads[2], &attr, multpArray, (void*) 0);
    pthread_create(&threads[3], &attr, divArray, (void*) 0);
    
    pthread_attr_destroy(&attr);
    
    //wait for processes to all be finished before continuing
    for(i = 0; i < THREADCNT; i++)
        pthread_join(threads[i], &status);
    
    gettimeofday(&end, NULL);
    
    //Testing
//    for(i = 0; i < 10; i++)
//        printf("Addition [%d] is %d\n", i, mil.addition[i]);
//    for(i = 0; i < 10; i++)
//        printf("Subtraction [%d] is %d\n", i, mil.subtraction[i]);
//    for(i = 0; i < 10; i++)
//        printf("Multiplication [%d] is %d\n", i, mil.multiplication[i]);
//    for(i = 0; i < 10; i++)
//        printf("Division [%d] is %d\n", i, mil.division[i]);
    
    //print timing
    printf("%ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
    
    pthread_exit(NULL);
}
