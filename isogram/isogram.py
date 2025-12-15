def is_isogram(string):
    # convert all letters to lower case 
    lower = string.lower()

    # create empty list to store all letter 
    letterList = []

    # iterate through the lower case string and extract only alphabetic characters 
    for char in lower:
        if char.isalpha():
            letterList.append(char)

    # note that we could create the letters list with a list comprehension 
    #theLetters = [char for char in lower if char.isalpha()]

    # Turn the list into a set. A set data structure cannot have duplicate elements
    letterSet = set(letterList)

    # If the string is an isogram, the list and set lengths will be equal
    return len(letterList) == len(letterSet)

     
assert(is_isogram("a") == True)
assert(is_isogram("aa") == False)
assert(is_isogram("six-year-old") == True)
assert(is_isogram("Banana") == False)
assert(is_isogram("The lazy brown fox") == False)

