using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaseballCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            // 1. (중복되지 않는 세개의 0~9 사이의 정수로 이루어진) 정답을 생성한다.
            Answer answer = new Answer();
            answer.Create();
            answer.Print();

            int tryCount = 0;
            while (true)
            {
                tryCount++;

                // 2. 추측을 입력받는다.
                Guess guess = new Guess();
                guess.Input();
                guess.Print();

                // 3. 결과를 계산한다.
                Result result = new Result();
                result.Calculate(answer, guess);
                result.Print();

                // 4. 3S가 아니면 2번으로 돌아간다.
                if (result.isCorrect())
                    break;
            }

            // 5. 도전횟수를 출력한다.
            Console.WriteLine($"도전횟수 : {tryCount}");
        }
    }
}
