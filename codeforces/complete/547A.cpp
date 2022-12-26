#include <map>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <ctime>
//#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000010, mod = 1000000007;
int m, h1, a1, x1, y1, h2, a2, x2, y2, s1, len1, f[maxn], s2, len2, g[maxn];
typedef long long LL;
LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	LL r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
//x = a1 + m1 * t1
//x = a2 + m2 * t2
//m1 * t1 - m2 * t2 = a2 - a1
//x = a1 + m1 * t1 = a1 + m1 * t10 + m1 * m2 / gcd(m1, m2)
LL CRT(LL a1, LL m1, LL a2, LL m2, LL &mod)
{
	LL res = a1;
	mod = m1;
	LL x, y, r;
	r = exgcd(mod, m2, x, y);
	if((a2 - res) % r != 0)
		return -1;
	x = (a2 - res) / r * x % (m2 / r);
	if(x < 0)
		x += m2 / r;
	res += mod * x;
	mod *= m2 / r;
	return res;
}
int main()
{
	scanf("%d", &m);
	scanf("%d%d%d%d", &h1, &a1, &x1, &y1);
	memset(f, -1, sizeof f);
	for(int i = 0, now = h1; i <= m; ++i, now = ((long long)x1 * now + y1) % m)
		if(f[now] == -1)
		{
			f[now] = i;
		}
		else
		{
			s1 = f[now];
			len1 = i - f[now];
			break;
		}
	if(f[a1] == -1)
	{
		puts("-1");
		return 0;
	}
	scanf("%d%d%d%d", &h2, &a2, &x2, &y2);
	memset(g, -1, sizeof g);
	for(int i = 0, now = h2; i <= m; ++i, now = ((long long)x2 * now + y2) % m)
		if(g[now] == -1)
		{
			g[now] = i;
		}
		else
		{
			s2 = g[now];
			len2 = i - g[now];
			break;
		}
	if(g[a2] == -1)
	{
		puts("-1");
		return 0;
	}
	long long mod;
	long long res = CRT(f[a1] % len1, len1, g[a2] % len2, len2, mod);
	if(res != -1 && res < f[a1])
		res += ((f[a1] - res - 1) / mod + 1) * mod;
	if(res != -1 && res < g[a2])
		res += ((g[a2] - res - 1) / mod + 1) * mod;
	if(res == -1 || f[a1] < s1 && res >= s1 || g[a2] < s2 && res >= s2)
		puts("-1");
	else
		printf("%I64d\n", res);
	return 0;
}
