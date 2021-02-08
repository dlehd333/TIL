// 다중 파일 컴파일

#include <iostream>
#include "Constant.h"
#include "Result.h"
#include "Answer.h"
#include "Guess.h"
#include "Number.h"

using namespace std;

int main()
{
    // 1. (중복되지 않는 세개의 0~9 사이의 정수로 이루어진) 정답을 생성한다.
    int answers[DIGIT];
    createAnswers(answers);

    printNumbers(answers, "[정답] ");

    int tryCount = 0;
    while (true)
    {
        tryCount++;
        cout << "도전횟수 : " << tryCount << endl;

        // 2. 추측을 입력받는다.
        int guesses[DIGIT];
        inputGuesses(guesses);

        printNumbers(guesses, "[추측] ");


        // 3. 결과를 계산한다.
        Result result = {};
        calculateResult(&result, answers, guesses);

        printResult(&result);


        // 4. 정답이 아니면 2번으로 돌아간다.
        if (isCorrectResult(&result))
            break;
    }


    // 5. 도전횟수를 출력한다.
    cout << "너님의 도전횟수는 " << tryCount << "회 입니다." << endl;
}
