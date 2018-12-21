#include <iostream>
#include <string>
#include <vector>																																										//	#define 1 2

using namespace std;
//КАЕФ
bool prefix_function(string s, int SOBAKA)
{
	vector<size_t> pi(s.size()); // в i-м елементі (його індекс i-1) кількість співпавших символів в початку і в кінцці для підстроки довжиною і
								 // p[0]=0 завжди, p[1]=1, якщо починається з двух однакових 
	for (size_t i = 1; i < s.size(); ++i)
	{
		size_t j = pi[i - 1];
		while ((j > 0) && (s[i] != s[j])) // не рівні
			j = pi[j - 1];				// берем значення які вже підраховані 
		if (s[i] == s[j]) // рівні
			++j;
		pi[i] = j;
	}
	//return pi;
	for (int i = SOBAKA + 1; i < pi.size(); ++i)
		if (SOBAKA == pi[i]) return true;
	return false;
}

int main()
{
	string base, is;
	base.size();
	cin >> base >> is;
	if (base.size() != is.size())
	{
		cout << "NO" << endl;
		system("pause");
		return 0;
	}
	cout << prefix_function(is + "@" + base + base, is.size()) << endl;
	system("pause");
}