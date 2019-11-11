//**************************************************************

// Assignment #4

// Name: Evan Jackson

// Parallel Programming Date: Date of Submission (11/12/2019)

//***************************************************************

// This goal of the program is to take 2 arrays of length
// 1,000,000, and create 4 more arrays, also of size 1,000,000
// holding the sum, difference, product, and quotient of the
// other 2 arrays respecitvely. This take is done in serial.

// TO RUN IN STAMPEDE:
// mpicc serial.exe -o JacksonA4NoThreads.c
// sbatch serialScript
// (result will show 5 times for 5 runs)

//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define LENGTH 1000000
int *a;
int *b;

int * addArray(){
    //create sum array
    int * addition = (int *) malloc(LENGTH * sizeof(int));
    int i;
    
    for(i = 0; i < LENGTH; i++)
        addition[i] = a[i] + b[i];
    
    return addition;
}

int * subArray(){
    //create difference array
    int * subtraction = (int *) malloc(LENGTH * sizeof(int));
    int i;
    
    for(i = 0; i < LENGTH; i++)
        subtraction[i] = a[i] - b[i];
    
    return subtraction;
}

int * multpArray(){
    //create product array
    int * multiplication = (int *) malloc(LENGTH * sizeof(int));
    int i;
    
    for(i = 0; i < LENGTH; i++)
        multiplication[i] = a[i] * b[i];
    
    return multiplication;
}

int * divArray(){
    //create quotient array
    int * division = (int *) malloc(LENGTH * sizeof(int));
    int i;
    
    for(i = 0; i < LENGTH; i++)
        division[i] = a[i] / b[i];
    
    return division;
}


int main(int argc, const char * argv[]) {
    int i;
    
    struct timeval start, end;
    
    //create 2 arrays of size 1,000,000
    a = (int *) malloc(LENGTH * sizeof(int));
    b = (int *) malloc(LENGTH * sizeof(int));
    //fill arrays a & b
    for(i = 0; i < LENGTH; i++){
        a[i] = 1;
        b[i] = 2;
    }
    
    gettimeofday(&start, NULL);
    //call each function and set pointer to address
    int * addition = addArray();
    int * subtraction = subArray();
    int * multiplication = multpArray();
    int * division = divArray();
    
    gettimeofday(&end, NULL);
   
    //Testing
//    for(i = 0; i < 10; i++)
//        printf("Addition [%d] is %d\n", i, addition[i]);
//    for(i = 0; i < 10; i++)
//        printf("Subtraction [%d] is %d\n", i, subtraction[i]);
//    for(i = 0; i < 10; i++)
//        printf("Multiplication [%d] is %d\n", i, multiplication[i]);
//    for(i = 0; i < 10; i++)
//        printf("Division [%d] is %d\n", i, division[i]);
    
    //print timing
    printf("%ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
    return 0;
}
