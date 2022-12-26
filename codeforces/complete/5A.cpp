#include <string>
#include <iostream>
using namespace std;
int cnt, ans;
string str;
int main()
{
	ios::sync_with_stdio(0);
	while(getline(cin, str))
		if(str[0] == '+') ++cnt;
		else if(str[0] == '-') --cnt;
		else ans += (str.substr(str.find(':')).size() - 1) * cnt;
	cout << ans << endl;
	return 0;
}
