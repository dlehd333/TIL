using System;
using System.Linq;

namespace BaseballCSharp
{
    public class Answer : NumberContainer
    {
        public void Create()
        {
            Random random = new Random();

            while (true)
            {
                for (int i = 0; i < _numbers.Length; i++)
                    _numbers[i] = random.Next(Constant.MaxNumber);

                if (_numbers.ToHashSet().Count == Constant.Digit)
                    break;
            }
        }

        protected override string GetPrefix()
        {
            return "[정답] ";
        }
    }
}