#pragma once

struct Guess
{
	int numbers[DIGIT];

	void input();

	void print();

	int at(int index);
};

