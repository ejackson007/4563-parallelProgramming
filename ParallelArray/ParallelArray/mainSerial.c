//
//  main.c
//  ParallelArray
//
//  Created by Evan Jackson on 10/14/19.
//  Copyright © 2019 Evan Jackson. All rights reserved.
//

#include <stdio.h>

#define SIZE 640000

int main(int argc, const char * argv[]) {
    // insert code here...
    int a[SIZE];
    long int sum = 0;
    
    for(int i = 0; i < SIZE; i++){
        a[i] = i + 1;
    }
    
    for(int i = 0; i < SIZE; i++){
        sum = sum + a[i];
    }
    
    printf("The sum is %li\n", sum);
    return 0;
}
