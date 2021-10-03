#include<iostream>
using namespace std;

void elevator(int floor);
int factorial(int n);
double power(int a, int n);// основание степени, показатель степени 


//#define ELEVATOR
//#define FACTORIAL
#define POWER



void elevator(int level)
{
	if (level == 0)	
	{
		cout << level;
		cout << " " << endl;
		return;
	}
	cout << level << endl;
	elevator(level - 1);
	cout << level << endl;
}

int factorial(int n)
{
	/*if (n == 0)return 1;
	return n * factorial(n - 1);*/
	
	return n == 0 ? 1 : n * factorial(n - 1);
}

double power(int a, int n)
{
	/*if (n == 0)return 1;//1-это константа
	if (n < 0)
	{
		return 1./a * power(a, n + 1);
	}
	return a * power(a, n - 1);*/

	return n == 0 ? 1 : n > 0 ? a * power(a, n - 1) : 1. / a * power(a, n + 1);
}



void main()
{
	setlocale(LC_ALL, "Russian");
	/*cout << "Hello World";
	main();*/

#ifdef ELEVATOR
	int level;
	cout << "¬ы в подвале: "; cin >> level;
	elevator(level);
#endif // ELEVATOR

#ifdef FACTORIAL
	int n;
	cout << "¬ведите число дл€ вычислени€ факториала: "; cin >> n;
	cout << factorial(n) << endl;
#endif // FACTORIAL

#ifdef POWER
	int a;
	int n;
	cout << "¬ведите основание и показатель степени: "; cin >> a >> n;
	cout << power(a, n) << endl;
#endif // POWER

	
}