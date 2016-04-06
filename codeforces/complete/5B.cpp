#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int n, maxs;
string s[1024];
int main()
{
	ios::sync_with_stdio(false);
	while(getline(cin, s[n]))
	{
		maxs = max(maxs, (int)s[n].length());
		++n;
	}
	for(int i = -2; i < maxs; ++i)
		cout << "*";
	cout << endl;
	for(int i = 0, j, k, l = 0; i < n; ++i)
	{
		cout << "*";
		k = maxs - s[i].length();
		j = k >> 1;
		k -= j;
		if(j ^ k)
		{
			if(l & 1)
				swap(j, k);
			l ^= 1;
		}
		while(j--)
			cout << " ";
		cout << s[i];
		while(k--)
			cout << " ";
		cout << "*" << endl;
	}
	for(int i = -2; i < maxs; ++i)
		cout << "*";
	cout << endl;
	return 0;
}
