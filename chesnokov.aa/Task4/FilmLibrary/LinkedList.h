#pragma once
enum ListExcept 
{
	OutOfRange
};
// узел списка
template <class T> class Node
{
public:
	T data;          // хранит данные

	Node<T>* p_next; // и указатель на следующий узел
	Node() : data(T()), p_next(nullptr) {};
};

// мини версия cвязного списка
// не совершает управление памятью, пользователь сам должен следить
// за динамически созданной памятью
template <class T> class LinkedList
{
public:
	Node<T>* head;   // первый элемент в списке
private:
	int count;       // кол-во элементов в списке
public:
	// добавления элментов
	void AddToEnd(const T& elem);
	void AddToStart(const T& elem);
	void AddAt(const T& elem, int index);
	// удаления элементов
	void DeleteAtEnd();
	void DeletAtStart();
	void DeleteAt(int index);
	// получение данных
	T GetAt(int index) { return operator[](index)->data; }
	int Count() const { return count; }
	Node<T>* operator[](int index);
public:
	LinkedList();
	~LinkedList();
};

template<class T>
void LinkedList<T>::AddToEnd(const T& elem)
{
	Node<T>* cur;
	if (head != nullptr)  // если список не пустой
	{
		cur = head;
		while (cur->p_next != nullptr)   // нашли конец списка 
										 //(т.е. за последним элементом не следует следующий)
		{
			cur = cur->p_next;
		}
		// указываем последнему узлу следующий новый узел
		cur->p_next = new Node<T>();
		cur->p_next->data = elem;

	}
	else
	{
		// создаем первый элемент в списке
		cur = new Node<T>;
		cur->data = elem;
		head = cur;
	}
	count++;
}

template<class T>
void LinkedList<T>::AddToStart(const T & elem)
{
	// cоздаем новый узел
	Node<T>* newnode = new Node<T>;
	newnode->data = elem;
	newnode->p_next = head;
	// заменяем голову на новую
	head = newnode;
	count++;
}

template<class T>
void LinkedList<T>::AddAt(const T & elem, int index)
{
	if (index > count || index < 0)  // элементов меньше чем указнный индекс
	{
		ListExcept e = OutOfRange;
		throw e;
	}
	if (index == 0)
	{
		AddToStart(elem);
		return;
	}
	if (index == count)
	{
		AddToEnd(elem);
		return;
	}
	// разъединяем два соседних элемента, вклинив между ними новый
	Node<T>* newnode = new Node<T>;
	newnode->data = elem;
	newnode->p_next = operator[](index);
	operator[](index - 1)->p_next = newnode;
	count++;
	return;
}

template<class T>
void LinkedList<T>::DeleteAtEnd()
{
	if (count == 0) return;  // список и так пуст
	if (count == 1)
	{
		delete head;
		head = nullptr;
		count--;
		return;
	}
	delete operator[](count - 1);
	// указываем что за предпослденим элементом больше ничто не следует
	operator[](count - 2)->p_next = nullptr;
	count--;
}

template<class T>
void LinkedList<T>::DeletAtStart()
{
	if (count == 0) return;  // cписок и так пуст
	if (count == 1)
	{
		delete head;
		head = nullptr;
		count--;
		return;
	}
	// головным элементом делаем второй элемент
	Node<T>* temp = operator[](1);
	delete head;
	head = temp;
	count--;
}

template<class T>
void LinkedList<T>::DeleteAt(int index)
{
	if (index >= count || index < 0)
	{
		ListExcept e = OutOfRange;
		throw e;
	}
	if (index == count - 1)
	{
		DeleteAtEnd();
		return;
	}
	if (index == 0)
	{
		DeletAtStart();
		return;
	}
	Node<T>* follow = operator[](index + 1); // элемент следующий за удаляемым
	delete operator[](index);
	operator[](index - 1)->p_next = follow;  // заполняем разрыв
	count--;
	return;
}

template<class T>
Node<T> * LinkedList<T>::operator[](int index)
{
	if (index >= count)
	{
		ListExcept e = OutOfRange;
		throw e;
	}
	Node<T>* cur = head;
	// проходим до нужного по списку
	for (int i = 0; i < index; i++)
	{
		cur = cur->p_next;
	}
	return cur;
}

template<class T> LinkedList<T>::LinkedList()
{
	count = 0;
	head = nullptr;
}


template<class T> LinkedList<T>::~LinkedList()
{
	if (count == 0) return;
	if (count == 1)
	{
		delete head;
		return;
	}
	Node<T>* temp1, *temp2;
	temp1 = head;
	temp2 = temp1->p_next;
	for (int i = 1; i < count; i++)  // удаляем узлы поочереди начиная с головы
	{
		delete temp1;
		temp1 = temp2;
		temp2 = temp2->p_next;
	}
	delete temp2;
	count = 0;
}
