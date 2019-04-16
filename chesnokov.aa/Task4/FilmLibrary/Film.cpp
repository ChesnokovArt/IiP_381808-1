#pragma once
#include "Film.h"
#include <iostream>
void printdate(const Date& date)
{
	cout << date.dayOfMonth << "." << date.month << "." << date.year << endl;
}
bool operator==(const Date& left, const Date& right)
{
	if ((left.year == right.year) && (left.month == right.month)
		&& (left.dayOfMonth == right.dayOfMonth)) return true;
	return false;
}

bool operator>(const Date& left, const Date& right)
{
	if (left.year > right.year) return true;
	else if (left.year == right.year && left.month > right.month) return true;
	else if (left.year == right.year && left.month == right.month
		&& left.dayOfMonth > right.dayOfMonth) return true;
	return false;
}

bool operator<(const Date& left, const Date& right)
{
	if (left.year < right.year) return true;
	else if (left.year == right.year && left.month < right.month) return true;
	else if (left.year == right.year && left.month == right.month
		&& left.dayOfMonth < right.dayOfMonth) return true;
	return false;
}

bool operator >=(const Date& left, const Date& right)
{
	return (left > right || left == right);
}
bool operator <=(const Date& left, const Date& right)
{
	return (left < right || left == right);
}

istream & operator>>(istream & in, Film & temp)
{
	cout << "Введите название: ";
	in >> temp.name;
	cout << "Введите продюсера: ";
	in >> temp.producer;
	cout << "Введите сценариста: ";
	in >> temp.scenarist;
	cout << "Введите композитора: ";
	in >> temp.composer;
	cout << "Введите cборы: ";
	in >> temp.fee;
	cout << "Введите день выхода: ";
	in >> temp.releaseDate.dayOfMonth;
	cout << "Введите месяц выхода: ";
	in >> temp.releaseDate.month;
	cout << "Введите год выхода: ";
	in >> temp.releaseDate.year;
	return in;
}



void Film::PrintFilm() const
{
	cout << name << ", " << producer << ", " << scenarist << ", " << fee << ", ";
	printdate(releaseDate);
}

Film::Film()
{
	fee = 0;
}
