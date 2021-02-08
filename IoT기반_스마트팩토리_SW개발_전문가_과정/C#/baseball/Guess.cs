using System;

namespace BaseballCSharp
{
    public class Guess : NumberContainer
    {
        public void Input()
        {
            for (int i = 0; i < _numbers.Length; i++)
            {
                string line = Console.ReadLine();
                _numbers[i] = int.Parse(line);
            }
        }

        protected override string GetPrefix()
        {
            return "[추측] ";
        }
    }
}