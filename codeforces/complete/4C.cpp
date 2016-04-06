#include <map>
#include <string>
#include <iostream>
using namespace std;
map<string, int> Hash;
int n;
string str;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	while(n--)
	{
		cin >> str;
		if(!Hash[str])
		{
			cout << "OK" << endl;
			++Hash[str];
		}
		else cout << str << Hash[str]++ << endl;
	}
	return 0;
}
