#include "ProCenter.h"

void ProCenter::AddClient(Client cl)
{
	// если не хватает зарезервированной памяти
	if (numClients + 1 > numClientsReserved)
	{
		Client* temp = clients;
		// резервируем памяти побольше
		clients = new Client[numClients + 5];
		// копируем в новую память
		for (int i = 0; i < numClients; i++)
		{
			clients[i] = temp[i];
		}
		// добавляем в конец
		clients[numClients] = cl;
		numClients++;
	}
	else
	{
		// иначе просто добавляем в конец
		clients[numClients] = cl;
		numClients++;
	}
}

void ProCenter::AddDepozit(Depozit d)
{
	// если не хватает зарезервированной памяти
	if (numDepoz + 1 > numDepozReserved)
	{
		Depozit* temp = depozits;
		// резервируем памяти побольше
		depozits = new Depozit[numDepoz + 5];
		// копируем в новую память
		for (int i = 0; i < numDepoz; i++)
		{
			depozits[i] = temp[i];
		}
		// добавляем в конец
		depozits[numDepoz] = d;
		numDepoz++;
	}
	else
	{
		// иначе просто добавляем в конец
		depozits[numDepoz] = d;
		numDepoz++;
	}
}

void ProCenter::DeleteDepozit(int id)
{
	// находим индекс депозита 
	int i;
	for (i = 0; i < numDepoz; i++)
	{
		if (depozits[i].ownerid == id) break;
	}
	// если не было найдено нужного депозита ничего не делаем
	if (i == numDepoz) return;
	// cмещаем все депозиты после удаляемого
	for (; i < numDepoz-1; i++)
	{
		depozits[i] = depozits[i + 1];
	}
	numDepoz--;
}

ProCenter::ProCenter()
{
	numClients = numDepoz = 0;
	// нулевой указатель так как данные считываются с файла
	depozits = nullptr;
	clients = nullptr;
}

ProCenter::~ProCenter()
{
	delete[] clients;
	delete[] depozits;
}

istream & operator>>(istream & in, ProCenter & pc)
{
	// заказываем необходимую память
	in >> pc.numClients >> pc.numDepoz;
	// резервируем память с запасом
	pc.numClientsReserved = pc.numClients + 5;
	pc.numDepozReserved = pc.numDepoz + 5;
	pc.clients = new Client[pc.numClientsReserved];
	pc.depozits = new Depozit[pc.numDepozReserved];
	for (int i = 0; i < pc.numClients; i++)
	{
		in >> pc.clients[i];
	}
	for (int i = 0; i < pc.numDepoz; i++)
	{
		in >> pc.depozits[i];
	}
	return in;
}

ostream & operator<<(ostream & out, const ProCenter & pc)
{
	out << pc.numClients << endl;
	out << pc.numDepoz << endl;
	for (int i = 0; i < pc.numClients; i++)
	{
		out << pc.clients[i] << endl;
	}
	for (int i = 0; i < pc.numDepoz; i++)
	{
		out << pc.depozits[i] << endl;
	}
	return out;
}
