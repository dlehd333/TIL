using System;
using System.Collections.Generic;
using System.Linq;

namespace Shutta
{
    public class Dealer
    {
        public Dealer()
        {
            for(int i =0; i < 2; i++)
            {
                for(int j = 1; j <= 10; j++)
                {
                    bool kwang = (j == 1 || j == 3 || j == 8) && i == 0;
                    Card card = new Card(j, kwang);
                    _cards.Add(card);
                }
            }
        }
        private List<Card> _cards = new List<Card>();
        private int _cardIndex = 0;
        public Card DrawCard()
        {
            return _cards[_cardIndex++];
        }

        public void Shuffle()
        {
            _cards = _cards.OrderBy(x => Guid.NewGuid()).ToList();
            _cardIndex = 0;
        }
    }
}