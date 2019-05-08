#include "Client.h"

// указатель на открытый депозит не считывается,
// пользователь класса (процессинговый центр, сам должен обрабатывать это)
istream& operator>>(istream& in, Client& cl)
{
	/* формат:
		ID   Фамилия Имя  Отчество Сумма_на_счету Пароль 
		0000 Иванов  Иван Иванович 1000000        qwerty
	*/
	in >> cl.ID >> cl.Surname >> cl.Name >> 
		cl.Patronymic >> cl.Money >> cl.Password;
	return in;
}

ostream & operator<<(ostream & out, const Client & cl)
{
	/* формат:
	0000 Иванов Иван Иванович 1000000 qwerty
	*/
	out << cl.ID << ' ' << cl.Surname << ' ' << cl.Name << ' ' <<
		cl.Patronymic << ' ' << cl.Money << ' ' << cl.Password << endl;
	return out;
}
