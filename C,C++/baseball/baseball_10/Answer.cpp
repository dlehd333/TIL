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

void Answer::print()
{
    cout << "[정답] ";
    for (int i = 0; i < DIGIT; i++)
        cout << numbers[i] << " ";
    cout << endl;
}

int Answer::at(int index)
{
    return numbers[index];
}
