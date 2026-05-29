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
	//0. 배열의 마지막에서 처음 방향으로 진행
	//1. 현재 인덱스랑 자기 앞의 인덱스 (자기포함)에서 랜덤으로 골라서 swap
	//2. 다음 인덱스로 진행
	//3. 0번 인덱스까지 가면 1회 한 것.

	for (int i = Length - 1; i > 0; i--)
	{
		int Target = rand() % (i + 1);
		int Temp = Array[i];
		Array[i] = Array[Target];
		Array[Target] = Temp;
	}
}

void PrintPlayerHand(BlackJackPlayer& Player)
{
	std::string ShapeString[4] =
	{
		{"♠ "},
		{"♣ "},
		{"♥ "},
		{"◆ "},
	};

	ECardShape Shape = Spade;
	int Val = 0;

	printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf(" 당신의 패\n");
	for (int i = 0; i < Player.HandLen; i++)
	{
		Shape = CalcCardShape(Player.Hand[i]);
		Val = CalcCardVal(Player.Hand[i]);

		if (i % 3 == 0) printf("\n");
		printf("[%s      %d]", ShapeString[(int)Shape].c_str(), Val);
	}
	printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

void PrintDealerHand(BlackJackDealer& Dealer)
{
	std::string ShapeString[4] =
	{
		{"♠ "},
		{"♣ "},
		{"♥ "},
		{"◆ "},
	};

	ECardShape Shape = Spade;
	int Val = 0;

	printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf(" 딜러의 패\n");
	for (int i = 0; i < Dealer.HandLen; i++)
	{
		Shape = CalcCardShape(Dealer.Hand[i]);
		Val = CalcCardVal(Dealer.Hand[i]);

		if (i >= Dealer.PublicIndex)
		{
			printf("[가려진 카드]");
			continue;
		}

		if (i % 3 == 0) printf("\n");
		printf("[%s      %d]", ShapeString[(int)Shape].c_str(), Val);
	}
	printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

void PrintAmount(int Amount)
{
	printf("패의 합은 %d 입니다\n\n", Amount);
}

void PrintHand(BlackJackPlayer& Player, BlackJackDealer& Dealer)
{
	system("cls");
	PrintPlayerHand(Player);
	PrintDealerHand(Dealer);
}

ECardShape CalcCardShape(int Card)
{
	return ECardShape(Card / NumOfCardInOnShape);
}

int CalcCardVal(int Card)
{
	return (Card % NumOfCardInOnShape) + 1;
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

void GetCard(int* InHand, int& InHandLen)
{
	InHand[InHandLen++] = TrumpCard[CardIndex++];
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

int CalcCardAmount(int* InHand, int& InHandLen)
{
	int Amount = 0;

	for (int i = 0; i < InHandLen; i++)
	{
		int AceCnt = 0;
		int CardValue = (InHand[i] % NumOfCardInOnShape) + 1;

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

	}


	return Amount;
}

void Homework02_Run()
{
	/*
	블랙잭 만들기
		게임 목표
			두 카드의 합이 21에 가깝게 만들되, 21을 넘지 않는 것이 목표
			21을 초과하면(버스트, Bust)  즉시 패배
			배팅은 없음
		카드의 값
			2~10: 카드 숫자 그대로 점수.
			J(잭), Q(퀸), K(킹): 각각 10점.
			A(에이스): 1점 또는 11점(유리한 쪽으로 자동 선택).
		게임 진행 절차
			초기 배분
				딜러와 플레이어 모두 2장씩 카드를 받음.
				플레이어의 카드는 두 장 모두 공개.
				딜러는 한 장은 공개(오픈 카드), 한 장은 비공개(홀 카드).
		플레이어 턴
			플레이어가 먼저 행동.
			선택지:
				Hit(히트): 카드를 한 장 더 받음.
				Stand(스탠드): 더 이상 카드를 받지 않고 멈춤.
			플레이어가 21을 초과하면(버스트) 즉시 패배.
		딜러 턴
			플레이어가 스탠드를 하면 딜러 차례.
			딜러는 자신의 카드 합이 17 이상이 될 때까지 계속 히트(카드 받기)해야 함.
				A가 포함된 "소프트 17"(A+6=7 또는 17)도 멈춤.
			17 이상이면 멈추고, 21을 넘으면 딜러 패배.
		승패 판정
			버스트가 아닌 경우, 점수 비교.
				플레이어가 21에 더 가까우면 승리.
				동점이면 무승부(Push).
				딜러가 더 가까우면 패배.
			블랙잭: 처음 받은 두 장이 A + 10(또는 J, Q, K)이면 블랙잭. 일반적으로 블랙잭이 단순 21점보다 우선함.
	*/
	printf("\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃       2. 블랙잭 만들기        ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");



	BlackJackPlayer Player;
	BlackJackDealer Dealer;


	//트럼프 카드 초기화
	for (int i = 0; i < NumOfTrumpCard; i++)
	{
		TrumpCard[i] = i;
	}

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


	/*
	반복
		- 카드패 계산
		- 받을지 여부 입력
			- 받은경우
				- 카드를 받음
			- 안받은경우
				- 반복문 탈출
	*/

	bool IsStand = false;
	bool IsPlayerLose = false;

	printf("당신의 차례!\n");
	while (IsStand == false)
	{
		int PlayerAmount = CalcCardAmount(Player.Hand, Player.HandLen);
		//플레이어 턴에는 아직 가려진 패가 있음
		int DealerAmount = CalcCardAmount(Dealer.Hand, Dealer.PublicIndex);

		printf("당신 패의 합 : %d\n", PlayerAmount);
		printf("딜러 패의 합 : %d\n\n", DealerAmount);

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

		if (Input == 2)
		{
			IsStand = true;
			break;
		}

		system("cls");
		printf("Hit를 선택해 새 카드를 받습니다\n");
		GetEnter();
		GetCard(Player.Hand, Player.HandLen);
		PrintHand(Player, Dealer);
	}

	// 플레이어 패배시 종료
	if (IsPlayerLose) return;
	/*
	┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
	┃           딜러 턴				┃
	┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
	*/
	// 다음을 반복
	// 17이상까지 카드를 받는다.
	// 이 과정에서 21 넘으면 패배



	/*
	딜러의 가려졌던 하나 공개
	반복
		- 카드패 계산
		- 21 넘으면 패배
		- 17보다 작은 경우

	*/
	// 딜러의 공개범위를 끝까지 늘림.
	Dealer.PublicIndex = Dealer.HandLen + 1;
	int PlayerAmount = CalcCardAmount(Player.Hand, Player.HandLen);
	int DealerAmount = 0;
	bool IsDealerLose = false;

	system("cls");
	PrintHand(Player, Dealer);

	do
	{
		DealerAmount = CalcCardAmount(Dealer.Hand, Dealer.PublicIndex);
		printf("당신 패의 합 : %d\n", PlayerAmount);
		printf("딜러 패의 합 : %d\n\n", DealerAmount);

		if (CheckEndCondition(DealerAmount))
		{
			printf("딜러의 버스트... 승리하였습니다.\n");
			IsDealerLose = true;
			GetEnter();
			break;
		}

		system("cls");
		printf("딜러가 새 카드를 받습니다\n");
		GetEnter();
		GetCard(Dealer.Hand, Dealer.HandLen);
		PrintHand(Player, Dealer);

	} while (DealerAmount < 17);

	if (IsDealerLose) return;
	/*
	┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
	┃          사후 판정			┃
	┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
	*/

	// 여기까지 온건 둘 다 버스트가 아님
	// 21에 가까운쪽이 승리
	// 같으면 무승부
	//	- 둘다 21점에 한쪽만 블랙잭이면 블랙잭인 쪽 승리
	PlayerAmount = CalcCardAmount(Player.Hand, Player.HandLen);
	DealerAmount = CalcCardAmount(Dealer.Hand, Dealer.PublicIndex);

	int PlayerFinalScore = WinningScore - PlayerAmount;
	int DealerFinalScore = WinningScore - DealerAmount;

	printf("당신 패의 합 : %d\n", PlayerAmount);
	printf("딜러 패의 합 : %d\n\n", DealerAmount);

	if (PlayerFinalScore < DealerFinalScore)
		printf("\n\n 당신의 승리! \n\n");
	else if (PlayerFinalScore > DealerFinalScore)
		printf("\n\n 딜러의 승리...! \n\n");
	else if (PlayerFinalScore == DealerFinalScore)
		printf("\n\n 무승부! \n\n");

	// 처음 받은 두장이 A+10(10, j, q, k)이면 블랙잭
}