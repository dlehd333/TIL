#include "NumberContainer.h"
#include <iostream>
using namespace std;

int NumberContainer::at(int index)
{
    return numbers[index];
}

void NumberContainer::print()
{
    cout << getPrefix();
    for (int i = 0; i < DIGIT; i++)
        cout << numbers[i] << " ";
    cout << endl;
}