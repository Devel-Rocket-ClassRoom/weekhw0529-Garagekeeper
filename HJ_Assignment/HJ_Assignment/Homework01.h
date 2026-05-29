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

void Homework01_Run();