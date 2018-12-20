#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int NMAX_HORPSPOOL = 256;
const int POW_RABIN_CARP = 257;


int naive_algorithm(string need,string haystack)
{
	int ans = -1;
	for (int i = 0; i <= (int)haystack.length() - (int)need.length(); ++i)
	{
		bool ok = true;
		for (int j = 0; j < (int)need.length(); ++j)
		{
			if (need[j] != haystack[j + i]) {
				ok = false;
				break;
			}
		}
		if (ok) {
			ans = i;
			break;
		}
	}
	return ans;
}


int Horspool(string need, string haystack)
{
	int mas_for_need[NMAX_HORPSPOOL];
	for (int i = 0; i < NMAX_HORPSPOOL; ++i)
		mas_for_need[i] = (int)need.length();
	for (int i = 0; i < (int)need.length()-1; ++i)
		mas_for_need[need[i]] = (int)need.length() - i - 1;

	int step = 0;
	int ans = -1;
	while ((int)haystack.length() - step >= (int)need.length())
	{
		int i = (int)need.length() - 1;
		while (haystack[step + i] == need[i])
		{
			if (i == 0) {
				ans = step;
				break;
			}
			--i;
		}
		if (ans >= 0)
			break;
		step += mas_for_need[haystack[step + (int)need.length() - 1]];
	}	
	return ans;
}


int Boyer_Moore(string need, string haystack)
{
	int n = (int)need.length();
	vector<int> suffshift(n + 1, n), z(n, 0);
	for (int i = 1, l = 0, r = 0; i < n; ++i)
	{
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && need[n - 1 - z[i]] == need[n - 1 - (i + z[i])])
			++z[i];
		if (i + z[i] - 1 > r)
		{
			l = i;
			r = i + z[i] - 1;
		}
	}
	for (int i = n - 1; i > 0; --i)
		suffshift[n - z[i]] = i;
	for (int i = 1, r = 0; i < n; ++i)
	{
		if (i + z[i] == n)
		{
			for (; r <= i; ++r)
				if (suffshift[r] == n)
					suffshift[r] = i;
		}
	}

	int ans = -1;
	for (int i = 0, j = 0; i <= (int)haystack.length()-n && j >= 0; i += suffshift[j + 1]) {
		for (j = n - 1; j >= 0 && need[j] == haystack[i + j]; j--);
		if (j < 0)
			ans = i;
		if (ans >= 0)
			break;
	}

	return ans;
}


int prefics_function(string need, string haystack)
{
	string concat = need + "#" + haystack;
	int n = (int)concat.length();
	vector<int> pi(n);
	for (int i = (int)need.length()+1; i < n; ++i)
	{
		int j = pi[i - 1];
		while (j > 0 && concat[i] != concat[j])
			j = pi[j - 1];
		if (concat[i] == concat[j])
			++j;
		pi[i] = j;
	}
	int ans = -1;
	for (int i = 2*(int)need.length(); i < n; ++i)
	{
		if (pi[i] >= (int)need.length())
		{
			ans = i-pi[i];
			break;
		}
	}
	if (ans == -1)
		return ans;
	ans -= (int)need.length();
	return ans;
}


int Rabin_Karp(string need, string haystack)
{
	vector<long long> pow_hash(max(need.length(), haystack.length()));
	pow_hash[0] = 1;
	for (int i = 1; i < (int)pow_hash.size(); ++i)
		pow_hash[i] = pow_hash[i - 1] * POW_RABIN_CARP;

	vector<long long> hash_table(haystack.length());
	for (int i = 0; i < (int)hash_table.size(); ++i) {
		hash_table[i] = (haystack[i] + 1)*pow_hash[i];
		if (i)
			hash_table[i] += hash_table[i - 1];
	}

	long long count_need_hash = 0;
	for (int i = 0; i < (int)need.length(); ++i)
		count_need_hash += pow_hash[i] * (need[i] + 1);
	int ans = -1;
	for (int i = 0; i <= (int)haystack.length() - (int)need.length(); ++i)
	{
		long long cur_hash = hash_table[i + (int)need.length() - 1];
		if (i)
			cur_hash -= hash_table[i - 1];
		if (cur_hash == count_need_hash * pow_hash[i])
		{
			ans = i;
			break;
		}
	}
	return ans;
}


int main()
{
	string need, haystack;
	cout << "Input string that you want to find\n";
	getline(cin, need);
	cout << "Input string where you want to search\n";
	getline(cin, haystack);
	int ans = -1;
	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ans = naive_algorithm(need,haystack);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Time of Naive algorithm work: " << duration / 1000.0 << "ms\n\n";

	
	t1 = high_resolution_clock::now();
	ans = Horspool(need, haystack);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Time of Horspool algorithm work: " << duration / 1000.0 << "ms\n\n";

	
	t1 = high_resolution_clock::now();
	ans = Boyer_Moore(need, haystack);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Time of Boyer-Moore algorithm work: " << duration / 1000.0 << "ms\n\n";

	
	t1 = high_resolution_clock::now();
	ans = prefics_function(need, haystack);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Time of Knuth-Morris-Pratt algorithm work: " << duration / 1000.0 << "ms\n\n";

	
	t1 = high_resolution_clock::now();
	ans = Rabin_Karp(need, haystack);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Time of Rabin-Karp algorithm work: " << duration / 1000.0 << "ms\n\n";

	if (ans >= 0)
		cout << "The first occurrence starts from " << ans + 1 << " position.\n";
	else
		cout << "There is no occurences.\n";

	system("pause");
	return 0;
}