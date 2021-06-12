#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define delimiter "\n----------------------------------------------------------------\n"

class ForwardList;
ForwardList operator+(const ForwardList& left, const ForwardList& right);

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
	friend class Iterator;
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element:: count = 0;

class Iterator
{
	Element* Temp;
	// Этот класс просто обравачивает указатель на Element
	//	что позволяет нам перегружаь операции для указателя на Element
public:
	Iterator(Element* Temp = nullptr)
	{
		this->Temp = Temp;
		cout << "IConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "IDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
		//return !(*this==other);
	}
	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Element* getHead()const
	{
		return Head;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
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
	ForwardList(ForwardList&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}

	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	ForwardList& operator=(ForwardList&& other)
	{
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
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
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
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
		/*Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp <<"\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общие количество элементов: " << Element::count << endl;
	}

};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (Element* Temp = right.getHead(); Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}

#define BASE_CHECK
//#define COPY_METHODS_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_ARRAY
//#define RANGE_BASED_LIST

void main()
{
	setlocale(LC_ALL, "russian");
#ifdef COPY_METHODS_CHECK
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
#endif // COPY_METHODS_CHECK

#ifdef OPERATOR_PLUS_CHECK

	ForwardList list1 = { 3, 5, 8, 13, 21 };
	/*list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);*/
	ForwardList list2 = { 34, 55, 89 };
	/*list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);*/

	ForwardList list3 = list1 + list2;
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_ARRAY

	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;

	// range based for (цикл for для контейнера) (налог foreach)
	for (int i : arr)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // RANGE_BASED_ARRAY

#ifdef RANGE_BASED_LIST
	ForwardList list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;

	for (Iterator it = list.begin(); it != list.end(); it++)
	{
		//it != list.end() неявное преобразование nullptr в Iterator и создается в временный безимянный обьект
		cout << *it << "\t";
	}
	cout << endl;
#endif // RANGE_BASED_LIST
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