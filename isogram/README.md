# Programming Exercise - Determine if a word or phrase is a Heterogram (1-Isogram).

A **heterogram** (from *hetero-*, meaning 'different', and *-gram* meaning 'written') is a word, phrase, or sentence in which no letter of the alphabet appears more than once. The term **isogram** is also used to mean the same thing. (from *iso-* meaning 'equal' and *-gram* meaning 'written'). 

**N-Isogram:** Each letter appears exactly N times. For example, "deed" and "noon" are 2-isogram words. **1-Isogram** means each letter appears exactly once.

Programming exercises commonly use the term *Isogram* to mean the same as *1-Isogram* and we will follow that convention. Thus, an isogram is a word or phrase that has no repeating alphabetic letters. Non-alphabetic characters such as spaces and hyphens are allowed to appear multiple times.


## Problem Statement

Write a function that determines if an input string is an isogram. The function returns true if the string is an isogram. Otherwise, it returns false.

## Key Characteristics

- **No Repeating Letters:** A letter cannot appear more than once. For example, "machine" is an isogram, but "tomorrow" is not (due to the repeated 'o' and 'r);
- **Case-Insensitive:** The letter's case does not matter. An uppercase 'A' is the same as a lowercase 'a' for purposes of the test. 
- **Non-Alphabetic Characters Ignored:** Spaces, hyphens, and other symbols generally do not count towards the letter repetition check. For example "six-year-old" is an isogram.
- **Empty String:** Assume an empty string is an isogram.



## Common Programming Approaches 

Below are some commonly used programming methods to solve the isogram problem.

- **Using a Set:** Convert the string (after processing to lower case and removing non-alphabetic characters) into a set. A set automatically removes duplicate elements. If the length of the set is equal to the length of the processed string, it's an isogram.

- **Using a Frequency Map/Dictionary**: Iterate through the string and use a dictionary or hash map to count the occurrences of each letter. If any count exceeds one, it's not an isogram.

- **Using a loop with a list/array:** Iterated through the string and add each character to a list of "seen" characters. Before adding, check if the current character is already in the list; if it is, the string is not an isogram.


## Example Solutions 

[isogram.c](isogram.c) uses a frequency array to count letters.

[isogram.py](isogram.py) uses a set, comparing set length to processed string length.

