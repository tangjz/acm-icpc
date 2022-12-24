#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 101;
int n;
string str[maxn];
int main()
{
	ios::sync_with_stdio(0);
	while(cin >> n)
	{
		for(int i = 0; i < n; ++i)
			cin >> str[i];
		sort(str, str + n);
		for(int i = 0; i < n; ++i)
			cout << str[i] << endl;
	}
	return 0;
}
