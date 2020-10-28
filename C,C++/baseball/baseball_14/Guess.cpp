#include "Constant.h"
#include <iostream>
#include "Guess.h"
using namespace std;

void Guess::input()
{
    for (int i = 0; i < DIGIT; i++)
        std::cin >> numbers[i];
}

const char* Guess::getPrefix()
{
    return "[Guess] ";
}
