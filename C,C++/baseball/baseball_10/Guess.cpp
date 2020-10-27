#include "Constant.h"
#include <iostream>
#include "Guess.h"
using namespace std;

void Guess::input()
{
    for (int i = 0; i < DIGIT; i++)
        std::cin >> numbers[i];
}

void Guess::print()
{
    cout << "[추측] ";
    for (int i = 0; i < DIGIT; i++)
        cout << numbers[i] << " ";
    cout << endl;
}

int Guess::at(int index)
{
    return numbers[index];
}
