#include <map>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<string, string> Book;
map<string, string> Dict;
set<Book> Lib, Rcv;
string tmp1, tmp2;
int main()
{
	ios::sync_with_stdio(0);
	while(getline(cin, tmp1) && tmp1 != "END")
	{
		string::size_type pos = tmp1.rfind("\"");
		tmp2 = tmp1.substr(pos + 5);
		tmp1 = tmp1.substr(1, pos - 1);
		Dict[tmp1] = tmp2;
		Lib.insert(make_pair(tmp2, tmp1));
	}
	while(getline(cin, tmp1) && tmp1 != "END")
		if(tmp1[0] == 'B')
		{
			tmp2 = tmp1.substr(8, tmp1.size() - 9);
			Lib.erase(make_pair(Dict[tmp2], tmp2));
		}
		else if(tmp1[0] == 'R')
		{
			tmp2 = tmp1.substr(8, tmp1.size() - 9);
			Rcv.insert(make_pair(Dict[tmp2], tmp2));
		}
		else
		{
			for(set<Book>::iterator it = Rcv.begin(), jt = Rcv.end(); it != jt; ++it)
			{
				set<Book>::iterator pos = Lib.insert(*it).first;
				if(pos == Lib.begin())
					cout << "Put \"" + it -> second + "\" first" << endl;
				else
					cout << "Put \"" + it -> second + "\" after \"" + (--pos) -> second + "\"" << endl;
			}
			cout << "END" << endl;
			Rcv.clear();
		}
	return 0;
}
