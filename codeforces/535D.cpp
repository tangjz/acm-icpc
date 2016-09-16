#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 1000010, maxd = 21, mod = 1000000007;
int n, len, m, f[maxn], yy[maxn], po[maxn], ans;
char s[maxn];
bool vis[maxn];
int main()
{
	scanf("%d%d%s", &n, &m, s);
	len = strlen(s);
	for(int i = 1, j; i < len; ++i)
	{
		j = f[i];
		while(j && s[i] != s[j])
			j = f[j];
		if(s[i] == s[j])
			f[i + 1] = j + 1;
	}
	for(int i = len; i > 0; i = f[i])
		vis[i] = 1;
	for(int i = 1; i <= m; ++i)
		scanf("%d", yy + i);
	po[0] = 1;
	for(int i = 1; i <= n; ++i)
		po[i] = po[i - 1] * 26LL % mod;
	if(!m)
	{
		printf("%d\n", po[n]);
		return 0;
	}
	ans = po[yy[1] - 1];
	for(int i = 1; i < m && ans; ++i)
		if(yy[i] + len <= yy[i + 1])
			ans = (long long)ans * po[yy[i + 1] - yy[i] - len] % mod;
		else if(!vis[yy[i] + len - yy[i + 1]])
			ans = 0;
	ans = (long long)ans * po[n - yy[m] - len + 1] % mod;
	printf("%d\n", ans);
	return 0;
}
