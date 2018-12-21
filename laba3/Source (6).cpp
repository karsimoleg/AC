#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <conio.h>

using namespace std;

const int NMAX = 100;
const int inf = 0;

struct Pyramid
{
	int d;
	int n;
	int s[NMAX + 1];
	Pyramid(int n, int d) {
		this->d = d;
		this->n = n;
	}
};

void Print_Help(const Pyramid& p, int x, int level) {

	if (x > p.n) return;
	for (int t = 0; t < level; t++)
		cout << "    ";

	cout << "[" << x << "] " << p.s[x] << endl;

	for (int i = 0; i < p.d; i++)
		Print_Help(p, (x - 1)*p.d + 2 + i, level + 1);
}

void Print(const Pyramid& p) {

	for (int i = 1; i <= p.n; i++)
		cout << p.s[i] << " ";
	cout << endl;

	Print_Help(p, 1, 0);
	cout << endl;
}

void Put_Element(Pyramid& p) {

	for (int i = 0; i <= p.n; i++)
		p.s[i] = rand() % 50;
	sort(p.s, p.s + p.n);
}

void Max_Heapify(Pyramid& p, int x) {

	int xmax = x, d = p.d;
	for (int i = 0; i < d && (x - 1)*d + 2 + i <= p.n; i++)
		if (p.s[(x - 1)*d + 2 + i] > p.s[xmax]) xmax = (x - 1)*d + 2 + i;

	if (xmax == x) return;
	swap(p.s[xmax], p.s[x]);
	Max_Heapify(p, xmax);
}

void Build_Max_Heap(Pyramid& p) {

	for (int i = p.n; i >= 1; i--)
		Max_Heapify(p, i);
}

int Extract_Max(Pyramid& p) {

	int max = p.s[1];
	p.s[1] = p.s[p.n];
	p.n--;

	Max_Heapify(p, 1);
	return max;
}

void Increase_Key(Pyramid& p, int x, int key) {

	if (p.s[x] > key) return;

	int d = p.d;
	p.s[x] = key;

	while (x > 1 && p.s[(x - 2) / d + 1] < p.s[x]) {
		swap(p.s[x], p.s[(x - 2) / d + 1]);
		x = (x - 2) / d + 1;
	}
}

void Insert_Key(Pyramid& p, int key)
{

	p.s[++p.n] = 0;
	Increase_Key(p, p.n, key);
}

int main()
{
	srand(time(NULL));
	Pyramid p = Pyramid(8, 2);
	Put_Element(p);
	Print(p);

	Insert_Key(p, 67);
	Print(p);

	cout << " ExtractMax = " << Extract_Max << endl;
	_getch();
}