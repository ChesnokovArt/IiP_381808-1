#pragma once
#include "Client.h"
#include "Depozit.h"

// предоставляет доступ к клиентам и их депозитам
// класс-обертка для Client Depozit
class ProCenter
{
public:
	Depozit * depozits;
	int numDepoz;
	Client * clients;
	int numClients;
	// добавление клиента в массив
	void AddClient(Client cl);
	// добавление депозита в массив
	void AddDepozit(Depozit d);
	// удалить депозит из массива по айди владельца
	void DeleteDepozit(int id);
private:
	// на сколько депозитов/клиентов зарезервировано памяти
	int numDepozReserved, numClientsReserved;
public:
	// работа с файлами
	friend istream & operator>>(istream& in, ProCenter& pc);
	friend ostream & operator<<(ostream& out, const ProCenter& pc);
	ProCenter();
	~ProCenter();
};

istream & operator>>(istream& in, ProCenter& pc);
ostream & operator<<(ostream& out, const ProCenter& pc);