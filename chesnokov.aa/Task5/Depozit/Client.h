#pragma once
#include <string>
using namespace std;

// представляет клиента в банке
// авторизация происходит по ID и password
struct Client
{
	unsigned int ID;      // номер счета клиента от 0001 до 9999
	string Surname;       // Фамилия
	string Name;          // Имя
	string Patronymic;    // Отчество
	unsigned int Money;   // доступные деньги на счету
	string Password;      // пароль >3 символов
};

// перегруженные операции ввода вывода в поток
istream& operator>>(istream& in, Client& cl);
ostream& operator<<(ostream& out, const Client& cl);