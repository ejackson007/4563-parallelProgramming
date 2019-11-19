import multiprocessing as mp
import os
import numpy
import pprint

def addArray(arr):
    summation = 0
    for i in arr:
        summation += i
    
    return summation

a = numpy.arange(640)
summation = numpy.arange(4)
for n in range(640):
    a[n] = n

#split array into pieces
a = numpy.array_split(a, 12)

pool = mp.Pool(processes=4)
summation = pool.map(addArray, a)
arraySum = numpy.sum(summation)

# sum = addArray(a)
print(f"Sum array is {summation}\n")
print(f"Summation of the array is {arraySum}\n")