//#pragma once

#ifndef __Result__
#define __Result__

#include "Answer.h"
#include "Guess.h"

class Result
{
private:
    // member variable == field
    int strike;
    int ball;
    int out;

public:
    // member function == method
    void calculate(Answer* answer, Guess* guess);

    void print();

    bool isCorrect();
};


#endif