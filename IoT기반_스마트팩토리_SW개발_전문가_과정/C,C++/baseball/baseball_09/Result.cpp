#include <iostream>
#include "Result.h"
#include "Constant.h"

void Result::calculate(int* answers, int* guesses)
{
    for (int i = 0; i < DIGIT; i++)
    {
        int j = (i + 1) % DIGIT;
        int k = (i + 2) % DIGIT;

        if (guesses[i] == answers[i])
            strike++;
        else if (guesses[i] == answers[j] || guesses[i] == answers[k])
            ball++;
        else
            this->out++;
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