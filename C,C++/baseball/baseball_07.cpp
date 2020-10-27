// 함수2 (모듈화)

#include <iostream>
using namespace std;

#define MAX_NUMBER 10
const int DIGIT = 3;

struct Result
{
    int strike;
    int ball;
    int out;
};

void printNumbers(int* numbers, const char* prefix)
{
    cout << prefix;
    for (int i = 0; i < DIGIT; i++)
        cout << numbers[i] << " ";
    cout << endl;
}

void createAnswers(int* answers)
{
    srand(0);

    while (true)
    {
        for (int i = 0; i < DIGIT; i++)
            answers[i] = rand() % MAX_NUMBER;

        if (answers[0] != answers[1] && answers[1] != answers[2] && answers[2] != answers[0])
            break;
    }
}

void inputGuesses(int* guesses)
{
    for (int i = 0; i < DIGIT; i++)
        cin >> guesses[i];
}

void calculateResult(Result* result, int* answers, int* guesses)
{
    for (int i = 0; i < DIGIT; i++)
    {
        int j = (i + 1) % DIGIT;
        int k = (i + 2) % DIGIT;

        if (guesses[i] == answers[i])
            result->strike++;
        else if (guesses[i] == answers[j] || guesses[i] == answers[k])
            result->ball++;
        else
            result->out++;
    }
}

void printResult(const Result* result)
{
    cout << "S:" << result->strike << " B:" << result->ball << " O:" << result->out << endl;
}

bool isCorrectResult(const Result* result)
{
    return result->strike == DIGIT;
}

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
