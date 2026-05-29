#include <iostream>
#include "Homework01.h"

using namespace std;

const string DayofWeekWString[7] =
{
	{"일"},
	{"월"},
	{"화"},
	{"수"},
	{"목"},
	{"금"},
	{"토"}
};

bool IsLeapYear(int Years)
{
	bool Res = false;

	if ( ( (Years % 4) == 0) && ( (Years % 100) != 0)  || (Years % 400 == 0))
		Res = true;

	return Res;
}

void GetInput(int& InYear, int& Month, int& Day)
{
	printf("요일을 알고 싶은 날짜를 입력해주세요 (년 월 일) : ");

	cin >> InYear >> Month >> Day;
}

int CalcDay(int InYear, int InMonth, int InDay)
{
	{
		int YearAmount = 1;
		int MonthAmount = 1;
		int DayAmount = 1;

		// 입력받은 연도의 직전까지 Day 누적
		while (YearAmount < InYear)
		{
			// 0-1. 1년은 365일
			DayAmount += 365;
			
			// 0-2. 현재연도가 윤년이면 1년은 366일 
			if (IsLeapYear(YearAmount))
				++DayAmount;

			// 다음 연도로
			++YearAmount;
		}

		// 입력받은 연도의 직전 월까지 Day 누적
		while (MonthAmount < InMonth)
		{
			// 해당 월의 일수를 더한다.
			DayAmount += DayOfMonth[MonthAmount];

			// 해당년도가 윤년이고 해당월이 2월 이면 1일 더해준다.
			if (MonthAmount == FEB && IsLeapYear(YearAmount))
				DayAmount++;

			// 다음 월로
			++MonthAmount;
		}

		// 같은 연도, 같은 월까지 왔으니 남은 일자를 더해준다.
		// 누적된 값을 7로 나눠 인덱스를 구한다.
		DayAmount += InDay - 1;
		return DayAmount;
	}
}

void PrintResult(int InYear, int InMonth, int InDay, int ResDay)
{
	// 요일 스트링에서 요일을 출력한다.
	printf("%d년 %d월 %d일은 %s요일 입니다.\n", InYear, InMonth, InDay, DayofWeekWString[ResDay].c_str());
}

void Homework01_Run()
{
	/*
	요일 구하기
		1년 1월 1일(월요일)을 기준으로 입력한 날짜까지 며칠이 지났는지 계산한 후, 7로 나눈 나머지로 요일을 구하기.
		윤년도 올바르게 처리할 것
		입력받은 연, 월, 일을 기준으로 요일을 출력.
			예시 입력: 2026 5 29 → 결과: 금요일
		Homework01_Run(); 함수로 실행 가능해야 함.
	*/
	printf("\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃       1. 요일 구하기          ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	int InputYear = 0;
	int InputMonth = 0;
	int InoputDay = 0;

	// 입력을 받는다.
	GetInput(InputYear, InputMonth, InoputDay);

	// 1/1/1 부터 입력 날자까지의 누적일을 얻는다
	int Day = CalcDay(InputYear, InputMonth, InoputDay);

	// 누적일을 7로 나눠 요일 정보를 얻는다.
	Day %= NumOfDayInWeek;
	
	// 요일을 출력한다.
	PrintResult(InputYear, InputMonth, InoputDay, Day);

}