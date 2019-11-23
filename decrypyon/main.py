import multiprocessing as mp
import os
import numpy
import enchant

message = 'GUVF vf ZL FRPERG zrffntr.'
alphaUpp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alphaLow = "abcdefghijklmnopqrstuvwxyz"

def decrypt(upper, lower):
    #try each key possible
    for uppKey in upper:
        #ensure that upper and lower are on the same letter
        index = upper.find(uppKey)

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
        print('Key #%s: %s' % (index, decrypted))

def chunk(alphabet, size):
    #is seeing as a float instead of an int for some reason. Will figure out later
    #############################################################################
    for i in range(0, len(alphabet), size):
        yield list[i:i+size]            
                

d = enchant.Dict("en_US") # english dictionary to check for real words
#decrypt(alphaUpp, alphaLow)
a = list(chunk(alphaUpp, len(alphaUpp) / 4))
b = list(chunk(alphaLow, len(alphaLow) / 4))

print(a)
print(b)


# #split array into pieces
# a = numpy.array_split(a, 64)

# pool = mp.Pool(processes=4)
# pool.map(decrypt, a, b)


# sum = addArray(a)
# print(f"Sum array is {summation}\n")
# print(f"Flipped array is {flipped}\n")
#print(f"Summation of the array is {arraySum}\n")
