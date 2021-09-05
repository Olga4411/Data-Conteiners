#include<iostream>
using namespace std;

class Element
{

	int Data;//�������� ��������
	Element* pNext;//����� ���������� ��������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;// ������ ������-��������� �� ��������� ������� ������(�� �������)
public:
	ForwardList()
	{
		Head = nullptr;// ����������� �� ���������, ������� ������ ������.
		// ���� ������ ��������� �� 0, �� ������ ����, �.�. �� �������� ���������,
		//� ������ ������ �� �� ��� ���������.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	// Adding elements
	void push_front(int Data)
	{
		//1) ������� ����� �������
		Element* New = new Element(Data);
		//2)����������� ������� � ������
		New->pNext = Head;
		//3)�������, ��� ����� ������� ������ ��������� ������� ������
		Head = New;
	}
	//Methods
	void print()const
	{
		Element* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext; 
		}
	}
	
};

void main()
{
	setlocale(LC_ALL, "Russian");
	int n; cout << "������� ������ ������:"; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

}