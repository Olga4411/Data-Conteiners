#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
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
	}*Head, * Tail;
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
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "RIConstructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "RIDestructor:\t" << this << endl;
		}

		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
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
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	//HW
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
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
	List(const initializer_list<T>& il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List<T>& other) :List()
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
	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)return*this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp->pNext) push_back(Temp->Data);
		cout << "LCopyConstructor:" << this << endl;
		return*this;
	}

	// Adding elements
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
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
	void push_back(T Data)
	{
		if (!Head && !Tail)return push_front(Data);
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
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
		Tail->pNext = nullptr;
		size--;
	}

	void erase(size_t index)	// Удаляет значение по индексу.//HW
	{
		if (index == 0)return pop_front();
		if (index == size - 1)return pop_back();	// Удаление последнего элемента
		if (index >= size)return;
		Element* Temp;
		if (index < size / 2)	// Иду сначала списка.
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		// Для удаления элемента из списка сначала нужно исключить элемент из списка.
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
	}

	//Methods

	
	void insert(size_t index, int Data)//HW
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);

		//1) Доходим до позиции, на которую нужно вставить элемент:
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}

		//2) Создаем элемент, и включаем его в список:
		Element* New = new Element(Data);
		New->pPrev = Temp->pPrev;
		New->pNext = Temp;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}
	void print()const
	{
		cout << "Адрес начала списка" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Количество элементов списка" << this->size << endl;
	}
	void reverse_print()const
	{
		cout << "Адрес конца списка" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Количество элементов списка" << this->size << endl;
	}

};
//#define RANGE_BASED
//#define BASE_CHECK
#define ITERATORS_CHECK
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

	size_t index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);

	list.print();
	list.reverse_print();
	//HOMEWORK
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif //  BASE_CHECK

#ifdef ITERATORS_CHECK
	List<int> list = { 3,5,8,13,21 };
	//list = list;
	//list.print();
	////List list2=list;
	//List list2;
	//list2 = list;
	//list2/print();
	
	
	for (int i : list)	cout << i << tab;	cout << endl;
	for (List<int>::Iterator it = list.begin(); it != list.end(); it++)
		cout << *it << tab;
	cout << endl;
	//for (List::Iterator it = list.end(); it != list.begin(); it--)cout << *it << tab;	cout << endl;

	for (List<int>::ReverseIterator rit = list.rbegin(); rit != list.rend(); rit++)
		cout << *rit << tab;
	cout << endl;


	
#endif // ITERATORS_CHECK

#ifdef RANGE_BASED
	double arr[] = { 3.5,5.8,8.8,13.2,21.9 };
	cout << sizeof(arr) << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++)// оператор [] возвращает значение по индексу
	{
		//cout << arr[i] << *(arr+i)<<"\t";
		cout << *(arr + i) << "\t";
	}
	cout << endl;
	for (int i : arr)//Range-based for intended to work only with containers
	{
		cout << i << "\t";
	}
	cout << endl;
	/*for (type i : conteiner)
	{
		//i-iterator;
	}*/

	List<int> list = { 0,1,1,2,3,5,8,13,21 };
	for (double i : list)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // RANGE_BASED



}