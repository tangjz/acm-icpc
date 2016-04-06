#include <string>
#include <iostream>
using namespace std;
string s, t;
int main()
{
	ios::sync_with_stdio(0);
	while(cin >> s >> t)
		if(s.find(t) != string::npos)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	return 0;
}
