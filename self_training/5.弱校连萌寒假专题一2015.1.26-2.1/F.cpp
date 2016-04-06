#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int n;
string tmp1, tmp2, dict[256], word[101], tran[101];
int diff(string a, string b)
{
	if(a == b)
		return 0;
	if(a.size() < b.size())
		swap(a, b);
	if(a.substr(0, b.size()) == b)
		return a.size() - b.size();
	return INF;
}
int main()
{
	ios::sync_with_stdio(0);
	while(cin >> tmp1 && tmp1[0] != '*')
	{
		cin >> tmp2;
		dict[tmp1[0]] = tmp2;
	}
	while(cin >> word[n] && word[n][0] != '*')
		++n;
	sort(word, word + n);
	for(int i = 0; i < n; ++i)
		for(int j = 0, k = (int)word[i].size(); j < k; ++j)
			tran[i] += dict[word[i][j]];
	while(cin >> tmp1 && tmp1[0] != '*')
	{
		int dis = INF, pos = 0, flag = 0;
		for(int i = 0; i < n; ++i)
		{
			int tmp = diff(tmp1, tran[i]);
			if(tmp < dis)
			{
				dis = tmp;
				pos = i;
			}
			else if(!tmp && !dis)
				flag = 1;
		}
		cout << word[pos] + (dis ? "?" : (flag ? "!" : "")) << endl;
	}
	return 0;
}
