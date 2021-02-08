// 인디언 섯다 (섯다 + 인디언 포커) : 플레이어는 2인으로 고정
// 작업자 : 이동희(dlehd333), 장석, 이재훈

using System;
using System.Collections.Generic;

namespace Shutta
{
    class Program
    {
        static void Main()
        {
            // 플레이어 생성(2명)
            var players = new List<Player>();
            for (int i = 0; i < 2; i++)
            {
                Console.Write($"플레이어{i+1} 의 이름을 입력하세요 : ");
                string name = Console.ReadLine();
                players.Add(new Player(name));
            }
            // 딜러 생성
            var dealer = new Dealer();
            // 베팅금이 쌓이는 변수
            int groundMoney = 0;
            // 플레이 시작
            while (true)
            {
                Console.Clear();
                // 돈이 떨어진 플레이어가 있으면 게임 종료
                if (HasAnyoneOring(players))
                    break;
                // 라운드 시작
                GoRound(players, dealer, ref groundMoney);
                // 라운드 결과 정산
                ResultRound(players, ref groundMoney);
                Break();
            }
        }

        private static void GoRound(List<Player> players, Dealer dealer, ref int groundMoney)
        {
            Break($"게임을 시작합니다. 참가비 {Constant.BettingMoney}원이 들어갑니다.");
            // 카드 회수
            foreach (var player in players)
                player.DropCards();
            dealer.Shuffle();
            // 참가비
            foreach(var player in players)
                player.Bet.BetMoney += Constant.BettingMoney;
            Console.Clear();
            // 카드 뽑기
            for (int i = 0; i < 2; i++)
            {
                foreach (var player in players)
                    player.AddCard(dealer.DrawCard());
            }
            // 1페이즈 : 자신의 카드 1장을 확인한다
            PhaseOne(players);
            // 2페이즈 : 자신의 카드 1장과 상대방 카드 1장을 확인하고 베팅한다
            PhaseTwo(players);
        }
        private static void PhaseOne(List<Player> players)
        {
            for (int i = 0; i < 2; i++)
            {
                // 확인할 카드를 선택한다
                ChoiceCard(players[i]);
                // 자신이 선택한 카드를 보여준다
                ShowPlayerCards(players[i]);
                Console.Clear();
            }
        }
        private static void PhaseTwo(List<Player> players)
        {
            for (int i = 0; i < 2; i++)
            {
                // 자신이 선택한 카드와 상대방이 선택한 카드를 보여준다
                ShowPlayerCards(players, i);
                // 카드를 보고 베팅 여부를 결정한다
                Betting.DoBetting(players, i);
                // 다이를 선택했다면 게임을 끝낸다
                if (Betting.DiedPlayer > -1)
                    return;
                Console.Clear();
            }
            // 상대방이 레이즈 또는 올인을 선택했다면 추가 베팅을 선택한다
            if (players[1].Bet.BetType == 2 || players[1].Bet.BetType == 3)
                Betting.DoBetting(players, 2);
        }
        private static void ShowPlayerCards(Player player)
        {
            Console.WriteLine("선택한 카드입니다");
            Console.WriteLine($"{player.Name} : {player.Cards[player.PickupCard]}");
            Break();
        }
        private static void ShowPlayerCards(List<Player> players, int index)
        {
            Console.WriteLine("선택한 카드와 상대방이 보여준 카드입니다");
            int opponent = (index + 1) % 2;
            int opponentPick = (players[opponent].PickupCard + 1) % 2;
            Console.Write($"{players[index].Name} : {players[index].Cards[players[index].PickupCard]} / ");
            Console.WriteLine($"{players[opponent].Name} : {players[opponent].Cards[opponentPick]}");
        }
        private static void ChoiceCard(Player player)
        {
            Console.Write($"{player.Name}님, 오픈할 카드를 선택해 주세요(0 or 1) : ");
            player.PickupCard = (int.Parse(Console.ReadLine())) % 2;
        }
        private static void ResultRound(List<Player> players, ref int groundMoney)
        {
            Console.Clear();
            // 배팅금 회수
            for (int i = 0; i < 2; i++)
            {
                players[i].Money -= players[i].Bet.BetMoney;
                groundMoney += players[i].Bet.BetMoney;
                players[i].Bet.BetMoney = 0;
            }
            // 승자 결정
            Player winner = FindWinner(players);
            // 동점시 재경기
            if (Player.IsDraw)
            {
                Player.IsDraw = false;
                Break("동점입니다");
                return;
            }
            Console.WriteLine("승자는 " + winner.Name + "입니다.");
            // 승자에게 베팅금을 주고 베팅금을 0원으로
            winner.Money += groundMoney;
            groundMoney = 0;
            // 플레이어의 잔액을 보여준다
            ShowPlayerMoney(players);
            // 이긴 사람을 선으로 바꿔주기
            if(winner.Name == players[1].Name)
            {
                Player t = players[0];
                players[0] = players[1];
                players[1] = t;
            }
        }
        private static Player FindWinner(List<Player> players)
        {
            List<int> score = new List<int>();
            // 플레이어의 카드와 점수를 보여주고, 점수를 저장한다
            foreach (var player in players)
            {
                Console.WriteLine($"{player.Name} : {player.Cards[0]} / {player.Cards[1]} / score : {player.GetScore()}");
                score.Add(player.GetScore());
            }
            // 다이 한 플레이어가 있다면 상대방이 승리한 것으로 간주
            if (Betting.DiedPlayer > -1)
            {
                Console.WriteLine($"{players[Betting.DiedPlayer].Name} 플레이어가 다이 하셨습니다.");
                Player diedPlayer = players[(Betting.DiedPlayer + 1) % 2];
                Betting.DiedPlayer = -1;
                return diedPlayer;
            }
            else
            {
                // 점수가 같으면 무승부로
                if (score[0] == score[1])
                {
                    Player.IsDraw = true;
                    return players[0];
                }
                // 무승부가 아니라면 점수로 승패를 결정한다
                else if (score[0] > score[1])
                    return players[0];
                else
                    return players[1];
            }
        }
        private static void ShowPlayerMoney(List<Player> players)
        {
            foreach(var player in players)
                Console.WriteLine($"{player.Name} has {player.Money:C0} won.");
        }
        private static bool HasAnyoneOring(List<Player> players)
        {
            // 플레이어 중에 돈이 다 떨어진 사람이 있다면 true
            if (players.Exists(x => x.Money <= 0))
                return true;
            return false;
        }
        private static void Break(string message = "")
        {
            Console.Write(message);
            Console.ReadKey();
        }
    }
}
