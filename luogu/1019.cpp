#include <iostream>
using namespace std;
char s;
string x[21];
int n, f[21][21] = {}, used[21] = {}, ans = 0;
void dfs(int i, int len)
{
	for(int j = 1; j <= n; ++j)
		if(used[j] < 2 && f[i][j])
		{
			++used[j];
			dfs(j, len + f[i][j]);
			--used[j];
		}
	if(len > ans) ans = len;
}
int main()
{
	int i, j, k, tmp1, tmp2, len;
	ios::sync_with_stdio(false);
	cin >> n;
	for(i = 1; i <= n; ++i) cin >> x[i];
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= n; ++j)
		{
			tmp1 = x[i].length();
			tmp2 = x[j].length();
			if(tmp1 < tmp2) len = tmp1;
			else len = tmp2;
			for(k = 1; k <= len; ++k)
				if(x[i].substr(tmp1 - k, k) == x[j].substr(0, k)) break;
			if(k < len) f[i][j] = tmp2 - k;
		}
	while((s = cin.get()) < 'A' || (s > 'Z' && s < 'a') || s > 'z');
	for(i = 1; i <= n; ++i)
		if(s == x[i][0])
		{
			++used[i];
			dfs(i, x[i].length());
			--used[i];
		}
	cout << ans << endl;
	return 0;
}