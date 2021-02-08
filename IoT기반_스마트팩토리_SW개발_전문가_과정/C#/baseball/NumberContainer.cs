using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaseballCSharp
{
    public abstract class NumberContainer
    {
        protected int[] _numbers = new int[Constant.Digit];

        public void Print()
        {
            Console.Write(GetPrefix());

            //for (int i = 0; i < _numbers.Length; i++)
            //    Console.Write(_numbers[i] + " ");
            foreach (int x in _numbers)
                Console.Write(x + " ");

            Console.WriteLine();
        }

        protected abstract string GetPrefix();

        //public int At(int i)
        //{
        //    return _numbers[i];
        //}

        // indexer
        public int this[int i]
        {
            get
            {
                return _numbers[i];
            }
        }
    }
}
