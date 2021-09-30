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
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List;
	}*Head,*Tail;
	//Element* Head
	//Element* Tail
	
	size_t size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

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

		const int& operator*()const
		{
			return this->Temp->Data;
		}

		int& operator*()
		{
			return this->Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	size_t get_size()const
	{
		return this->size;
	}
	List()
	{
		//Конструктор по умолчанию-создает пустой список
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		for (Element* Temp = other.Head; Temp; Temp->pNext)push_back(Temp->Data);
			cout << "LCopyConstructor:" << this << endl;
	}

	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//Operators
	List& operator=(const List& other)
	{
		if (this == &other)return*this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp->pNext) push_back(Temp->Data);
			cout << "LCopyConstructor:" << this << endl;
		return*this;
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
		//0) Проверяем, не является ли удаляемый элемент списка последним
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		//1)исключаем элемент частично из списка
		Head = Head->pNext;
		//2) удаляем из памяти 
		delete Head->pPrev;
		//3)забываем об удаленном элементе
		Head->pPrev = nullptr;
		size--;
	}

	void pop_back()
	{
		if (Head = Tail) return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail -> pNext = nullptr;
		size--;
	}

	//Methods
	void print()const
	{
		cout << "Адрес начала списка" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp-> Data << "\t" << Temp->pNext << endl;
		cout << "Количество элементов списка" << this->size << endl;
	}
	void reverse_print()const
	{
		cout << "Адрес конца списка" << Tail << endl;
		for(Element*Temp=Tail;Temp;Temp=Temp->pPrev)
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Количество элементов списка" << this->size << endl;
	}

};

//#define BASE_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef  BASE_CHECK
	int n;
	cout << "Введите размер спиcка:"; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
#endif //  BASE_CHECK

	List list = { 3,5,8,13,21 };
	list = list;
	list.print();
	//List list2=list;
	List list2;
	list2 = list;
	//list2/print();
	for (List::Iterator it = list2.begin(); it != list2.end(); it++)
	{
		cout << *it << "\t";
	}
	cout << endl;
	list2.reverse_print();


}