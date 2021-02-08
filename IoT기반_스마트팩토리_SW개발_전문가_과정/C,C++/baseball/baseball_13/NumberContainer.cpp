#include "NumberContainer.h"
#include <iostream>
using namespace std;

void NumberContainer::print()
{
    cout << "[Answer] ";
    for (int i = 0; i < DIGIT; i++)
        cout << numbers[i] << " ";
    cout << endl;
}

int NumberContainer::at(int index)
{
    return numbers[index];
}
