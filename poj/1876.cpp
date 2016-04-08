#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef map<string, int> Users;
map<string, Users> MTA;
string sender, text;
map<string, int> idx, vis;
vector<vector<string> > recver;
int main()
{
	ios::sync_with_stdio(0);
	while(cin >> text && text != "*")
	{
		int cnt;
		Users tmp;
		tmp.clear();
		cin >> text >> cnt;
		while(cnt--)
		{
			cin >> sender;
			tmp[sender] = 1;
		}
		MTA[text] = tmp;
	}
	while(cin >> sender && sender != "*")
	{
		int cnt = 0;
		string::size_type pos = sender.find('@');
		string from = sender.substr(pos + 1), to, tmp;
		idx.clear();
		vis.clear();
		for(vector<vector<string> >::iterator it = recver.begin(), jt = recver.end(); it < jt; ++it)
			(*it).clear();
		recver.clear();
		while(cin >> tmp && tmp != "*")
		{
			to = tmp.substr(tmp.find('@') + 1);
			if(vis.find(tmp) != vis.end())
				continue;
			vis[tmp] = 1;
			if(idx.find(to) == idx.end())
			{
				idx[to] = cnt++;
				vector<string> name;
				name.clear();
				name.push_back(tmp);
				recver.push_back(name);
			}
			else
				recver[idx[to]].push_back(tmp);
		}
		text = "";
		getline(cin, tmp);
		while(getline(cin, tmp) && tmp != "*")
			text += "     " + tmp + "\n";
		Users List = MTA[from];
		if(List.find(sender.substr(0, sender.find('@'))) == List.end())
			continue;
		for(vector<vector<string> >::iterator it = recver.begin(), jt = recver.end(); it < jt; ++it)
		{
			vector<string> &temp = *it;
			to = temp[0].substr(temp[0].find('@') + 1);
			List = MTA[to];
			cout << "Connection between " + from + " and " + to << endl;
			cout << "     HELO " + from << endl;
			cout << "     250" << endl;
			cout << "     MAIL FROM:<" + sender + ">" << endl;
			cout << "     250" << endl;
			bool flag = 0;
			for(vector<string>::iterator it = temp.begin(), jt = temp.end(); it < jt; ++it)
			{
				cout << "     RCPT TO:<" + *it + ">" << endl;
				if(List.find((*it).substr(0, (*it).find('@'))) != List.end())
				{
					flag = 1;
					cout << "     250" << endl;
				}
				else
					cout << "     550" << endl;
			}
			if(flag)
			{
				cout << "     DATA" << endl;
				cout << "     354" << endl;
				cout << text << "     ." << endl;
				cout << "     250" << endl;
			}
			cout << "     QUIT" << endl;
			cout << "     221" << endl;
		}
	}
	return 0;
}