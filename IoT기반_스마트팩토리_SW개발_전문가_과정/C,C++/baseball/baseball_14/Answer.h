#pragma once
#include "Constant.h"
#include "NumberContainer.h"

class Answer : public NumberContainer
{
private:
	int luckyNo;

public:
	void create();
	
	int getLuckyNo(); // getter
	void setLuckyNo(int luckyNo); // setter

	virtual const char* getPrefix();
};


