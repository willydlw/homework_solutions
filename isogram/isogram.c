#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// gcc -Wall -o isogram isogram.c

// Frequency Count Approach
bool isIsogram(const char* string)
{
    // Create a zero-initialized array to store a count of each letter's occurrence
    int frequency[26] = {0};    // 26 letters in English alphabet

    // iterate through each character in the string
    for(size_t i = 0; i < strlen(string); i++)
    {
        // only count alphabetic characters
        if(isalpha(string[i]))
        {
            char letter = tolower(string[i]);   // convert to lower case
            int index = letter - 'a';           // convert letter to array index location
            frequency[index]++;                 // add 1 to that letter's count
            if(frequency[index] > 1)
            {
                return false;                   // we can stop counting when a letter's count is > 1
            }
        }
    }

    return true;            // no letter count was > 1, so must be isogram
}


void testIsogram(const char* string, bool expected)
{
    bool result = isIsogram(string);
    if(result != expected){
        fprintf(stderr, "[ERROR] string: %s, expected: %s != result: %s\n", string, expected? "true":"false", 
                result? "true" : "false");
    }
}


void runTests()
{
    testIsogram("", true);      // empty string
    testIsogram("a", true);
    testIsogram("aa", false);
    testIsogram("aA", false);   // upper A and lower a same letter
    testIsogram("abc", true); 
    testIsogram("six-year-old", true);  // ignore hyphens
    testIsogram("six year old", true);  // ignore spaces
    testIsogram("The quick brown fox jumps over the lazy dog", false);
    testIsogram("dialogue", true);
    testIsogram("deed", false);
    testIsogram("PATHFINDER", true);
    
}

int main()
{
    runTests();
    return 0;
}