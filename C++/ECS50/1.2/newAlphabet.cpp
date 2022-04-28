#include "string"
#include "iostream"
#include "stdlib.h"

int main(int argc, char* argv[])
{
    std::string word = "";
    int currentLetter;
    int caseIdentifier;
    int locationCount;

    for (int i = 1; i < argc; ++i) {
        locationCount = 0;
        currentLetter = atoi(argv[i]);
        caseIdentifier = currentLetter >> 26;

        if (caseIdentifier == 0)
        {
            while ((currentLetter >> locationCount) != 1)
            {
                locationCount += 1;
            }
            word += ('a' + locationCount);
        }

        if (caseIdentifier == 1)
        {
            currentLetter -= 67108864;
            while ((currentLetter >> locationCount) != 1)
            {
                locationCount += 1;
            }
            word += ('A' + locationCount);
        }

    }

    std::cout << "You entered the word: " << word;
}