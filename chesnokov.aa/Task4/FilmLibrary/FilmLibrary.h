#pragma once
#include "LinkedList.h"
#include "Film.h"
#include <iostream>
using namespace std;

/* класс, хранящий информацию о фильмах
 * фильмы хранятся упорядочено по годам и по названию
 * т.е. в рамках одного года фильмы упорядочены по алфавиту
 */
// ВОЗМОЖНОСТИ:
/*
1) добавить фильм
2) изменить данные фильма по названию
3) найти фильм по названию и году
4) выдать все фильмы заданного режиссера
5) выдать все фильмы вышедвшие в прокат в данном году
6) выдать заднное число фильмов с наибольшими сборами 
7) выдать заднное число фильмов с наибольшими сборами в выбранном году
8) узнать текущее число фильмов
9) удалить фильм по названию
10)считать с файла, записать в файл
*/
class FilmLibrary
{
private:
	// используется связный список для хранения фильмов,
	// так как он позволяет быстро добавлять удалять из середины списка
	// элементы, при этом не используя буфферы 
	LinkedList<Film> m_films;
public:
	// добавляет фильм с учетом сортировки
	void AddFilm(const Film& film);
	// поиск фильма по имени и году выхода
	// индекс фильма возвращается в outIndex
	Node<Film>* FindFilm(string name, int year, int& outIndex);
	// поиск фильма по имени 
	// индекс фильма возвращается в outIndex
	Node<Film>* FindFilm(string name, int& outIndex);
	// изменение фильма по имени и году на указанный фильм
	void ChangeFilm(string name, int year, const Film& newFilm);
	// выдать все фильмы заданного режиссера
	// в outSize возвращается количество таких фильмов 
	const Film* FindByProd(const string producer, int& outSize);
	// выдать все фильмы вышедшие в указанном году
	// в outSize возвращается количество таких фильмов 
	const Film* FindByYear(int year, int& outSize);
	// выдать заданное число фильмов с наибольшими сборами
	// число найденных фильмов возвращается параметром IOnum
	const Film* FindeMaxByFee(int& IOnum);
	// выдать заданное число фильмов с наибольшими сборами в заданный год
	// число найденных фильмов возвращается параметром IOnum
	const Film* FindeMaxByFeeByYear(int year, int& IOnum);
	void DeleteFilm(string name);
	// узнать текущее число фильмов
	int NumberOfFilms() const { return m_films.Count(); }
	void TESTPRINT();
	// перегрузка операторов ввода/вывода
	friend istream& operator>> (istream& in, FilmLibrary& lib);
	friend ostream& operator<< (ostream& out, const FilmLibrary& lib);
public:
	FilmLibrary();
	~FilmLibrary();
};

istream& operator>> (istream& in, FilmLibrary& lib);
ostream& operator<< (ostream& out, const FilmLibrary& lib);