#pragma once
#include "ProCenter.h"
class Bank
{
private:
	
	ProCenter database;  // база данных клиентов и их депозитов
	Client* curClient;   // текущий авторизованный клиент
	int curMonth;
public:
	// авторизация клиента, возвращает false если не успешно
	bool LogIn(int id, string pas);
	// вывести доступные депзиты на экран
	void PrintAvaibleDepozits();
	// проверить на открытые депозиты
	bool CheskDepozit();
	// открыть депозит на указанный срок, переведя указанную сумму на него
	// возвращает falsr если не успешно
	bool OpenDepozit(int numMonth, int money);
	// вывести информацию о депозите
	void PrintDepozitInfo();
	// cнять накопления с депозита
	void TakeCapital();
	// закрыть депозит
	bool CloseDepozit();

	// В целях отладки симуляция течения времени
	// следующий месяц
	void NextMonth();

public:
	Bank();
	~Bank();
};

enum BankExceptions
{
	NotAuthorized
};