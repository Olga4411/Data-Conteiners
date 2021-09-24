
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Element
{
	static int count;
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
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
	Element* Head;	//Голова списка - указывает на начальный (нулевой) элемент списка.
	size_t size;
public:
	ForwardList()
	{
		//Конструктор по умолчанию, создает пустой список.
		Head = nullptr;
		size = 0;
		//Если Голова указывает на 0, то список пуст, т.е., не содержит элементов,
		//и Голове больше не на что указывать.
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :
		ForwardList()//Делегируем конструктор по умолчанию, чтобы НЕ создавать пустой список вручную
	{
		//begin();	//Возвращает Итератор на начало контейнера
		//end();	//Возвращает Итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			this->push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//Конструктор копирования выполняет DeepCopy:
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
		//1) Удаляем старое значение объекта:
		while (Head)pop_front();
		//2) Выполняем побитовое копирование:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		return *this;
	}

	//						Adding elements:
	void push_front(int Data)
	{
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Прикрепляем элемент к списку:
		New->pNext = Head;
		//3) Говорим что Новый элемент теперь Начальный элемент списка:
		Head = New;

		size++;
	}
	void push_back(int Data)
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
	void insert(int Index, int Data)
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
		//1) Запоминаем адрес удаляемого элемента:
		Element* erased = Head;
		//2) Исключаем элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из памяти:
		delete erased;
		size--;
	}
	void pop_back()
	{
		//1) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) Удаляем элемент из памяти:
		delete Temp->pNext;
		//3) "Забываем" об удаленном элементе
		Temp->pNext = nullptr;
		size--;
	}

	//					Methods:
	void print()const
	{
		Element* Temp = Head; //Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ 
		//к элементам структуры данных
		/*while (Temp != nullptr)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext; //Переход на следующий элемент.
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n; cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	int index;
	int value;
	/*cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();*/
#endif // BASE_CHECK

	ForwardList list = { 3,5,8,13,21 };
	list.print();
	ForwardList list2;
	list2 = list;
	list2.print();

}