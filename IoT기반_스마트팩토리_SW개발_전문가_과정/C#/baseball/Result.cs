using System;

namespace BaseballCSharp
{
    public class Result
    {
        private int _strike;
        private int _ball;
        private int _out;

        public void Calculate(Answer answer, Guess guess)
        {
            for (int i = 0; i < Constant.Digit; i++)
            {
                int j = (i + 1) % Constant.Digit;
                int k = (i + 2) % Constant.Digit;

                if (guess[i] == answer[i])
                    _strike++;
                else if (guess[i] == answer[j] || guess[i] == answer[k])
                    _ball++;
                else
                    _out++;
            }
        }

        public void Print()
        {
            Console.WriteLine($"S:{_strike} B:{_ball} O:{_out}");
        }

        public bool isCorrect()
        {
            return _strike == Constant.Digit;
        }
    }
}