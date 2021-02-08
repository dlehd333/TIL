using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.XPath;

namespace Shutta
{
    public class Betting
    {
        public static void DoBetting(List<Player> players, int bettingStep)
        {
            if (bettingStep == 0)
                FirstStep(players[0]);
            else if (bettingStep == 1)
                SecondStep(players);
            else if (bettingStep == 2)
                LastStep(players);
        }
        private static void FirstStep(Player player)
        {
            int inputResult = player.Bet.GetBettingType("베팅 여부를 선택해 주세요(베팅(1),다이(2)) : ", 2);

            if (inputResult == 1)
                player.Bet.BetMoney = player.Bet.GetBettingMoney(player, 0);
            else
                DiedPlayer = 0;
        }
        private static void SecondStep(List<Player> players)
        {
            int inputResult = players[1].Bet.GetBettingType("베팅 여부를 선택해 주세요(콜(1),레이즈(2),올인(3),다이(4)) : ", 4);

            if (inputResult == 1)
                players[1].Bet.BetMoney = players[0].Bet.BetMoney;
            else if (inputResult == 2)
                players[1].Bet.BetMoney = players[1].Bet.GetBettingMoney(players[1], players[0].Bet.BetMoney);
            else if (inputResult == 3)
                players[1].Bet.BetMoney = players[1].Money;
            else if (inputResult == 4)
                DiedPlayer = 1;
        }
        private static void LastStep(List<Player> players)
        {
            int inputResult = players[0].Bet.GetBettingType("레이즈(올인)가 발생했습니다(콜(1),다이(2)) : ", 2);

            if (inputResult == 1)
            {
                if (players[0].Money > players[1].Bet.BetMoney)
                    players[0].Bet.BetMoney = players[1].Bet.BetMoney;
                else
                    players[0].Bet.BetMoney = players[0].Money;
            }
            else
                DiedPlayer = 0;
        }
        public int GetBettingType(string message, int maxNum)
        {
            int bettingType;
            while (true)
            {
                Console.WriteLine();
                Console.WriteLine(message);
                bettingType = int.Parse(Console.ReadLine());
                if (bettingType > 0 && bettingType <= maxNum)
                    break;
            }
            BetType = bettingType;
            return bettingType;
        }
        public int GetBettingMoney(Player player, int minMoney)
        {
            int bettingMoney;
            while (true)
            {
                Console.WriteLine("금액을 베팅하세요 : ");
                bettingMoney = int.Parse(Console.ReadLine());
                if (bettingMoney < player.Money && bettingMoney > minMoney)
                    break;
            }
            BetMoney = bettingMoney;
            return bettingMoney;
        }
        public int BetType { get; set; }
        public int BetMoney { get; set; }
        public static int DiedPlayer { get; set; } = -1;
    }
}