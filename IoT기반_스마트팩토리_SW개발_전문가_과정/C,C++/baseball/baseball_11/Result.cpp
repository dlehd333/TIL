#include <iostream>
#include "Result.h"
#include "Constant.h"
#include "Answer.h"
#include "Guess.h"

void Result::calculate(Answer* answer, Guess* guess)
{
    for (int i = 0; i < DIGIT; i++)
    {
        int j = (i + 1) % DIGIT;
        int k = (i + 2) % DIGIT;

        if (guess->at(i) == answer->at(i))
            strike++;
        else if (guess->at(i) == answer->at(j) || guess->at(i) == answer->at(k))
            ball++;
        else
            out++;
    }
}

void Result::print()
{
    std::cout << "S:" << strike << " B:" << ball << " O:" << out << std::endl;
}

bool Result::isCorrect()
{
    return strike == DIGIT;
}