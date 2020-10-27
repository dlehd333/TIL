#include "Constant.h"
#include <iostream>

void inputGuesses(int* guesses)
{
    for (int i = 0; i < DIGIT; i++)
        std::cin >> guesses[i];
}