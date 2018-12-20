#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 1000;
const long long step = 31;

string all_values[NMAX];
string look_for[NMAX];
long long pow_hash[NMAX][NMAX],hash_table[NMAX][NMAX];

// рахує степені кожної комірки
void create_pow_hash(int n)
{
    for (int i = 0;i < n; ++i)
    {
        if (i == 0)
            pow_hash[i][0] = 1;
        else
            pow_hash[i][0] = pow_hash[i-1][n-1]*step;
        for (int j = 1;j < n; ++j)
            pow_hash[i][j] = pow_hash[i][j-1]*step;
    }
}

// хешування
void create_hash_table_for_all(int n)
{
    hash_table[0][0] = all_values[0][0]-'a'+1;
    for (int j = 1;j < n; ++j)
        hash_table[0][j] = (all_values[0][j]-'a'+1)*pow_hash[0][j] + hash_table[0][j-1];
    for (int i = 1;i < n; ++i)
    {
        hash_table[i][0] = (all_values[i][0]-'a'+1)*pow_hash[i][0] + hash_table[i-1][0];
        for (int j = 1;j < n; ++j)
            hash_table[i][j] = (all_values[i][j]-'a'+1)*pow_hash[i][j] + hash_table[i-1][j] + hash_table[i][j-1] - hash_table[i-1][j-1];
    }
}

// перевірка на входження
vector<pair<int,int> > check(int n,int m,int count_hash)
{
    vector<pair<int,int> > ans;
    ans.clear();
    for (int i = 0;i <= n-m; ++i)
    {
        for (int j = 0;j <= n-m; ++j)
        {
            long long cur_all = hash_table[i+m-1][j+m-1];
            if (i && j)
                cur_all += hash_table[i-1][j-1];
            if (i)
                cur_all -= hash_table[i-1][j+m-1];
            if (j)
                cur_all -= hash_table[i+m-1][j-1];
            long long cur_look_for = count_hash * pow_hash[i][j];
            if (cur_all == cur_look_for)
                ans.push_back({i,j});
        }
    }
    return ans;
}

// тести
int main()
{
    int n,m;
    cout << "Input the size of matrix in which we would search another:\n";
    cin >> n;
    cout << "Input the matrix(all elements input without spaces, new row starts from enter, all elements are small letters):\n";
    getline(cin,all_values[0]);
    for (int i = 0;i < n; ++i)
        getline(cin,all_values[i]);
    cout << "Input the size of matrix which we would like to find:\n";
    cin >> m;
    cout << "Input the matrix(all elements input without spaces, new row starts from enter, all elements are small letters):\n";
    getline(cin,look_for[0]);
    for (int i = 0;i < m; ++i)
        getline(cin,look_for[i]);

    if (n < m)
        cout << "m is more than n\n";
    else
    {
        create_pow_hash(n);
        create_hash_table_for_all(n);

        long long count_hash = 0;
        for (int i = 0;i < m; ++i)
        {
            for (int j = 0;j < m; ++j)
                count_hash += (look_for[i][j]-'a'+1)*pow_hash[i][j];
        }
        vector<pair<int,int> > res = check(n,m,count_hash);
        if ((int)res.size())
        {
            cout << "YES\n";
            cout << res.size() << '\n';
            for (int i = 0;i < (int) res.size(); ++i)
                cout << res[i].first + 1 << ' ' << res[i].second + 1 << '\n';
        }
        else
            cout << "NO\n";
    }
}
