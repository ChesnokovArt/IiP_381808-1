#include "Depozit.h"
istream& operator>>(istream& in, Depozit& d)
{
	int per, ran;
	// cчитываем в формате:
	//    ID----------Начальная сумма----Накопленная--месяц вложения
	in >> d.ownerid >> d.InitialMoney >> d.Capital >> d.StartMonth
		//период--диапозон суммы вклада
		>> per    >> ran;
	d.Period = (Period)per;
	d.Range = (Range)ran;
	// по таблице находим процентную ставку
	d.Percentage = gPercentageTable[ran][per];
	return in;
}
ostream& operator<<(ostream& out, const Depozit& d)
{
	// выводим в формате:
	//    ID--------------------Начальная сумма----------Накопленная---------месяц вложения
	out << d.ownerid << ' ' << d.InitialMoney << ' ' << d.Capital << ' ' << d.StartMonth << ' '
		//период-------------------диапозон суммы вклада
		<< (int)d.Period << ' ' << (int)d.Range << endl;
	return out;
}