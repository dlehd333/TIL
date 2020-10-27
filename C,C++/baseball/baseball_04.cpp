// 배열/컬렉션 (연속되고 같은 타입의 데이터를 묶는 방법)

#include <iostream>
using namespace std;

#define MAX_NUMBER 10
const int DIGIT = 3;

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
        int strike = 0;
        int ball = 0;
        int out = 0;

        for (int i = 0; i < DIGIT; i++)
        {
            int j = (i + 1) % DIGIT;
            int k = (i + 2) % DIGIT;

            if (guesses[i] == answers[i])
                strike++;
            else if (guesses[i] == answers[j] || guesses[i] == answers[k])
                ball++;
            else
                out++;
        }

        cout << "S:" << strike << " B:" << ball << " O:" << out << endl;


        // 4. 3S가 아니면 2번으로 돌아간다.
        if (strike == DIGIT)
            break;
    }


    // 5. 도전횟수를 출력한다.
    cout << "너님의 도전횟수는 " << tryCount + 1 << "회 입니다." << endl;
}
