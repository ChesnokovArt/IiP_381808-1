#pragma once
#include <string>
using namespace std;

// вспомогательный класс, для представления даты
class Date
{
public:
	int year;        // год 
	int month;       // месяц от 1 до 12
	int dayOfMonth;  // день от начала месяца
	Date() : year(1900), month(1), dayOfMonth(1) {};
	Date(int y, int m, int d) : year(y), month(m), dayOfMonth(d) {};
	friend bool operator==(const Date& left, const Date& right);
	friend bool operator> (const Date& left, const Date& right);
	friend bool operator< (const Date& left, const Date& right);
	friend bool operator>=(const Date& left, const Date& right);
	friend bool operator<=(const Date& left, const Date& right);
	
};

// класс представляющий фильм
class Film
{
public:
	string name;           // имя фильма 
	string producer;       // режиссер
	string scenarist;      // сценарист
	string composer;       // композитор
	Date releaseDate;      // дата выхода в прокат
	unsigned int fee;      // кассовые сборы (в руб) 

public:
	void PrintFilm() const;
	Film();
	Film(const string& name, const string& producer, const string& scenarist,
		const string& composer, const Date& releaseDate, const int fee)
		: name(name), producer(producer), scenarist(scenarist), composer(composer),
		releaseDate(releaseDate), fee(fee) {};
	friend istream& operator>> (istream& in, Film& temp);
};

istream& operator>> (istream& in, Film& temp);
