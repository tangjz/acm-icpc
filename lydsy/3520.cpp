#include <cmath>
#include <stdio.h>
#include <algorithm>
typedef long double LDB;
const int maxn = 1000, maxm = maxn * maxn;
int n, tot, ord[maxm];
short deg[maxn], L[maxm], R[maxm], ans;
LDB a[maxn], b[maxm];
void upd(short &x, short y)
{
	if(x < y)
		x = y;
}
bool cmp(const int &x, const int &y)
{
	return b[x] < b[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
	{
		int x;
		scanf("%d", &x);
		a[i] = log((LDB)x);
	}
	for(int i = 0; i < n; ++i)
	{
		LDB s = 0;
		for(int j = i + 1; j < n; ++j)
		{
			s += a[j];
			ord[tot] = tot;
			L[tot] = i;
			R[tot] = j;
			b[tot++] = s / (j - i);
		}
	}
	std::sort(ord, ord + tot, cmp);
	for(int i = 0, j = 0; i < tot; )
	{
		for( ; j < tot && !(b[ord[i]] < b[ord[j]]); ++j)
		{
			upd(ans, ++deg[L[ord[j]]]);
			upd(ans, ++deg[R[ord[j]]]);
		}
		for( ; i < j; ++i)
		{
			--deg[L[ord[i]]];
			--deg[R[ord[i]]];
		}
	}
	printf("%d\n", ans + 1);
	return 0;
}
