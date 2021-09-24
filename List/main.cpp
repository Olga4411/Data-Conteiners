#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;


class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data,Element*pNext=nullptr, Element*pPrev=nullptr):Data(Data),pNext(pNext),pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head,*Tail;
	//Element* Head
	//Element* Tail
	
	size_t size;
public:
	size_t get_size()const
	{
		return this->size;
	}
	List()
	{
		//����������� �� ���������-������� ������ ������
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	// Adding elements
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head=Tail= new Element(Data);
			size++;
			return;
		}
		else
		{
			//Element* New = new Element(Data);
			//New->pNext = Head;
			//Head->pPrev = New;
			//Head = New;
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (!Head && !Tail)return push_front(Data);
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr,Tail);
		size++;
	}
	// Remooving elements
	void pop_front()
	{
		//0) ���������, �� �������� �� ��������� ������� ������ ���������
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		//1)��������� ������� �������� �� ������
		Head = Head->pNext;
		//2) ������� �� ������ 
		delete Head->pPrev;
		//3)�������� �� ��������� ��������
		Head->pPrev = nullptr;
		size--;
	}

	void pop_back()
	{
		if (Head = Tail) return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail
	}

	//Methods
	void print()const
	{
		cout << "����� ������" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp-> Data << "\t" << Temp->pNext << endl;
		cout << "���������� ��������� ������" << this->size << endl;
	}
	void reverse_print()const
	{
		cout << "����� ����� ������" << Tail << endl;
		for(Element*Temp=Tail;Temp;Temp=Temp->pPrev)
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "���������� ��������� ������" << this->size << endl;
	}

};
void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ���c��:"; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();


}