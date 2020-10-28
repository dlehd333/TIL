#pragma once
#include "NumberContainer.h"

class Guess : public NumberContainer
{
public:
	void input();

	virtual const char* getPrefix();
};

