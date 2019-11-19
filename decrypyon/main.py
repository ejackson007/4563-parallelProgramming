import multiprocessing as mp
import os
import numpy
import pprint

def addArray(arr):
    summation = 0
    for i in arr:
        summation += i
    
    return summation

def flipArray(arr):
    arr = numpy.flip(arr)
    return arr

a = numpy.arange(640)
summation = numpy.arange(4)
for n in range(640):
    a[n] = n

#split array into pieces
a = numpy.array_split(a, 64)

pool = mp.Pool(processes=4)
summation = pool.map(addArray, a)
flipped = pool.map(flipArray, a)
arraySum = numpy.sum(summation)

# sum = addArray(a)
print(f"Sum array is {summation}\n")
print(f"Flipped array is {flipped}\n")
#print(f"Summation of the array is {arraySum}\n")