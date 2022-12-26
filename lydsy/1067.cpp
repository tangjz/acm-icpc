/*
 * ST表练习题
 */
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50002;
int n, m, year[maxn], st[maxn][19], Log[maxn];
inline int query(int l, int r)
{
	if(l > r) return 0;
	int len = Log[r - l + 1];
	return max(st[l][len], st[r - (1 << len) + 1][len]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &year[i], &st[i][0]);
	for(int j = 1; j <= 18; ++j)
		for(int i = 1; i <= n - (1 << j) + 1; ++i)
			st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
	for(int i = 1, j = 1, k = -1; i <= n; ++i)
		if(i == j) Log[i] = ++k, j <<= 1;
		else Log[i] = k;
	scanf("%d", &m);
	while(m--)
	{
		int x, y, l, r;
		scanf("%d%d", &x, &y);
		l = lower_bound(year + 1, year + n + 1, x) - year;
		r = lower_bound(year + 1, year + n + 1, y) - year;
		if(l <= n && year[l] == x)
			if(r <= n && year[r] == y)
				if(st[l][0] >= st[r][0] && query(l + 1, r - 1) < st[r][0])
					if(r - l == y - x) puts("true");
					else puts("maybe");
				else puts("false");
			else if(query(l + 1, r - 1) < st[l][0]) puts("maybe");
			else puts("false");
		else if(r <= n && year[r] == y && query(l, r - 1) >= st[r][0]) puts("false");
		else puts("maybe");
	}
	return 0;
}
