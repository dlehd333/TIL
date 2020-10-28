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
    cout << "[Guess] ";
    for (int i = 0; i < DIGIT; i++)
        cout << numbers[i] << " ";
    cout << endl;
}