#include <iostream>
#include <string>
#include <vector>																																										//	#define 1 2

using namespace std;

bool prefix_function(string s, int SOBAKA)
{
	vector<size_t> pi(s.size()); // кількість символів які співпали для під рядка і
								 //  p[0]=0 завжди, p[1]=1, якщо починається з двух однакових 
	for (size_t i = 1; i < s.size(); ++i)
	{
		size_t j = pi[i - 1];
		while ((j > 0) && (s[i] != s[j])) // не рівнв
			j = pi[j - 1];				// берем раніше пораховані значення(починаючи з максимально можливих)
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
