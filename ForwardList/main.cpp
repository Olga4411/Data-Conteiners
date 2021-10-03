
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

template<typename T>
class Element
{
	static int count;
	T Data;		//�������� ��������
	Element* pNext;	//����� ���������� ��������
public:
	Element(T Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;	//������ ������ - ��������� �� ��������� (�������) ������� ������.
	size_t size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return*this;
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

		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()
	{
		return this->Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		//����������� �� ���������, ������� ������ ������.
		Head = nullptr;
		size = 0;
		//���� ������ ��������� �� 0, �� ������ ����, �.�., �� �������� ���������,
		//� ������ ������ �� �� ��� ���������.
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<T>& il) :
		ForwardList()//���������� ����������� �� ���������, ����� �� ��������� ������ ������ �������
	{
		//begin();	//���������� �������� �� ������ ����������
		//end();	//���������� �������� �� ����� ����������
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			this->push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//����������� ����������� ��������� DeepCopy:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//						Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		//1) ������� ������ �������� �������:
		while (Head)pop_front();
		//2) ��������� ��������� �����������:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		return *this;
	}

	//						Adding elements:
	void push_front(T Data)
	{
		//1) ������� ����� �������:
		Element* New = new Element(Data);
		//2) ����������� ������� � ������:
		New->pNext = Head;
		//3) ������� ��� ����� ������� ������ ��������� ������� ������:
		Head = New;

		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr) return	push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		/*Element* New = new Element(Data);
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Index, T Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index >= size)return push_back(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//						Removing elements:
	void pop_front()
	{
		//1) ���������� ����� ���������� ��������:
		Element* erased = Head;
		//2) ��������� ������� �� ������:
		Head = Head->pNext;
		//3) ������� ������� �� ������:
		delete erased;
		size--;
	}
	void pop_back()
	{
		//1) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) ������� ������� �� ������:
		delete Temp->pNext;
		//3) "��������" �� ��������� ��������
		Temp->pNext = nullptr;
		size--;
	}

	//					Methods:
	void print()const
	{
		Element* Temp = Head; //Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ 
		//� ��������� ��������� ������
		/*while (Temp != nullptr)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext; //������� �� ��������� �������.
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ���������: " << Element::count << endl;
	}
};

#define delimiter "/n---------------------/n"
//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n; cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	int index;
	int value;
	/*cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(index, value);
	list.print();*/
#endif // BASE_CHECK

	ForwardList list = { 3,5,8,13,21 };
	list.print();
	/*ForwardList list2;
	list2 = list;
	list2.print();*/
	cout << delimiter << endl;
	for (ForwardList::Iterator it = list.begin(), end=list.end();it != end; it++)
	{
		cout << *it << "\t";
	}
	cout << endl;
	cout << delimiter << endl;
	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;
}