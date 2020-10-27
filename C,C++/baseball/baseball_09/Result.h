//#pragma once

#ifndef __Result__
#define __Result__

struct Result
{
    // member variable == field
    int strike;
    int ball;
    int out;

    // member function == method
    void calculate(int* answers, int* guesses);

    void print();

    bool isCorrect();
};


#endif