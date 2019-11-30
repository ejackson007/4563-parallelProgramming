import multiprocessing as mp
import os
import numpy
import enchant
import time

f = open("hiddenMeaning.txt", 'r')
o = open("decoded.txt", 'w')
message = f.read()
alphaUpp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alphaLow = "abcdefghijklmnopqrstuvwxyz"
d = enchant.Dict("en_US") # english dictionary to check for real words
toPrint = [] # threads cannot write to files

def decrypt(indexes):
    #try each key in thread partition
    for index in indexes:
        #define in loop so each check gets a new bool to check if it is a real word
        isreal = True
        #ensure that upper and lower are on the same letter
        decrypted = ""
        # Change every value in the string under the same key
        for character in message:
            #check if character is upper or lower case, and then work accordingly 
            if character.isupper():
                # get placement in alphabet for shift
                pointer = alphaUpp.find(character)
                pointer = pointer - index
                #since cipher is in a circle, you need to "wrap" if under 26
                if pointer < 0:
                    pointer = pointer + 26
                
                # append decryped character
                decrypted = decrypted + alphaUpp[pointer]
            #lowercase
            elif character.islower():
                # get placement in alphabet for shift
                pointer = alphaLow.find(character)
                pointer = pointer - index
                #since cipher is in a circle, you need to "wrap" if under 26
                if pointer < 0:
                    pointer = pointer + 26
                
                # append decryped characterß
                decrypted = decrypted + alphaLow[pointer]
            #if special character, like puncuation or space
            else:
                decrypted = decrypted + character
        #check first few words to see if they are real values
        realword = decrypted.split(" ", 6)
        for i in range(0, 4):
            if d.check(realword[i]) == False:
                isreal = False
        #print final message
        if isreal == True:
            toPrint.append(index)
            toPrint.append(decrypted)
            return toPrint      

print("How many threads would you like to test? Enter an integer 1-26")
threads = int(input())

a = numpy.arange(26)
a = numpy.array_split(a, threads)

pool = mp.Pool(processes=threads)

startTime = time.time()
toPrint = pool.map(decrypt, a)
executionTime = time.time() - startTime

# get rid of none for functions that did not return anything
toPrint = list(filter(None, toPrint))

o.write(f"Key #{toPrint[0][0]}\nThread Count {threads}\nExecution Time: {executionTime} seconds\n\n{toPrint[0][1]}")
print(f"Execution completed in {executionTime} seconds")