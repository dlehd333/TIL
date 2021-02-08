// 구조체/사용자정의타입 (순서가 없거나 타입이 다른 데이터를 묶는 방법)

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

int main()
{
    // 1. (중복되지 않는 세개의 0~9 사이의 정수로 이루어진) 정답을 생성한다.
    srand(0);

    int answers[DIGIT];

    while (true)
    {
        for (int i = 0; i < DIGIT; i++)
            answers[i] = rand() % MAX_NUMBER;

        if (answers[0] != answers[1] && answers[1] != answers[2] && answers[2] != answers[0])
            break;
    }

    cout << "[정답] ";
    for (int i = 0; i < DIGIT; i++)
        cout << answers[i] << " ";
    cout << endl;

    int tryCount = 0;
    while (true)
    {
        // 2. 추측을 입력받는다.
        tryCount++;
        cout << "도전횟수 : " << tryCount << endl;

        int guesses[DIGIT];

        for (int i = 0; i < DIGIT; i++)
            cin >> guesses[i];

        cout << "[추측] ";
        for (int i = 0; i < DIGIT; i++)
            cout << guesses[i] << " ";
        cout << endl;


        // 3. 결과를 계산한다.
        Result result = {};
        int n = 0;

        for (int i = 0; i < DIGIT; i++)
        {
            int j = (i + 1) % DIGIT;
            int k = (i + 2) % DIGIT;

            if (guesses[i] == answers[i])
                result.strike++;
            else if (guesses[i] == answers[j] || guesses[i] == answers[k])
                result.ball++;
            else
                result.out++;
        }

        cout << "S:" << result.strike << " B:" << result.ball << " O:" << result.out << endl;


        // 4. 3S가 아니면 2번으로 돌아간다.
        if (result.strike == DIGIT)
            break;
    }


    // 5. 도전횟수를 출력한다.
    cout << "너님의 도전횟수는 " << tryCount << "회 입니다." << endl;
}
