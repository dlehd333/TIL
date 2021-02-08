// 길고 못생긴 코드

#include <iostream>
using namespace std;

int main()
{
    // 1. (중복되지 않는 세개의 0~9 사이의 정수로 이루어진) 정답을 생성한다.
    srand(0);

    int answer0;
    int answer1;
    int answer2;

    while (true)
    {
        answer0 = rand() % 10;
        answer1 = rand() % 10;
        answer2 = rand() % 10;

        if (answer0 != answer1 && answer1 != answer2 && answer2 != answer0)
            break;
    }

    cout << "[정답] ";
    cout << answer0 << " ";
    cout << answer1 << " ";
    cout << answer2 << " ";
    cout << endl;

    int tryCount = 0;
    while (true)
    {
        // 2. 추측을 입력받는다.
        tryCount++;
        cout << "도전횟수 : " << tryCount << endl;

        int guess0;
        int guess1;
        int guess2;

        cin >> guess0;
        cin >> guess1;
        cin >> guess2;

        cout << "[추측] ";
        cout << guess0 << " ";
        cout << guess1 << " ";
        cout << guess2 << " ";
        cout << endl;


        // 3. 결과를 계산한다.
        int strike = 0;
        int ball = 0;
        int out = 0;

        if (guess0 == answer0)
            strike++;
        else if (guess0 == answer1 || guess0 == answer2)
            ball++;
        else
            out++;

        if (guess1 == answer1)
            strike++;
        else if (guess1 == answer2 || guess1 == answer0)
            ball++;
        else
            out++;

        if (guess2 == answer2)
            strike++;
        else if (guess2 == answer0 || guess2 == answer1)
            ball++;
        else
            out++;

        cout << "S:" << strike << " B:" << ball << " O:" << out << endl;


        // 4. 3S가 아니면 2번으로 돌아간다.
        if (strike == 3)
            break;
    }


    // 5. 도전횟수를 출력한다.
    cout << "너님의 도전횟수는 " << tryCount + 1 << "회 입니다." << endl;
}
