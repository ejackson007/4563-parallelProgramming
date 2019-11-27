alphaUpp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alphaLow = "abcdefghijklmnopqrstuvwxyz"

f = open("original.txt", 'r')
o = open("hiddenMeaning.txt", 'w')
context = f.read()

def createKey():
    print("Enter an integer for the key")
    key = int(input())
    key = key % 26
    return key

def encrypt(key):
    encrypted = ""
    for letter in context:
        if letter.isupper():
            pointer = alphaUpp.find(letter)
            pointer = pointer + key

            if pointer > 25: # must be 25 because of [0-25]
                pointer = pointer - 26
            
            encrypted = encrypted + alphaUpp[pointer]
        elif letter.islower():
            pointer = alphaLow.find(letter)
            pointer = pointer + key
            
            if pointer > 25:
                pointer = pointer - 26
            encrypted = encrypted + alphaLow[pointer]
        else:
            encrypted = encrypted + letter
    o.write(encrypted)

key = createKey()
encrypt(key)

print("MESSAGE SCRAMBLED!")
