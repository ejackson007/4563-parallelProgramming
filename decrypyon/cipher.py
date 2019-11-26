alphaUpp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alphaLow = "abcdefghijklmnopqrstuvwxyz"

f = open("original.txt", 'r')
o = open("hiddenMeaning.txt", 'w')
context = f.read()

def createKey():
    print("Enter an integer for the key")
    key = input()
    key = key % 26
    return key

def encrypt(key):
    encrypted = ""
    for letter in context:
        if letter.isupper():
            pointer = alphaUpp.find(letter)
            pointer = pointer + key
            
            if pointer > 26:
                pointer = pointer - 26
            
            encrypted = encrypted + alphaUpp[pointer]
        elif letter.islower():
            pointer = alphaLow.find(letter)
            pointer = pointer + key
            
            if pointer > 26:
                pointer = pointer - 26
            
            encrypted = encrypted + alphaLow[pointer]
        else:
            encrypted = encrypted + letter