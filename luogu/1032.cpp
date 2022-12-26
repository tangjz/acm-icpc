#include <map>
#include <string>
#include <iostream>
using namespace std;
map<string, int> Hash;
struct Node
{
	int step, len;
	string ch;
	bool hash()
	{
		if(Hash[ch]) return false;
		Hash[ch] = 1;
		return true;
	}
} data[5550];
int length[2][7];
string ans, a[7], b[7];
int main()
{
	int i, l = 0, r = 0, m = 6;
	ios::sync_with_stdio(false);
	cin >> data[0].ch >> ans;
	for(i = 1; i <= 6; ++i)
	{
		cin >> a[i] >> b[i];
		length[0][i] = a[i].length();
		length[1][i] = b[i].length();
		if(a[i].empty())
		{
			m = --i;
			break;
		}
	}
	data[0].len = data[0].ch.length();
	while(l <= r && data[l].step <= 10)
	{
		for(i = 1; i <= m; ++i)
		{
			string::size_type len = 0;
			while((len = data[l].ch.find(a[i], len)) != string::npos)
			{
				data[++r] = data[l];
				data[r].ch.replace(len, length[0][i], b[i].c_str(), length[1][i]);
				data[r].len += length[1][i] - length[0][i];
				++data[r].step;
				if(data[r].ch == ans)
				{
					cout << data[r].step << endl;
					return 0;
				}
				if(!data[r].hash()) --r;
				if(++len >= data[l].len) break;
			}
		}
		++l;
	}
	cout << "NO ANSWER!" << endl;
}
