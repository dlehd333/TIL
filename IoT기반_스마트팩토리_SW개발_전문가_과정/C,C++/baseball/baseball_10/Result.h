//#pragma once

#ifndef __Result__
#define __Result__

#include "Answer.h"
#include "Guess.h"

struct Result
{
    // member variable == field
    int strike;
    int ball;
    int out;

    // member function == method
    void calculate(Answer* answer, Guess* guess);

    void print();

    bool isCorrect();
};


#endif