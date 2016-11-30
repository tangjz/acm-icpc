#include <string>
#include <iostream>
#include <algorithm>
using namespace std; 
const int maxn = 101;
int n;
string str[maxn];
bool cmp(const string &x, const string &y)
{
	return x + y < y + x; 
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> str[i];
	sort(str, str + n, cmp);
	for(int i = 0; i < n; ++i)
		cout << str[i];
	cout << endl;
	return 0;
} 

