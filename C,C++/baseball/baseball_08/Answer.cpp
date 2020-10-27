#include <iostream>
#include "Constant.h"

void createAnswers(int* answers)
{
    srand(0);

    while (true)
    {
        for (int i = 0; i < DIGIT; i++)
            answers[i] = rand() % MAX_NUMBER;

        if (answers[0] != answers[1] && answers[1] != answers[2] && answers[2] != answers[0])
            break;
    }
}