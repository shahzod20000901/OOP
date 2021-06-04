#include<iostream>
using namespace std;
#define delimiter "\n----------------------------------------------------------------\n"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(const int Data, Element* pNext = nullptr)
	{
		count++;
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element:: count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other)
	{
		Head = nullptr;
		size = 0;
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyConstructor:\t" << this << endl;
	}

	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
//					operators:
	ForwardList& operator=(const ForwardList& other)
	{
		while (Head)pop_front();
		if (this == &other)return *this;
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

//				Methdos:
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		Element* Temp = Head;
		while(Temp->pNext!=nullptr)
		Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void Insert(int Index, int Data)
	{
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void pop_front()
	{
		Element* to_del = Head;
		Head = Head->pNext;
		delete to_del;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext!=nullptr)
			Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == 0) { pop_front();return; }
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* to_del = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete to_del;
		size--;
	}

	void print()
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общие количество элементов: " << Element::count << endl;
	}

};

void main()
{
	setlocale(LC_ALL, "russian");
	ForwardList list;
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	cout << delimiter;
	list.print();
	cout << delimiter;
	list.push_back(55555);
	list.print();
	cout << delimiter;
	int Index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значения добавляемого элемента: "; cin >> value;
	list.Insert(Index, value);
	list.print();
	cout << delimiter;
	list.pop_front();
	list.print();
	cout << delimiter;
	list.pop_back();
	list.print();
	cout << delimiter;
	int del_index;
	cout << "Введите индекс удаляемого элемента: "; cin >> del_index;
	list.erase(del_index);
	list.print();

	ForwardList list1 = list;
	list1.print();

	ForwardList list2;
	list2 = list;
	list2.print();

}

/*
TODO:
В класс ForwardList добавить методы:
1. void erase(int index);		//Удаляет значение по заданному индексу
2. Написать деструктор таким образом, чтобы он очищал список (удалял из него све элементы) перед удалением;
3. Оптимировать методы удаления элементов;
4. CopyMethods
5. MoveMethods
6. Обеспечить создание списка следующим образом:
	ForwardList list = { 3, 5, 8, 13, 21 };
*/

/*
класс ForwardList добавить методы:
1. void erase(int index);		//Удаляет значение по заданному индексу
2. Написать деструктор таким образом, чтобы он очищал список 
	(удалял из него све элементы) перед удалением;				DONE
3. Оптимировать методы добавления элементов и проходы по списку;
4. CopyMethods		DONE
5. MoveMethods
6. Перегрузить оператор + таким образом, чтобы он выполнял конкатенацию списков;
7. (Hardcore-чик)Обеспечить создание списка следующим образом:
	ForwardList list = { 3, 5, 8, 13, 21 };
8. (Hardcore)Обеспечить вывод списка на экран следующим образом:
	for(int i:list)
		cout << i << tab;
	cout << endl;
*/