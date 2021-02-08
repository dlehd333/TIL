#include "Constant.h"
#include <iostream>
using namespace std;

void printNumbers(int* numbers, const char* prefix)
{
    cout << prefix;
    for (int i = 0; i < DIGIT; i++)
        cout << numbers[i] << " ";
    cout << endl;
}