#include <iostream>
#include "Homework01.h"

using namespace std;

bool IsLeapYear(int Years)
{

	bool Res = false;

	// 연도가 4와 100의 배수 이면서 4
	if ( ( (Years % 4) == 0) && ( (Years % 100) != 0)  || (Years % 400 == 0))
	{
		Res = true;
	}
	else
	{
		Res = false;
	}

	return Res;
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

	
	// 3. 입력받은 연도까지 연도, 월, 일을 더해준다.
	// 4. 누적된 값을 7로 나눠 인덱스를 구한다.
	// 5. 요일 스트링에서 요일을 출력한다.

	string DayofWeek[7] =
	{
		{"일"},
		{"월"},
		{"화"},
		{"수"},
		{"목"},
		{"금"},
		{"토"}
	};

	int Year = 1;
	int Month = 1;
	int Day = 1;

	int InputYear = 0;
	int InputMonth = 0;
	int InoputDay = 0;

	printf("요일을 알고 싶은 날짜를 입력해주세요 (년 월 일) : ");

	cin >> InputYear >> InputMonth >> InoputDay;

	// 입력받은 연도의 직전까지 계산
	while (Year < InputYear)
	{
		// 0. 현재연도가 윤년인지 확인한다
		if (IsLeapYear(Year))
		{
			// 0-1. 현재연도가 윤년이면 1년은 366일 
			Day += 366 % 7;
		}
		else
		{
			// 0-2. 현재연도가 윤년이 아니면 1년은 365일
			Day += 365 % 7;
		}

		++Year;
	}

	while (Month < InputMonth)
	{
		Day += DayOfMonth[Month] % 7;;
		// 해당년도가 윤년이고 해당월이 2월 이면 1일 더해준다.
		if (Month == FEB && IsLeapYear(Year))
			Day++;

		++Month;
	}

	Day += InoputDay - 1;
	Day %= 7;
		

	printf("%d년 %d월 %d일 은 %s요일 입니다.\n", InputYear, InputMonth, InoputDay, DayofWeek[Day].c_str());





}