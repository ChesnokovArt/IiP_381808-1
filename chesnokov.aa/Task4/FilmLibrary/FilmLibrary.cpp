#include "FilmLibrary.h"

using namespace std;


void FilmLibrary::AddFilm(const Film & film)
{
	// так как фильмы хранятся упорядочено по годам и названию
	// сначало необходимо найти нужное место
	Node<Film>* currentPlace = m_films.head;
	int currentIndex = 0;
	while (currentPlace != nullptr 
		&& film.releaseDate.year < currentPlace->data.releaseDate.year)
		// cначала проходим до нужного года
	{
		currentPlace = currentPlace->p_next;
		currentIndex++;
	}
	// иначе ищем нужное лексикографическое место среди фльмов вышедших в этот год
	while (
		currentPlace != nullptr // не достигли конца списка
		&& film.releaseDate.year == currentPlace->data.releaseDate.year // до сих пор тот же год
		&& film.name > currentPlace->data.name   // проверка на то, что имя до сих пор больше по алфавитному порядку
		)
	{
		currentPlace = currentPlace->p_next;
		currentIndex++;
	}
	m_films.AddAt(film, currentIndex);
	return;
}

Node<Film> * FilmLibrary::FindFilm(string name, int year, int& outIndex)
{
	outIndex = 0;
	Node<Film>* cur = m_films.head;
	while (cur != nullptr && (cur->data.name != name || cur->data.releaseDate.year != year))
	{
		cur = cur->p_next;
		outIndex++;
	}
	// вернет nullptr если фильм не был найден
	return cur;
}

Node<Film>* FilmLibrary::FindFilm(string name, int & outIndex)
{
	outIndex = 0;
	Node<Film>* cur = m_films.head;
	while (cur != nullptr && cur->data.name != name)
	{
		cur = cur->p_next;
		outIndex++;
	}
	// вернет nullptr если фильм не был найден
	return cur;
}

void FilmLibrary::ChangeFilm(string name, int year,const Film & newFilm)
{
	int ind;
	Node<Film>* filmToChange = FindFilm(name, year, ind);
	if (filmToChange == nullptr)
	{
		// так как фильм не найден ничего не изменяем
		return;
	}
	// удаляем недействительный фильм
	m_films.DeleteAt(ind);
	// добавляем отредактированный
	AddFilm(newFilm);
	// копируем данные
	
}

const Film * FilmLibrary::FindByProd(const string producer, int & outSize)
{
	Film* res = nullptr;
	outSize = 0;
	Node<Film>* cur = m_films.head;
	// cначала считаем сколько таких фильмов всего
	while (cur != nullptr)
	{
		if (cur->data.producer == producer)
		{
			outSize++;
		}
		cur = cur->p_next;
	}
	// заказываем память
	res = new Film[outSize];
	outSize = 0;
	cur = m_films.head;
	// а теперь записываем в массив эти фильмы
	while (cur != nullptr)
	{
		if (cur->data.producer == producer)
		{
			res[outSize] = cur->data;
			outSize++;
		}
		cur = cur->p_next;
	}
	return res;
}

const Film * FilmLibrary::FindByYear(int year, int & outSize)
{
	Film* res = nullptr;
	outSize = 0;
	Node<Film>* cur = m_films.head;
	// cначала считаем сколько таких фильмов всего
	while (cur != nullptr)
	{
		if (cur->data.releaseDate.year == year)
		{
			outSize++;
		}
		cur = cur->p_next;
	}
	// заказываем память
	res = new Film[outSize];
	outSize = 0;
	cur = m_films.head;
	// а теперь записываем в массив эти фильмы
	while (cur != nullptr)
	{
		if (cur->data.releaseDate.year == year)
		{
			res[outSize] = cur->data;
			outSize++;
		}
		cur = cur->p_next;
	}
	return res;
}

const Film * FilmLibrary::FindeMaxByFee(int& IOnum)
{
	// если фильмов меньше чем пользователь запрашиваем изменяем количество
	if (IOnum > m_films.Count()) IOnum = m_films.Count();
	Film* res = new Film[IOnum]();
	Node<Film>* cur = m_films.head;
	while (cur != nullptr)
	{
		// находим подходящее место в массиве
		int ind = IOnum;
		while (cur->data.fee > res[ind - 1].fee && (ind - 1) >= 0) ind--;
		// сдвигаем менее дорогие фильмы 
		for (int i = IOnum - 1; i > ind; i--)
		{
			res[i] = res[i - 1];
		}
		if (ind < IOnum)   // если входит в текущий топ, то заменяем
		{
			res[ind] = cur->data;
		}
		cur = cur->p_next;
	}
	return res;
}

const Film * FilmLibrary::FindeMaxByFeeByYear(int year, int & IOnum)
{
	Node<Film>* cur = m_films.head;
	// находим количество фильмов заданного года
	int count = 0;
	while (cur != nullptr)
	{
		if (cur->data.releaseDate.year == year) count++;
		cur = cur->p_next;
	}
	cur = m_films.head;
	// если фильмов меньше чем пользователь запрашиваем изменяем количество
	if (IOnum > count) IOnum = count;
	Film* res = new Film[IOnum]();
	
	while (cur != nullptr 
		&& cur->data.releaseDate.year >= year  // так как фильмы отсортированы по дате
		)
	{
		// если не дошли до нужного года пропускаем итерацию
		if (cur->data.releaseDate.year != year)
		{
			cur = cur->p_next;
			continue;
		}
		// находим подходящее место в массиве
		int ind = IOnum;
		while (cur->data.fee > res[ind - 1].fee && (ind - 1) >= 0) ind--;
		// сдвигаем менее дорогие фильмы 
		for (int i = IOnum - 1; i > ind; i--)
		{
			res[i] = res[i - 1];
		}
		if (ind < IOnum)   // если входит в текущий топ, то заменяем
		{
			res[ind] = cur->data;
		}
		cur = cur->p_next;
	}
	return res;
}

void FilmLibrary::DeleteFilm(string name)
{
	int index;
	FindFilm(name, index);
	m_films.DeleteAt(index);
}

void FilmLibrary::TESTPRINT()
{
	// проходим по всем элементам
	Node<Film>* cur = m_films.head;
	while (cur != nullptr)
	{
		cout << cur->data.name << " ";
		cur = cur->p_next;
	}
	cout << endl;
}

FilmLibrary::FilmLibrary()
{
	
}

FilmLibrary::~FilmLibrary()
{
}

istream & operator>>(istream & in, FilmLibrary & lib)
{
	int count;
	in >> count;
	string n, p, s, c;
	int f, dom, m, y;
	for (int i = 0; i < count; i++)
	{
		in >> n >> p >> s >> c >> f;
		in.get();  // пропускаем P
		in >> dom;
		in.get();  // пропускаем точку
		in >> m;
		in.get();
		in >> y;
		Film curFilm(n, p, s, c, Date(y, m, dom), f);

		lib.AddFilm(curFilm);
	}
	return in;
}

ostream & operator<<(ostream & out, const FilmLibrary & lib)
{
	out << lib.NumberOfFilms() << endl;
	Node<Film>* cur = lib.m_films.head;
	while (cur != nullptr)
	{
		out << cur->data.name << " " << cur->data.producer <<
			" " << cur->data.scenarist << " " << cur->data.composer
			<< " " << cur->data.fee << "Р "
			<< cur->data.releaseDate.dayOfMonth << "." << cur->data.releaseDate.month
			<< "." << cur->data.releaseDate.year << endl;
		cur = cur->p_next;
	}
	return out;
}
