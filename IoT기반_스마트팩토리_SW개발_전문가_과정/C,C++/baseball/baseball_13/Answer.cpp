#include <iostream>
#include "Constant.h"
#include "Answer.h"
using namespace std;

void Answer::create()
{
    srand(0);

    while (true)
    {
        for (int i = 0; i < DIGIT; i++)
            numbers[i] = rand() % MAX_NUMBER;

        if (numbers[0] != numbers[1] && numbers[1] != numbers[2] && numbers[2] != numbers[0])
            break;
    }
}

int Answer::getLuckyNo()
{
    if (luckyNo % 2 == 0)
        return luckyNo * -1;
    else
        return luckyNo;
}

void Answer::setLuckyNo(int luckyNo)
{
    // validation check
    if (luckyNo < 0)
        luckyNo = 0;

    this->luckyNo = luckyNo;
}
