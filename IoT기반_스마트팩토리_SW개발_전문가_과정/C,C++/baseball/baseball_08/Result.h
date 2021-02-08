//#pragma once

#ifndef __Result__
#define __Result__

struct Result
{
    int strike;
    int ball;
    int out;
};

void calculateResult(Result* result, int* answers, int* guesses);

void printResult(const Result* result);

bool isCorrectResult(const Result* result);
#endif