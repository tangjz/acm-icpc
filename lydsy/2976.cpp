#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 30;
int n, a[maxn], b[maxn], L[maxn], R[maxn];
int exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
pair<int, int> CRT(int a1, int m1, int a2, int m2)
{
	int x, y, r = exgcd(m1, m2, x, y);
	if((a2 - a1) % r)
		return make_pair(-1, 0);
	x = (a2 - a1) / r * (LL)x % (m2 / r);
	if(x < 0)
		x += m2 / r;
	return make_pair(m1 * x + a1, m1 / r * m2);
}
int main()
{
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", b + i);
		for(int i = 1; i <= n; ++i)
			a[b[i] - 1] = i;
		for(int i = 1; i < n; ++i)
			R[i] = i + 1;
		R[n] = 1;
		L[1] = n;
		for(int i = 2; i <= n; ++i)
			L[i] = i - 1;
		pair<int, int> ans = make_pair(0, 1);
		for(int i = 0, now = n; i < n; ++i)
		{
			int cnt = 0;
			for( ; now != a[i]; ++cnt, now = R[now]);
			ans = CRT(ans.first, ans.second, cnt % (n - i), n - i);
			if(ans.second == 0)
				break;
			L[R[now]] = L[now];
			R[L[now]] = R[now];
			now = L[now];
		}
		if(ans.second == 0)
			puts("NIE");
		else
		{
			if(ans.first <= 0)
				ans.first += ans.second;
			printf("%d\n", ans.first);
		}
	}
	return 0;
}
