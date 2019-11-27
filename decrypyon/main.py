import multiprocessing as mp
import os
import numpy
import enchant

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
                
                # append decryped character
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

def chunkstring(string, length):
    return (string[0+i:length+i] for i in range(0, len(string), length))          

a = numpy.arange(26)
a = numpy.array_split(a, 4)

pool = mp.Pool(processes=4)
toPrint = pool.map(decrypt, a)

# get rid of none for functions that did not return anything
toPrint = list(filter(None, toPrint))

o.write(f"Key #{toPrint[0][0]}\n\n {toPrint[0][1]}")
