#pragma once
#include "Constant.h"

class Answer
{
public:
	// 명시적인 생성자를 만들면 기본생성자는 생성되지 않음
	//Answer(); <- 안만들어짐
	Answer(int luckyNo); // constructor 생성자
	~Answer(); // deconstructor 소멸자

private:
	int numbers[DIGIT];
	int luckyNo;

public:
	void create();
	void print();
	int at(int index);

	int getLuckyNo(); // getter
	void setLuckyNo(int luckyNo); // setter
};


