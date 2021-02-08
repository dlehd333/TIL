#include <iostream>
#include "Result.h"
#include "Constant.h"

void calculateResult(Result* result, int* answers, int* guesses)
{
    for (int i = 0; i < DIGIT; i++)
    {
        int j = (i + 1) % DIGIT;
        int k = (i + 2) % DIGIT;

        if (guesses[i] == answers[i])
            result->strike++;
        else if (guesses[i] == answers[j] || guesses[i] == answers[k])
            result->ball++;
        else
            result->out++;
    }
}

void printResult(const Result* result)
{
    std::cout << "S:" << result->strike << " B:" << result->ball << " O:" << result->out << std::endl;
}

bool isCorrectResult(const Result* result)
{
    return result->strike == DIGIT;
}