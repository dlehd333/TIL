#pragma once
#include "Constant.h"

struct Answer
{
	int numbers[DIGIT];

	void create();

	void print();

	int at(int index);
};


