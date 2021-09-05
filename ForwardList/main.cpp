#include<iostream>
using namespace std;

class Element
{

	int Data;//Значение элемента
	Element* pNext;//Адрес следующего элемента
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
	Element* Head;// голова списка-указывает на начальный элемент списка(на нулевой)
public:
	ForwardList()
	{
		Head = nullptr;// конструктор по умолчанию, создает пустой список.
		// Если Голова указывает на 0, то список пуст, т.е. не содержит элементов,
		//и голове больше ни на что указывать.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	// Adding elements
	void push_front(int Data)
	{
		//1) Создаем новый элемент
		Element* New = new Element(Data);
		//2)прикрепляем элемент к списку
		New->pNext = Head;
		//3)говорим, что новый элемент теперь начальный элемент списка
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
	int n; cout << "Введите размер списка:"; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

}