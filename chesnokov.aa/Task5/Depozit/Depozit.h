#pragma once
#include "Client.h"

// периоды на которые возможны депозиты
// их числовые значению соответсвуют кол-ву месяцев
enum Period
{
	Period3Month,
	Period6Month,
	Period1Year 
};
enum Range
{
	UpTo100,
	From100To500,
	From500To1M
};

// представляет депозит
struct Depozit
{
	int ownerid;      // ID владельца депозита
	float Percentage; // процентная ставка
	Period Period;    // на какой период открыт депозит
	int StartMonth;   // месяц открытия депозита
	Range Range;      // диапазон
	int InitialMoney; // первоначальная сумма вклада
	int Capital;      // накопленный с процентов деньги
};

// перегруженные операции ввода вывода в поток
istream& operator>>(istream& in, Depozit& d);
ostream& operator<<(ostream& out, const Depozit& d);
// таблица процентов
const float gPercentageTable[3][3] =
{
	           // 3month-----6month----1year
	/*0-100*/    {3.2f,      3.8f,     4.3f},
	/*100-500*/  {3.9f,      4.5f,     5.0f},
	/*500-1m*/   {4.2f,      5.0f,     5.5f}
};

