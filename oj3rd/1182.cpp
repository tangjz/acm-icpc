#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 21;
int n;
string s[maxn];
int main()
{
	ios::sync_with_stdio(0);
	while(cin >> n)
	{
		for(int i = 0; i < n; ++i)
			cin >> s[i];
		sort(s, s + n);
		for(int i = 0; i < n; ++i)
			cout << s[i] << endl;
		cout << endl;
	}
	return 0;
}
