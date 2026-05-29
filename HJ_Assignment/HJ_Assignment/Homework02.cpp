#include <iostream>
#include <string>

#include "Homework02.h"

using namespace std;

//트럼프 카드를 43같은 숫자로 저장 0~12 (A~K라 쓸때는 1 더해서 사용)
//문양은 /13 숫자는 %13;
int TrumpCard[NumOfTrumpCard];
int CardCount[NumOfCardInOnShape] = { 0, };
// 카드를 배열에서 꺼내올 인덱스
int CardIndex = 0;

void FisherYatesShuffle(int* Array, int Length)
{

	for (int i = Length - 1; i > 0; i--)
	{
		int Target = rand() % (i + 1);
		int Temp = Array[i];
		Array[i] = Array[Target];
		Array[Target] = Temp;
	}
}

int GetOneOrTwoInput()
{
	int Input = 0;

	while (Input == 0)
	{
		cin >> Input;
		cin.clear();
		cin.ignore(10000, '\n');
		if (Input != 1 && Input != 2)
		{
			printf("올바를 숫자를 입력하세요.....\n");
			Input = 0;
		}
	}

	return Input;
}

void PrintAmount(int PlayerAmount, int DealerAmount)
{
	printf("당신 패의 합 : %s\n", PlayerAmount == -1 ? "BlackJack" : to_string(PlayerAmount).c_str());
	printf("딜러 패의 합 : %s\n\n", DealerAmount== -1 ? "BlackJack" : to_string(DealerAmount).c_str());
}

void PrintHand(BlackJackPlayer& Player, BlackJackDealer& Dealer)
{
	system("cls");
	PrintHand(Player.Name, Player.Hand, Player.HandLen);
	PrintHand(Dealer.Name, Dealer.Hand, Dealer.HandLen, Dealer.PublicIndex);
}

