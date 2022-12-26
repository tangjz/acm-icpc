#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 400001;
int n, m, a[maxn], L[maxn], R[maxn], cnt[maxn], mx, g[maxn];
struct Query
{
	int idx, pos, val, pL, pR;
	bool operator < (const Query &t) const
	{
		return pos < t.pos;
	}
} que[maxn];
bool cmp(const Query &x, const Query &y)
{
	return x.idx < y.idx;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int i = 0; i < m; ++i)
	{
		scanf("%d%d", &que[i].pos, &que[i].val);
		--que[i].pos;
		que[i].idx = i;
	}
	std::sort(que, que + m);
	// pre
	for(int i = 0, j = 0; i < n; ++i)
	{
		for( ; j < m && que[j].pos == i; ++j)
			que[j].pL = std::lower_bound(g + 1, g + mx + 1, que[j].val) - g;
		L[i] = std::lower_bound(g + 1, g + mx + 1, a[i]) - g;
		g[L[i]] = a[i];
		if(mx < L[i])
			++mx;
	}
	// suf
	mx = 0;
	for(int i = n - 1, j = m - 1; i >= 0; --i)
	{
		for( ; j >= 0 && que[j].pos == i; --j)
			que[j].pR = std::lower_bound(g + 1, g + mx + 1, -que[j].val) - g;
		R[i] = std::lower_bound(g + 1, g + mx + 1, -a[i]) - g;
		g[R[i]] = -a[i];
		if(mx < R[i])
			++mx;
	}
	// pro
	for(int i = 0; i < n; ++i)
		if(L[i] + R[i] > mx)
			++cnt[L[i]];
	std::sort(que, que + m, cmp);
	for(int i = 0; i < m; ++i)
		if(que[i].pL + que[i].pR > mx)
			printf("%d\n", que[i].pL + que[i].pR - 1);
		else if(L[que[i].pos] + R[que[i].pos] > mx && cnt[L[que[i].pos]] == 1)
			printf("%d\n", mx - 1);
		else
			printf("%d\n", mx);
	return 0;
}
