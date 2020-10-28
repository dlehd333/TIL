// abstract method(추상함수/순수가상함수)

#include <iostream>
#include "Constant.h"
#include "Result.h"
#include "Answer.h"
#include "Guess.h"

using namespace std;

void printWithDecoration(NumberContainer* container)
{
    cout << "###" << endl;
    container->print();
    cout << "---" << endl;
}

int main()
{
    // 1. (중복되지 않는 세개의 0~9 사이의 정수로 이루어진) 정답을 생성한다.
    Answer* answer = new Answer();

    printWithDecoration(answer);

    answer->setLuckyNo(answer->getLuckyNo() + 1);
    answer->create();
    answer->print();

    int tryCount = 0;
    while (true)
    {
        tryCount++;
        cout << "try count : " << tryCount << endl;

        // 2. 추측을 입력받는다.
        Guess* guess = new Guess();
        printWithDecoration(guess);
        guess->input();
        guess->print();


        // 3. 결과를 계산한다.
        Result* result = new Result();
        result->calculate(answer, guess);
        result->print();


        // 4. 정답이 아니면 2번으로 돌아간다.
        if (result->isCorrect())
        {
            delete guess;
            delete result;

            break;
        }

        delete guess;
        delete result;
    }

    delete answer;

    // 5. 도전횟수를 출력한다.
    cout << "Your try count is " << tryCount << endl;
}