void PrintHand(string Name, int* InHand, int& InHandLen, int PublicIndex)
{
	std::string ShapeString[4] = { {"♠ "},{"♣ "},{"♥ "},{"◆ "} };

	ECardShape Shape = Spade;
	int Val = 0;

	printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf(" %s의 패\n", Name.c_str());

	for (int i = 0; i < InHandLen; i++)
	{
		Shape = CalcCardShape(InHand[i]);
		Val = CalcCardVal(InHand[i]);

		if (i % 3 == 0) printf("\n");

		if (i >= PublicIndex)
		{
			printf("[가려진 카드]");
			continue;
		}

		if (Val == 1) printf("[%s      A]", ShapeString[(int)Shape].c_str());
		else if (Val == 11)printf("[%s      J]", ShapeString[(int)Shape].c_str());
		else if (Val == 12)printf("[%s      Q]", ShapeString[(int)Shape].c_str());
		else if (Val == 13)printf("[%s      K]", ShapeString[(int)Shape].c_str());
		else printf("[%s      %2d]", ShapeString[(int)Shape].c_str(), Val);

	}
	printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

ECardShape CalcCardShape(int Card)
{
	return ECardShape((Card-1) / NumOfCardInOnShape);
}

int CalcCardVal(int Card)
{
	return ((Card - 1) % NumOfCardInOnShape + 1);
}

int CalcCardAmount(int* InHand, int& InHandLen)
{
	int Amount = 0;
	int AceCnt = 0;

	for (int i = 0; i < InHandLen; i++)
	{
		int CardValue = CalcCardVal(InHand[i]);

		// 유효범위 확인
		if (CardValue > MaxCardValue || CardValue < 1)
		{
			printf("Err! 카드의 숫자가 유효범위 바깥입니다!");
			return -1;
		}

		// 에이스의 경우 계산을 미룬다
		if (CardValue == AceCard)
		{
			AceCnt++;
		}

		// J부터 K까지의 카드는 일괄적으로 10으로 만든다.
		else if (JCard <= CardValue && CardValue <= KCard)
		{
			Amount += 10;
		}
		else
		{
			Amount += CardValue;
		}
	}

	// 에이스 점수 결정
	if (AceCnt)
	{
		int MaxPoint = AceCnt * AceHighPoint;
		int MinPoint = AceCnt * AceLowPoint;
		int AcePoint = MaxPoint;
		while (AcePoint > MinPoint)
		{
			if (Amount + AcePoint <= WinningScore) break;
			AcePoint -= (AceHighPoint - AceLowPoint);
		}
		Amount += AcePoint;

		// 블랙잭
		if (Amount == WinningScore)
			Amount = BlackJackScore;
	}

	return Amount;
}

void GetCard(int* InHand, int& InHandLen)
{
	InHand[InHandLen++] = TrumpCard[CardIndex++];
}

bool CheckEndCondition(int Amount)
{
	return (Amount != BlackJackScore) && (Amount > WinningScore);
}

void GetEnter()
{
	printf("엔터를 눌러 진행하세요\n");
	cin.get();
}

void StartPhase(BlackJackPlayer& Player, BlackJackDealer& Dealer)
{
	bool IsPlayerTurn = true;

	for (int i = 0; i < InitialCardNum * 2; i++)
	{
		GetEnter();
		if (IsPlayerTurn)
		{
			//플레이어 한장 받음
			GetCard(Player.Hand, Player.HandLen);
			IsPlayerTurn = false;
		}
		else
		{
			//딜러 한장 받음
			GetCard(Dealer.Hand, Dealer.HandLen);
			IsPlayerTurn = true;
		}
		PrintHand(Player, Dealer);
	}
}

void Homework02_Run()
{

	printf("\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃       2. 블랙잭 만들기        ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	//트럼프 카드 초기화
	for (int i = 0; i < NumOfTrumpCard; i++)
	{
		TrumpCard[i] = i + 1;
	}
	while (true)
	{
		printf("새 게임을 시작하시겠습니까?\n");
		printf("[1.예]			   [2.아니오]\n");
		int Input = GetOneOrTwoInput();

		if (Input == 2)
		{
			printf("게임을 종료합니다\n");
			break;
		}

		BlackJackPlayer Player;
		BlackJackDealer Dealer;

		CardIndex = 0;

		// 시작하기 전에 한 번 섞기
		FisherYatesShuffle(TrumpCard, NumOfTrumpCard);

		/*
			┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
			┃           초기 배분			┃
			┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
		*/
		StartPhase(Player, Dealer);


		/*
			┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
			┃         플레이어 턴			┃
			┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
		*/
		//반복
		//	- 카드패 계산
		//	- 받을지 여부 입력
		//		- 받은경우
		//			- 카드를 받음
		//		- 안받은경우
		//			- 반복문 탈출


		bool IsStand = false;
		bool IsPlayerLose = false;

		printf("당신의 차례!\n");
		while (IsStand == false)
		{
			int PlayerAmount = CalcCardAmount(Player.Hand, Player.HandLen);
			//플레이어 턴에는 아직 가려진 패가 있음
			int DealerAmount = CalcCardAmount(Dealer.Hand, Dealer.PublicIndex);

			PrintAmount(PlayerAmount, DealerAmount);

			// 플레이어 버스트
			if (CheckEndCondition(PlayerAmount))
			{
				printf("당신의 버스트... 패배하였습니다.\n");
				IsPlayerLose = true;
				GetEnter();
				break;
			}

			if (PlayerAmount == BlackJackScore)
			{
				printf("\n\n !!Black Jack!!\n \n");
				break;
			}

			// 선택
			printf("카드를 더 받을지(Hit) 멈출지 정하세요\n");
			printf("1.Hit       2.Stand\n");
			int Input = GetOneOrTwoInput();
			

			if (Input == 2)
			{
				IsStand = true;
				break;
			}

			printf("Hit를 선택해 새 카드를 받습니다\n");
			GetEnter();
			system("cls");
			GetCard(Player.Hand, Player.HandLen);
			PrintHand(Player, Dealer);
		}

		// 플레이어 패배시 종료
		if (IsPlayerLose) continue;
		/*
		┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
		┃           딜러 턴				┃
		┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
		*/
		
		//딜러의 가려졌던 하나 공개
		//- 카드패 계산
		//- 21 넘으면 패배
		//- 17보다 작은 경우
		

		// 딜러의 공개범위를 끝까지 늘림.
		Dealer.PublicIndex = HandMAxCapacity;
		int PlayerAmount = CalcCardAmount(Player.Hand, Player.HandLen);
		int DealerAmount = CalcCardAmount(Dealer.Hand, Dealer.HandLen);
		bool IsDealerLose = false;

		system("cls");
		PrintHand(Player, Dealer);

		while (DealerAmount < 17)
		{
			printf("딜러가 새 카드를 받습니다\n");
			GetEnter();
			system("cls");

			GetCard(Dealer.Hand, Dealer.HandLen);
			DealerAmount = CalcCardAmount(Dealer.Hand, Dealer.HandLen);
			
			PrintHand(Player, Dealer);
			PrintAmount(PlayerAmount, DealerAmount);

			if (CheckEndCondition(DealerAmount))
			{
				printf("딜러의 버스트... 승리하였습니다.\n");
				IsDealerLose = true;
				GetEnter();
				break;
			}


		}

		if (IsDealerLose) continue;

		/*
		┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
		┃          사후 판정			┃
		┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
		*/
		// 21에 가까운쪽이 승리
		// 같으면 무승부
		//	- 둘다 21점에 한쪽만 블랙잭이면 블랙잭인 쪽 승리

		bool IsPlayerBlacjack = false;
		bool IsDelerBlacjack = false;

		PlayerAmount = CalcCardAmount(Player.Hand, Player.HandLen);
		DealerAmount = CalcCardAmount(Dealer.Hand, Dealer.HandLen);

		if (PlayerAmount == BlackJackScore)	IsPlayerBlacjack = true;
		if (DealerAmount == BlackJackScore)	IsDelerBlacjack = true;
		
		printf("당신 패의 합 : %s\n", IsPlayerBlacjack ? "BlackJack" : to_string(PlayerAmount).c_str());
		printf("딜러 패의 합 : %s\n\n", IsDelerBlacjack ? "BlackJack" : to_string(DealerAmount).c_str());

		int PlayerFinalScore = WinningScore - PlayerAmount;
		int DealerFinalScore = WinningScore - DealerAmount;

		if (IsPlayerBlacjack && !IsDelerBlacjack)
		{
			printf("\n\n 당신의 승리! \n\n");
		}
		else if (!IsPlayerBlacjack && IsDelerBlacjack)
		{
			printf("\n\n 딜러의 승리...! \n\n");
		}
		else if (IsPlayerBlacjack && IsDelerBlacjack)
		{
			printf("\n\n 무승부! \n\n");
		}
		else
		{
			if (PlayerFinalScore < DealerFinalScore)
				printf("\n\n 당신의 승리! \n\n");
			else if (PlayerFinalScore > DealerFinalScore)
				printf("\n\n 딜러의 승리...! \n\n");
			else if (PlayerFinalScore == DealerFinalScore)
				printf("\n\n 무승부! \n\n");
		}



	}
}