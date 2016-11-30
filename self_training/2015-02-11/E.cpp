#include <set>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
set<string> Hash;
string tmp;
int main()
{
	ios::sync_with_stdio(0);
	while(getline(cin, tmp) && tmp != "#")
	{
		Hash.clear();
		istringstream fin(tmp);
		while(fin >> tmp)
			Hash.insert(tmp);
		cout << Hash.size() << endl;
	}
	return 0;
}
