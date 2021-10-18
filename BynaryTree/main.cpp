#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

class Tree
{
	protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			/*this->Data = Data;
			this->pLeft = pLeft;
			this->pRight = pRight;*/

#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
#ifdef DEBUG
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
#endif // DEBUG

		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		this->Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)	Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight)insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);
		}
	}

	int minValue(Element* Root)
	{
		if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		//return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int count(Element* Root)
	{
		/*if (Root ==nullptr)return 0;
		return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
public:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)	Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		if(Data>Root->Data)
		{
			if (Root->pRight)insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "���������� ��������� ������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;
	cout << "����������� �������� � ������:" << tree.minValue(tree.getRoot())<< endl;
	cout << "������������ �������� � ������:" << tree.maxValue(tree.getRoot()) << endl;
	cout << "���������� ��������� ������:" << tree.count(tree.getRoot()) << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100, u_tree.getRoot());
	}
	u_tree.print(u_tree.getRoot());
	cout << endl;
	cout << "���������� ��������� ������:" << u_tree.count(u_tree.getRoot()) << endl;

}
