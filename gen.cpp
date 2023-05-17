#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>

typedef unsigned int uint;

std::string randomString(uint maxLength = 15, std::string charIndex = "abcdefghijklmnaoqrs><:;'|}{[])(*&?^tuvwxyzABC-+=!DEFGHIJKLMNOPQRSTUVWXYZ1234567890")
{ // maxLength and charIndex can be customized, but I've also initialized them.
    uint length = 17; // length of the string is a random value that can be up to 'l' characters.

    uint indexesOfRandomChars[17]; // array of random values that will be used to iterate through random indexes of 'charIndex'
    for (uint i = 0; i < length; ++i) // assigns a random number to each index of "indexesOfRandomChars"
        indexesOfRandomChars[i] = rand() % charIndex.length();

    std::string randomString = ""; // random string that will be returned by this function
    for (uint i = 0; i < length; ++i)// appends a random amount of random characters to "randomString"
    {
        randomString += charIndex[indexesOfRandomChars[i]];
    } 
    return randomString;
}

int main()
{
    std::ofstream fout("text.txt");
    srand(time(NULL));

    int i = 0;
    while(i < 1000000) {
        fout << randomString() << " " << i << std::endl;
        i++;
    }

    return 0;
}