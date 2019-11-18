//
//  main.c
//  pthreadICH
//
//  Created by Evan Jackson on 11/14/19.
//  Copyright © 2019 Evan Jackson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define SIZE 800
#define THREADCNT 8

int * a;
int * b;
int * threadSums;
int * globalTrack;
int globalSum;
pthread_t threads[THREADCNT];
pthread_mutex_t mutex;


void * addLocal(int arg){
    int localSum = 0;
    int i;
    for(i = arg; i < (arg * 100)+100; i++){
        localSum = (a[i] * b[i]) + localSum;
    }
    pthread_mutex_lock(&mutex);
    //for testing
    //printf("Thread %d local sum: %d\n", i, localSum);
    //update global
    globalSum += localSum;
    //save local sum
    threadSums[arg] = localSum;
    //save current global sum
    globalTrack[arg] = globalSum;
    pthread_mutex_unlock(&mutex);
    pthread_exit((void*) 0);
}

int main(int argc, const char * argv[]) {
    //get pthreads ready and global
    globalSum = 0;
    pthread_attr_t attr;
    void * status;
    //set sixe for localsums and globaltrack
    globalTrack = (int *) malloc(THREADCNT * sizeof(int));
    threadSums = (int *) malloc(THREADCNT * sizeof(int));
    //define arrays, and first values
    a = (int *) malloc(SIZE * sizeof(int));
    a[0] = 0;
    b = (int *) malloc(SIZE * sizeof(int));
    b[0] = 1;
    int i;
    
    //Fill array with values
    for(i = 1; i < SIZE; i++){
        a[i] = a[i-1] + 2;
        b[i] = b[i-1] + 2;
    }
    
    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for(i = 0; i < THREADCNT; i++){
        pthread_create(&threads[0], &attr, addLocal, (void*)i);
    }
    
    //sync before printing
    for(i = 0; i < THREADCNT; i++){
        pthread_join(threads[i], &status);
    }
    
    pthread_attr_destroy(&attr);
    
    //print answer
    for(i = 0; i < THREADCNT; i++){
        printf("Pthreads %d - did %d to %d | Local Sum = %d | Global Sum = %d\n", i, i*100,
               i*100 + 99, threadSums[i], globalTrack[i]);
    }
    printf("Final global sum is: %d", globalSum);
    pthread_exit(NULL);
}
