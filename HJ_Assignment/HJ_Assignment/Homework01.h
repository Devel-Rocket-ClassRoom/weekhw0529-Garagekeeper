#pragma once
#include <string>


const int MONTHLEN = 13;
const int NumOfDayInWeek = 7;
enum EMonth
{
	JAN = 1,
	FEB,
	MAR,
	APR,
	MAY,
	JUN,
	JUL,
	AUG,
	SEP,
	OCT,
	NOV,
	DEC,
	LENGTH = 13,
};

const int DayOfMonth[MONTHLEN] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


/// <summary>
/// 주어진 연도가 윤년인지 여부를 판정합니다.
/// </summary>
/// <param name="Years">판정할 연도(예: 2024)를 나타내는 정수.</param>
/// <returns>연도가 윤년이면 true, 그렇지 않으면 false.</returns>
bool IsLeapYear(int Years);

/// <summary>
/// 날짜를 입력받는 함수
/// </summary>
void GetInput(int& InYear, int& Month, int& Day);

/// <summary>
/// 1년 1월 1일부터 입력 날짜까지 몇일이 지났는지 계산해서 반환하는 함수
/// </summary>
/// <param name="InYear">입력한 연도</param>
/// <param name="InMonth">입력한 월</param>
/// <param name="InDay">입력한 일</param>
/// <returns>경과일(int) 반환</returns>
int CalcDay(int InYear, int InMonth, int InDay);

/// <summary>
/// 결과를 출력하는 함수
/// </summary>
/// <param name="InYear">입력한 연도</param>
/// <param name="InMonth">입력한 월</param>
/// <param name="InDay">입력한 일</param>
/// <param name="ResDay">최종 계산된 누적일</param>
void PrintResult(int InYear, int InMonth, int InDay, int ResDay);

void Homework01_Run();