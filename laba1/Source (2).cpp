

#include <iostream>
#include <vector>

using namespace std;

void createArr(vector<int> &vec, int n)
{
	for (int i = 0; i < n; i++)
	{
		vec.push_back(rand() % 100);
	}
}

void showArr(vector<int> &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

vector <int> merge(vector <int> a, vector <int> b)

{
	vector<int> c(a.size() + b.size());

	int kol1 = 0;
	int kol2 = 0;

	for (int i = 0; i < c.size(); i++)
	{

		if (kol1 == a.size())
		{
			c[i] = b[kol2];
			kol2++;
			continue;
		}

		if (kol2 == b.size())
		{
			c[i] = a[kol1];
			kol1++;
			continue;
		}

		if (a[kol1] <= b[kol2])
		{
			c[i] = a[kol1];
			kol1++;
		}
		else
		{
			c[i] = b[kol2];
			kol2++;
		}
	}
	return c;
}

vector<int> merge_sort(vector <int> vec)
{
	if (vec.size() <= 1)
	{
		return vec;
	}

	vector<int> a, b;
	a.assign(vec.begin(), vec.end() - (vec.size() / 2));
	b.assign(vec.end() - (vec.size() / 2), vec.end());
	return merge(merge_sort(a), merge_sort(b));
}

int main()
{

	vector<int> vec;
	int n;
	cout << "Size: ";
	cin >> n;

	createArr(vec, n);
	showArr(vec);

	vec = merge_sort(vec);

	cout << "Sorted: " << endl;

	showArr(vec);

	return 0;
}