from asyncore import write
from collections import Counter
import collections
import re
import string
import re
import string

def printsomething():
    print("Hello from python!")

def PrintMe(v):
        print('item unvailable')
        return 100;

def SquareValue(v):
    return v * v

# Counter is essentially a dictionary meaning it has keys and corresponding values
def itemCount():
    f = open("CS210_Project_Three_Input_File.txt", "r") # opens and reads text file
    itemsCounted = Counter(f.read().split())  # variable stores files strings
    itemsCounted.keys() # variable stores values as keys
    for key, value in itemsCounted.items(): # pairs the key and value in items variable
        print(key, value)  # word and its frequency is printed to screen
        f.close() 

def specificItem(searchTerm):
    searchTerm = searchTerm.lower() #searchTerm = searchTerm.lower() 
    text = open("CS210_Project_Three_Input_File.txt") #Opens the file in read mode open("CS210_Project_Three_Input_File.txt)
    wordCount = 0 #Creates variable to track how many t wordCount = 0
    lines = text.readlines() #Check each line of the input file
    for line in lines: # Checks in lines 
        word = line.strip().lower() #removes any errant spaces #line line.strip() #Converts characters to lowercase word line.lower()
        if word == searchTerm: #Checks if the found word is equal if word == searchTerm: 
            wordCount += 1 # Increments number of times t wordCount += 1
            print(word)
            return wordCount
        if word != searchTerm: # if user inputted word isn't in the file prints unavailable
            print("Item unavailable")
            return wordCount
    text.close() #Close opened file text.close()#Count the number of appearances for each

def histogram(): 
       # Open both the read and the write files
    with open('frequency.dat', "w") as wp:    
        # Same code as in "ItemCounter" to store the values as a dictionary
        with open('CS210_Project_Three_Input_File.txt') as fp:
            counts = collections.Counter(line.strip() for line in fp)
        # Write the item and counts to the output file
        for key in counts:
            wp.write('%s %d\n' % (key, counts[key]))
    # If the file was properly closed, tell the user
    if wp.closed:
        print('successfully written to file')
 