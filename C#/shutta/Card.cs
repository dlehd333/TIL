namespace Shutta
{
    public struct Card
    {
        public Card(int no, bool kwang)
        {
            No = no;
            Kwang = kwang;
        }
        public int No { get; }
        public bool Kwang { get; }
        public override string ToString()
        {
            if (Kwang)
                return $"{No}광";
            else
                return No.ToString();
        }
    }
}