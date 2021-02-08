#include <iostream>
#include "Constant.h"
#include "Answer.h"
using namespace std;

Answer::Answer(int luckyNo)
{
    this->luckyNo = luckyNo;
}

Answer::~Answer()
{
    std::cout << "Answer deid here" << std::endl;
}

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

void Answer::print()
{
    cout << "[Answer] ";
    for (int i = 0; i < DIGIT; i++)
        cout << numbers[i] << " ";
    cout << endl;
}

int Answer::at(int index)
{
    return numbers[index];
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
