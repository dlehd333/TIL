#pragma once
#include "Constant.h"

class NumberContainer
{
protected:
	int numbers[DIGIT];

public:
	virtual void print(); // overridable
	int at(int index);
};

