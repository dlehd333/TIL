using System;
using System.Collections.Generic;
using System.Diagnostics.Eventing.Reader;

namespace Shutta
{
    public class Player
    {
        public Player(string name)
        {
            Name = name;
            Money = Constant.SeedMoney;
            Cards = new List<Card>();
            Bet = new Betting();
        }
        public string Name { get; }
        public int Money { get; set; }
        public List<Card> Cards { get; }
        public int PickupCard { get; set; }
        public Betting Bet { get; set; }
        public void AddCard(Card card)
        {
            Cards.Add(card);
        }
        public void DropCards()
        {
            Cards.Clear();
        }
        public virtual int GetScore()
        {
            if(Cards[0].No > Cards[1].No)
            {
                Card t = Cards[0];
                Cards[0] = Cards[1];
                Cards[1] = t;
            }

            if (Cards[0].Kwang && Cards[1].Kwang) // 장땡
                return (Cards[0].No + Cards[1].No) * 100;
            else if (Cards[0].No == Cards[1].No) // 땡
                return Cards[0].No * 20;
            else if (Cards[0].No == 1 && Cards[1].No == 2)
                return 15;
            else if (Cards[0].No == 1 && Cards[1].No == 4)
                return 14;
            else if (Cards[0].No == 1 && Cards[1].No == 9)
                return 13;
            else if (Cards[0].No == 1 && Cards[1].No == 10)
                return 12;
            else if (Cards[0].No == 4 && Cards[1].No == 10)
                return 11;
            else if (Cards[0].No == 4 && Cards[1].No == 6)
                return 10;
            else // 끗
                return (Cards[0].No + Cards[1].No) % 10;
        }
        public static bool IsDraw { get; set; }
    }
}
