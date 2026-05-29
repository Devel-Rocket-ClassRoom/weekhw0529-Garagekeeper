#pragma once

// 트럼프카드 52장
const int NumOfTrumpCard = 52;
// 딜러,플레이어 둘 다 12장 이상 받으면 21점 넘는다.
const int HandMAxCapacity = 12;

// 한 문양에 카드가 몇개 있는지 (A~K)
const int NumOfCardInOnShape = 13;

// A~K 까지 카드 중 제일 큰 (K)의 숫자
const int MaxCardValue = 13;

// 블랙잭을 뽑은 경우 표시
const int BlackJackScore = INT32_MAX;
// 승리 기준 점수
const int WinningScore = 21;

// ACE의 선택 가능한 포인트
const int AceHighPoint = 11;
const int AceLowPoint = 1;

// 처음 받는 카드 개수
const int InitialCardNum = 2;

enum ECardShape
{
	Spade = 0,
	Clover,
	Heart,
	Diamond,
	CardShapeLen,
};

enum ELetterCard
{
	AceCard = 1,
	JCard = 11,
	QCard = 12,
	KCard = 13,
};

struct BlackJackPlayer
{
	
	int Amount = 0;
	int PublicIndex = 2;
	int HandLen = 0;
	int Hand[HandMAxCapacity] = { 0, };
};

struct BlackJackDealer
{
	int Amount = 0;
	int PublicIndex = 1;
	int HandLen = 0;
	int Hand[HandMAxCapacity] = { 0, };
};


/// <summary>
/// 배열을 섞는 함수
/// </summary>
/// <param name="Array"></param>
/// <param name="Length"></param>
void FisherYatesShuffle(int* Array, int Length);

void PrintPlayerHand(BlackJackPlayer& Player);
void PrintDealerHand(BlackJackDealer& Dealer);
void PrintAmount(int Amount);
void PrintHand(BlackJackPlayer& Player, BlackJackDealer& Dealer);
ECardShape CalcCardShape(int Card);
int CalcCardVal (int Card);
bool CheckEndCondition(int Amount);

void GetEnter(bool IsPlayerTurn);
void GetCard(int* InHand, int& InHandLen);
void StartPhase(BlackJackPlayer& Player, BlackJackDealer& Dealer);

int CalcCardAmount(int* InHand, int& InHandLen);

void Homework02_Run();
