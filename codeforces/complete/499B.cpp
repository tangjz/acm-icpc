#include <map>
#include <string>
#include <iostream>
using namespace std;
map<string, string> Hash;
int n, m;
string a, b;
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	while(m--)
	{
		cin >> a >> b;
		if(a.length() > b.length())
			swap(a, b);
		Hash[a] = Hash[b] = a;
	}
	while(n--)
	{
		cin >> a;
		cout << Hash[a] << ' ';
	}
	cout << endl;
	return 0;
}
