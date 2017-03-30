#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 300001, maxs = 10001, mod = 1000000007;
int n, a[maxn], b[maxn], len, num[maxs];
char str[maxs];
int divideAndRemain(int x)
{
	if(x == 1)
		return 0;
	int ret = 0;
	const int BASE = (int)1e9;
	for(int i = len - 1; i >= 0; --i)
	{
		LL tmp = (LL)ret * BASE + num[i];
		num[i] = tmp / x;
		ret = tmp % x;
	}
	for( ; len > 1 && !num[len - 1]; --len);
	return ret;
}
int f[2][maxn << 1 | 1], sz[2], cur, pre = 1;
inline void mod_add(int &x, int y)
{
	if((x += y) >= mod)
		x -= mod;
}
inline void mod_sub(int &x, int y)
{
	if((x -= y) < 0)
		x += mod;
}
int main()
{
	scanf("%d", &n);
	a[1] = 1;
	for(int i = 2; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", b + i);
	scanf("%s", str);
	len = strlen(str);
	for(int i = 0; i * 9 < len; ++i)
	{
		int L = i * 9, R = min((i + 1) * 9, len) - 1;
		for(num[i] = 0; L <= R; num[i] = num[i] * 10 + (str[len - 1 - (R--)] - '0'));
	}
	len = (len - 1) / 9 + 1;
	f[cur][sz[cur]++] = 1;
	for(int i = 1; i <= n; ++i)
	{
		int rem = divideAndRemain(a[i]);
		sz[pre] = 0;
		for(int j = rem; j < sz[cur]; j += a[i], ++sz[pre])
			f[pre][sz[pre]] = f[cur][j];
		sz[cur] = sz[pre] + b[i];
		for(int j = 0, ways = 0; j < sz[cur]; ++j)
		{
			if(j < sz[pre])
				mod_add(ways, f[pre][j]);
			if(j > b[i])
				mod_sub(ways, f[pre][j - b[i] - 1]);
			f[cur][j] = ways;
		}
	}
	printf("%d\n", len == 1 && num[0] < sz[cur] ? f[cur][num[0]] : 0);
	return 0;
}
