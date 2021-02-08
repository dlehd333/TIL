#pragma once
#include "Constant.h"

class NumberContainer
{
protected:
	int numbers[DIGIT];

public:
	void print();
	int at(int index);
	virtual const char* getPrefix() = 0;
};

