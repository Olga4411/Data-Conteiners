#include<iostream>
using namespace std;
void elevator(int level)
{
	if (level == 0)return;
	cout << level << endl;
	elevator(level - 1);//рекурсивный вызов
}

void main()
{
	setlocale(LC_ALL, "Russian");
	//cout << "Hello World";
	//main();// рекурсивный вызов функции main()
	int n;
	cout << "¬велите номер этажа"; cin >> n;
	elevator(n);
}