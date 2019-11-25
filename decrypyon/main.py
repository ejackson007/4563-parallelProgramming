import multiprocessing as mp
import os
import numpy
import enchant

message = 'GUVF vf ZL FRPERG zrffntr.'
alphaUpp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alphaLow = "abcdefghijklmnopqrstuvwxyz"

def decrypt(indexes):
    #try each key possible
    for index in indexes:
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
        #print final message
        print(f'Key #{index}: {decrypted}')

def chunkstring(string, length):
    return (string[0+i:length+i] for i in range(0, len(string), length))          
                
d = enchant.Dict("en_US") # english dictionary to check for real words

a = numpy.arange(26)
a = numpy.array_split(a, 4)

print(a)

pool = mp.Pool(processes=4)
pool.map(decrypt, a)
