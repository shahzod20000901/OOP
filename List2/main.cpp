/*� ���������� ������ �������� ������:
1. void push_back(int Data); DONE
2. void pop_front(); DONE
3. void pop_back(); DONE
4. void insert(int index, int data); DONE
5. void erase(int index); DONE
6. ���������� ������ ������� ������; DONE
7. ���� ����������� ��� ������ ����������:
	List list = {3,5,8,13,21}; DONE
	for(int i:list)
		cout << i << tab;
	cout << endl;*/

#include<iostream>
using namespace std;

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			this->pPrev = pPrev;
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List<T>;
	} *Head, * Tail;//����� �� ����� �������� ������ ��������� ��� ��������� �� ������� ����� ������.
	unsigned int size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr)
		{
			this->Temp = Temp;
			cout << "ITConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ITDestructor:\t" << this << endl;
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
		}
		const T& operator*() const
		{
			return Temp->Data;
		}
		T& operator*()
		{
			return Temp->Data;
		}
	};
	//  Adding elements
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const initializer_list<T>& il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(T Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		New->pPrev = nullptr;
		if (Head) Head->pPrev = New;
		Head = New;
		if (!Tail) Tail = Head;
		size++;
	}
	void push_back(T Data)
	{
		Element* New = new Element(Data);
		New->pPrev = Tail;
		New->pNext = nullptr;
		if (Tail) Tail->pNext = New;
		Tail = New;
		if (!Head) Head = Tail;
		size++;
	}
	void insert(unsigned int index, T data)
	{
		if (index == 0)
		{
			push_front(data);
			return;
		}
		if (index == size)
		{
			push_back(data);
			return;
		}
		if (index > size)return;
		if (index <= size / 2)
		{
			Element* New = new Element(data);
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)
			{
				Temp = Temp->pNext;
			}
			New->pNext = Temp->pNext;
			New->pPrev = Temp;
			Temp->pNext->pPrev = New;
			Temp->pNext = New;
			size++;
		}
		else
		{
			Element* New = new Element(data);
			Element* Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)
			{
				Temp = Temp->pPrev;
			}
			New->pPrev = Temp->pPrev;
			New->pNext = Temp;
			Temp->pPrev->pNext = New;
			Temp->pPrev = New;
			size++;
		}

	}
	void pop_front()
	{
		Element* to_del = Head;
		Head = Head->pNext;
		if (Head) Head->pPrev = nullptr;
		else Tail = nullptr;
		delete to_del;
		size--;
	}
	void pop_back()
	{
		Element* to_del = Tail;
		Tail = Tail->pPrev;
		if (Tail) Tail->pNext = nullptr;
		else Head = nullptr;
		delete to_del;
		size--;
	}
	void erase(int index)
	{
		if (index == 0)
		{
			pop_front();
			return;
		}
		if (index == size - 1)
		{
			pop_back();
			return;
		}
		if (index >= size)return;
		Element* Temp;
		if (index <= size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
				Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)
				Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;

	}
	void Print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << "\t" << Temp->pPrev << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "------------------------------" << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef BASE_CHECK
	int n, p;
	cout << "������� ������ ������: "; cin >> n;
	List<int> list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.Print();
	list.push_back(123);
	list.Print();
	list.pop_front();
	list.Print();
	list.pop_back();
	list.Print();
	cout << "������� ������ ������������ ��������: "; cin >> n;
	cout << "������� �������� ������������ ��������: "; cin >> p;
	list.insert(n, p);
	list.Print();
	cout << "������� ������ ���������� ��������: "; cin >> n;
	list.erase(n);
	list.Print();
	List<int> list2 = { 2,14,45,67,100 };
	list2.Print();
	for (int i : list2)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // BASE_CHECK

	List<double> d_list = { 2.3, 3.4, 4.5, 5.6 };
	//d_list.Print();
	for (List<double>::Iterator It = d_list.begin(); It != d_list.end(); It++)
	{
		cout << *It << "\t";
	}
	for (double i : d_list)cout << i << "\t"; cout << endl;

	List<string> s_list = { "������", "�����", "��", "�����", "�����-���" };
	for(List<string>::Iterator it=s_list.begin(); it!=s_list.end(); it++)
	{
		cout << *it << "\t";
	}
	s_list.Print();
	for (string i : s_list)cout << i << "\t"; cout << endl;
}