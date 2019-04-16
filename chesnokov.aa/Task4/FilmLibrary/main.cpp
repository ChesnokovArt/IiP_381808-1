#include "FilmLibrary.h"
#include "Film.h"
#include <locale>
#include <iostream>
#include <fstream>
#include "LinkedList.h"
using namespace std;

void printdate(const Date& date);

int main()
{
	setlocale(LC_ALL, "RUS");
	FilmLibrary MyFilms;
	int c;
	ofstream fout;
	ifstream fin;
	do
	{
		cout << "1) Вывести мою коллекцию фильмов" << endl;
		cout << "2) Добавить фильм в коллекцию" << endl;
		cout << "3) Изменить фильм по названию" << endl;
		cout << "4) Найти фильм по названию и году выхода в прокат" << endl;
		cout << "5) Все фильмы заданного режиссера" << endl;
		cout << "6) Все фильмы вышедшие в прокат в данном году" << endl;
		cout << "7) Самые продаваемые фильмы" << endl;
		cout << "8) Самые продаваемые фильмы в данном году" << endl;
		cout << "9) Узнать количество фильмов в колекции" << endl;
		cout << "10) Удалить фильм по названию" << endl;
		cout << "11) Считать с заданного файла" << endl;
		cout << "12) Сохранить коллецию на диске" << endl;
		cout << "0)  Выход" << endl;
		
		cin >> c;
		// временные переменные
		Film temp;
		const Film* collection;
		string tempname;
		int ind;
		unsigned int tempyear;

		switch (c)
		{
		case 1:
			cout << MyFilms;
			cout << "___________________" << endl;
			break;
		case 2:
			cin >> temp;
			MyFilms.AddFilm(temp);
			cout << "___________________" << endl;
			break;
		case 3:
			cout << "Введите название фильма и год выхода , которого хотите изменить: ";
			cin >> tempname;
			cin >> tempyear;
			cin >> temp;
			MyFilms.ChangeFilm(tempname, tempyear, temp);
			cout << "___________________" << endl;
			break;
		case 4:
			cout << "Введите название фильма и год выхода, которого хотите найти: ";
			cin >> tempname;
			cin >> tempyear;
			temp = MyFilms.FindFilm(tempname, tempyear, ind)->data;
			cout << "Найден фильм на позиции: " << ind << endl;
			temp.PrintFilm();
			cout << "___________________" << endl;
			break;
		case 5:
			cout << "Фильмы какого режиссера желаете?: ";
			cin >> tempname;
			collection = MyFilms.FindByProd(tempname, ind);
			for (int i = 0; i < ind; i++)
			{
				collection[i].PrintFilm();
			}
			cout << "___________________" << endl;
			break;
		case 6:
			cout << "Фильмы какого года желаете?: ";
			cin >> tempyear;
			collection = MyFilms.FindByYear(tempyear, ind);
			for (int i = 0; i < ind; i++)
			{
				collection[i].PrintFilm();
			}
			cout << "___________________" << endl;
			break;
		case 7:
			cout << "Сколько самых дорогих фильмов желаете?: ";
			cin >> ind;
			collection = MyFilms.FindeMaxByFee(ind);
			for (int i = 0; i < ind; i++)
			{
				collection[i].PrintFilm();
			}
			cout << "___________________" << endl;
			break;
		case 8:
			cout << "Сколько самых дорогих фильмов желаете?: ";
			cin >> ind;
			cout << "А какого года?: ";
			cin >> tempyear;
			collection = MyFilms.FindeMaxByFeeByYear(tempyear, ind);
			for (int i = 0; i < ind; i++)
			{
				collection[i].PrintFilm();
			}
			cout << "___________________" << endl;
			break;
		case 9:
			cout << "Фильмов в коллекции: " << MyFilms.NumberOfFilms() << endl;
			cout << "___________________" << endl;
			break;
		case 10:
			cout << "Какой фильм желаете удалить?: ";
			cin >> tempname;
			MyFilms.DeleteFilm(tempname);
			cout << "___________________" << endl;
			break;
		case 11:
			cout << "C какого файла считать?: ";
			cin >> tempname;
			fin.open(tempname);
			if (!fin.is_open()) break;
			fin >> MyFilms;
			fin.close();
			cout << "___________________" << endl;
			break;
		case 12:
			cout << "В какой файл записать?: ";
			cin >> tempname;
			fout.open(tempname);
			fout << MyFilms;
			fout.close();
			cout << "___________________" << endl;
			break;
		default:
			break;
		}
	} while (c != 0);
	

	
}
