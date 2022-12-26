#include <map>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int size[52], now, ans;
map<int, int> array[52];
int trans(char ch)
{
	return ch <= 'Z' ? ch - 'A' + 26 : ch - 'a';
}
int GetValue(string a)
{
	if(a.find('[') == string::npos)
	{
		int ret = 0;
		for(int i = 0, j = a.size(); i < j; ++i)
			ret = (ret << 3) + (ret << 1) + a[i] - '0';
		return ret;
	}
	int name = trans(a[0]), idx = GetValue(a.substr(2, a.size() - 3));
	if(idx == -1 || idx >= size[name] || array[name].find(idx) == array[name].end())
		return -1;
	return array[name][idx];
}
int main()
{
	ios::sync_with_stdio(0);
	string tmp;
	while(cin >> tmp)
		if(tmp == ".")
		{
			if(now)
				cout << ans << endl;
			ans = now = 0;
			for(int i = 0; i < 52; ++i)
				if(size[i])
				{
					array[i].clear();
					size[i] = 0;
				}
		}
		else
		{
			++now;
			if(ans)
				continue;
			string::size_type pos = tmp.find('=');
			if(pos == string::npos)
			{
				int name = trans(tmp[0]), idx = GetValue(tmp.substr(2, tmp.size() - 3));
				if(idx == -1)
				{
					ans = now;
					continue;
				}
				size[name] = idx;
			}
			else
			{
				int name = trans(tmp[0]), idx = GetValue(tmp.substr(2, pos - 3)), value = GetValue(tmp.substr(pos + 1));
				if(idx == -1 || idx >= size[name] || value == -1)
				{
					ans = now;
					continue;
				}
				array[name][idx] = value;
			}
		}
	return 0;
}
