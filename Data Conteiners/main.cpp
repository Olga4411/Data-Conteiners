#include<iostream>
using namespace std;

void main()
{
	const int n = 5;
	int arr[n] = { 3,5,8,13,21 };
	cout << arr << endl;
	for (int i = 0; i < n; i++)
	{
		cout << *(arr + i) << "\t";
	}
	cout << endl;
}