#include "Bank.h"
#include <iostream>
/*
# database.txt
20  -- текущий месяц
3  -- кол-во клиентов
2  -- кол-во депозитов
----------данные о клиентах-------
1122 Иванов Иван Иванович 100000 qwerty
1123 Петров Петр Петрович 250000 admin1234
7766 Смирнова Анна Викторовна 725000 anya322
---------данные о депозитах----------
1122 500000 50000 1 2 2
1123 100000 1200 2 1 2
*/

int main()
{
	setlocale(LC_ALL, "RUS");
	Bank myBank;
	int myID = 1122;
	string myPas = "qwerty";
	myBank.LogIn(myID, myPas);
	cout << "\nВам доступны следующие депозит(ы):\n" << endl;
	myBank.PrintAvaibleDepozits();
	cout << endl;
	myBank.PrintDepozitInfo();
	myBank.NextMonth();
	cout << "\nПрошёл месяц...\n" << endl;
	myBank.PrintDepozitInfo();
	myBank.TakeCapital();
	cout << "\nСняли накопления...\n" << endl;
	myBank.PrintDepozitInfo();
	myBank.CloseDepozit();
	cout << "\nЗакрыли депозит...\n" << endl;
	myBank.PrintDepozitInfo();
	cout << "Авторизация за Анну \n" << endl;
	myID = 7766;
	myPas = "anya322";
	myBank.LogIn(myID, myPas);
	cout << "Вам доступны следующие депозит(ы):\n" << endl;
	myBank.PrintAvaibleDepozits();
	myBank.PrintDepozitInfo();
	myBank.OpenDepozit(7, 200000);
	cout << "Открыли депозит" << endl;
	myBank.PrintDepozitInfo();
	myBank.NextMonth();
	cout << "\nПрошёл месяц...\n" << endl;
	myBank.PrintDepozitInfo();

	cin.get();
	return 0;
}