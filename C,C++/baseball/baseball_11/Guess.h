#pragma once

class Guess
{
private:
	int numbers[DIGIT];

public:
	void input();

	void print();

	int at(int index);
};

