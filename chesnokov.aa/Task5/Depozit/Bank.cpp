#include "Bank.h"
#include <fstream>
#include <iostream>

bool Bank::LogIn(int id, string pas)
{
	// если до этого кто то был авторизован, забываем о нем
	curClient = nullptr;
	for (int i = 0; i < database.numClients; i++)
	{
		if (database.clients[i].ID == id && database.clients[i].Password == pas)
		{
			curClient = &database.clients[i];
			return true;
		}
	}
	return false;
}

void Bank::PrintAvaibleDepozits()
{
	if (curClient == nullptr) throw NotAuthorized;
	cout << "До 100 т.р.:\n";
	cout << "На 3 меc.: " << gPercentageTable[0][0] << "%, ";
	cout << "На 6 мес.: " << gPercentageTable[0][1] << "%, ";
	cout << "На 1 год : " << gPercentageTable[0][2] << "%\n";
	if (curClient->Money > 100000)
	{
		cout << "От 100 до 500 т.р.:\n";
		cout << "На 3 меc.: " << gPercentageTable[1][0] << "%, ";
		cout << "На 6 мес.: " << gPercentageTable[1][1] << "%, ";
		cout << "На 1 год : " << gPercentageTable[1][2] << "%\n";
	}
	if (curClient->Money > 500000)
	{
		cout << "От 500 т.р. до 1 млн.\n";
		cout << "На 3 меc.: " << gPercentageTable[2][0] << "%, ";
		cout << "На 6 мес.: " << gPercentageTable[2][1] << "%, ";
		cout << "На 1 год : " << gPercentageTable[2][2] << "%\n";
	}
}

bool Bank::CheskDepozit()
{
	if (curClient == nullptr) throw NotAuthorized;
	for (int i = 0; i < database.numDepoz; i++)
	{
		if (database.depozits[i].ownerid == curClient->ID) return true;
	}
	return false;
}

bool Bank::OpenDepozit(int numMonth, int money)
{
	if (curClient == nullptr) throw NotAuthorized;
	// если депозит уже открыт или недостаточно денег на счету то отказать в депозите
	if (CheskDepozit() || money > curClient->Money)
	return false;
	Depozit temp;
	temp.Capital = 0;
	temp.InitialMoney = money;
	curClient->Money -= money;
	temp.ownerid = curClient->ID;
	temp.StartMonth = curMonth;

	if (money > 500000) temp.Range = From500To1M;
	else if (money > 100000) temp.Range = From100To500;
	else temp.Range = UpTo100;

	if (numMonth >= 12) temp.Period = Period1Year;
	else if (numMonth >= 6) temp.Period = Period6Month;
	else temp.Period = Period3Month;

	temp.Percentage = gPercentageTable[(int)temp.Range][(int)temp.Period];
	database.AddDepozit(temp);
	return true;
}

void Bank::PrintDepozitInfo()
{
	if (curClient == nullptr) throw NotAuthorized;
	// ищем нужный депозит
	int i;
	for (i = 0; i < database.numDepoz; i++)
	{
		if (database.depozits[i].ownerid == curClient->ID) break;
	}
	if (i == database.numDepoz)
	{
		cout << "Депозит не открыт\n";
		return;
	}
	cout << "Начальная сумма: " << database.depozits[i].InitialMoney << endl;
	cout << "Доступно для снятия: " << database.depozits[i].Capital << endl;
	cout << "Прошло месяцев: " << curMonth - database.depozits[i].StartMonth << endl;
	cout << "Процентная ставка: " << database.depozits[i].Percentage << '%' << endl;
}

void Bank::TakeCapital()
{
	if (curClient == nullptr) throw NotAuthorized;
	// ищем нужный депозит
	int i;
	for (i = 0; i < database.numDepoz; i++)
	{
		if (database.depozits[i].ownerid == curClient->ID) break;
	}
	// депозит не открыт
	if (i == database.numDepoz) return;
	curClient->Money += database.depozits[i].Capital;
	database.depozits[i].Capital = 0;
}

bool Bank::CloseDepozit()
{
	if (curClient == nullptr) throw NotAuthorized;
	// ищем нужный депозит
	int i;
	for (i = 0; i < database.numDepoz; i++)
	{
		if (database.depozits[i].ownerid == curClient->ID) break;
	}
	// депозит не открыт
	if (i == database.numDepoz) return false;
	int m;
	switch (database.depozits[i].Period)
	{
	case Period3Month:
		m = 3;
		break;
	case Period6Month:
		m = 6;
		break;
	case Period1Year:
		m = 12;
		break;
	}
	// не пришло время для закрытия
	if (curMonth - database.depozits[i].StartMonth < m) return false;
	// возвращаем деньги на счет
	curClient->Money += database.depozits[i].Capital + database.depozits[i].InitialMoney;
	database.DeleteDepozit(database.depozits[i].ownerid);
	return true;
}

void Bank::NextMonth()
{
	curMonth++;
	for (int i = 0; i < database.numDepoz; i++)
	{
		// начисляем проценты на депозит
		database.depozits[i].Capital += database.depozits[i].InitialMoney *
			(database.depozits[i].Percentage / 1200);
	}
}

Bank::Bank()
{
	curClient = nullptr;
	// при создании объекта банка считываем из файла данные
	ifstream fin("database.txt");
	fin >> curMonth;
	fin >> database;
	fin.close();
}

Bank::~Bank()
{
	//// сохраняем изменённые данные
	//ofstream fout("database.txt");
	//fout << curMonth << endl;
	//fout << database;
	//fout.close();
}
