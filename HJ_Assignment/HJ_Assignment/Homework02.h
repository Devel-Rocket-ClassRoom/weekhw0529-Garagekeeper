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
const int BlackJackScore = -1;
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
	std::string Name = "당신";
	int Amount = 0;
	int PublicIndex = HandMAxCapacity;
	int HandLen = 0;
	int Hand[HandMAxCapacity] = { 0, };
};

struct BlackJackDealer
{
	std::string Name = "딜러";
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
/// <summary>
/// 1번 2번을 고르는 입력을 받는 함수
/// </summary>
/// <returns></returns>
int GetOneOrTwoInput();

/// <summary>
/// 플레이어와 딜러의 총합을 출력
/// </summary>
/// <param name="PlayerAmount">플레이어의 총합</param>
/// <param name="DealerAmount">딜러의 총합</param>
void PrintAmount(int PlayerAmount, int DealerAmount);

/// <summary>
/// 플레이어와 딜러의 손패를 출력하는 함수
/// </summary>
/// <param name="Player">플레이어 구조체</param>
/// <param name="Dealer">딜러 구조체</param>
void PrintHand(BlackJackPlayer& Player, BlackJackDealer& Dealer);

/// <summary>
/// 손패를 출력하는 함수
/// </summary>
/// <param name="Name">이름</param>
/// <param name="InHand">손패 배열</param>
/// <param name="InHandLen">손배 길이</param>
/// <param name="PublicIndex">공개 범위</param>
void PrintHand(std::string Name, int* InHand, int& InHandLen, int PublicIndex = HandMAxCapacity);

/// <summary>
/// 트럼프 카드의 모양을 계산하는 함수
/// </summary>
/// <param name="Card">카드 번호</param>
/// <returns></returns>
ECardShape CalcCardShape(int Card);

/// <summary>
/// 트럼프 카드의 숫자를 계산하는 함수
/// </summary>
/// <param name="Card">카드 번호</param>
/// <returns></returns>
int CalcCardVal (int Card);

/// <summary>
/// 손패의 총합의 계산해 봔환하는 함수
/// </summary>
/// <param name="InHand">손패 배열의 합</param>
/// <param name="InHandLen">블랙잭 규칙에 맞는 총합</param>
/// <returns></returns>
int CalcCardAmount(int* InHand, int& InHandLen);

/// <summary>
/// 카드를 손패에 한 장받는 함수
/// </summary>
/// <param name="InHand">손패 배열</param>
/// <param name="InHandLen">손패 배열 길이</param>
void GetCard(int* InHand, int& InHandLen);

/// <summary>
/// 버스트가 발생했는지 확인하는 함수
/// </summary>
/// <param name="Amount"></param>
/// <returns></returns>
bool CheckEndCondition(int Amount);

/// <summary>
/// 초기 배분을 수행하는 함수
/// </summary>
/// <param name="Player">플레이어 구조체</param>
/// <param name="Dealer">딜러 구조체</param>
void StartPhase(BlackJackPlayer& Player, BlackJackDealer& Dealer);

void Homework02_Run();
