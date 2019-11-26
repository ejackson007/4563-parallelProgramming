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
    for letter in context:
        if letter.isupper():
            pointer = alphaUpp.find(letter)