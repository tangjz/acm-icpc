#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 50010;
int n, m, tsize, s[maxn], pos[maxn], pre[maxn], suf[maxn], tot, que[maxn], L[maxn], R[maxn], D[maxn], idn[maxn], idx[maxn], ans[maxn];
int seg[maxn << 1];
void scan(int &x)
{
	static int ch, flag;
	while(((ch = getchar()) < '0' || ch > '9') && ch != '-');
	x = (flag = ch == '-') ? 0 : ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0';
	if(flag)
		x = -x;
}
bool cmp(const int &x, const int &y)
{
	return L[x] / tsize < L[y] / tsize || L[x] / tsize == L[y] / tsize && R[x] < R[y];
}
inline int id(int L, int R)
{
	return L + R | L != R;
}
void build(int L, int R)
{
	if(L == R)
	{
		if(s[0] != L)
		{
			idn[L] = maxn;
			idx[L] = -maxn;
		}
		seg[id(L, R)] = idx[L] - idn[L];
		return;
	}
	int M = L + R >> 1;
	build(L, M);
	build(M + 1, R);
	seg[id(L, R)] = max(seg[id(L, M)], seg[id(M + 1, R)]);
}
void update(int L, int R, int x)
{
	if(L == R)
	{
		seg[id(L, R)] = idx[L] - idn[L];
		return;
	}
	int M = L + R >> 1;
	if(x <= M)
		update(L, M, x);
	else
		update(M + 1, R, x);
	seg[id(L, R)] = max(seg[id(L, M)], seg[id(M + 1, R)]);
}
int main()
{
	scan(n), scan(m);
	tsize = (int)sqrt(n + 0.233);
	for(int i = 1; i <= n; ++i)
	{
		scan(s[i]);
		s[i] += s[i - 1];
	}
	for(int i = 0; i <= n; ++i)
		que[tot++] = s[i];
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(int i = 0; i <= n; ++i)
		s[i] = lower_bound(que, que + tot, s[i]) - que + 1;
	memset(pos, -1, sizeof pos);
	for(int i = 0; i <= n; ++i)
	{
		if(pos[s[i]] == -1)
			pre[i] = -maxn;
		else
			pre[i] = pos[s[i]];
		pos[s[i]] = i;
	}
	memset(pos, -1, sizeof pos);
	for(int i = n; i >= 0; --i)
	{
		if(pos[s[i]] == -1)
			suf[i] = maxn;
		else
			suf[i] = pos[s[i]];
		pos[s[i]] = i;
	}
	for(int i = 0; i < m; ++i)
	{
		scan(L[i]), scan(R[i]);
		--L[i];
		D[i] = i;
	}
	sort(D, D + m, cmp);
	int ln = 0, rn = 0;
	build(1, tot);
	for(int i = 0; i < m; ++i)
	{
		int &lt = L[D[i]], &rt = R[D[i]];
		while(rn < rt)
		{
			++rn;
			if(idn[s[rn]] == maxn)
				idn[s[rn]] = rn;
			idx[s[rn]] = rn;
			update(1, tot, s[rn]);
		}
		while(rn > rt)
		{
			if(idn[s[rn]] == rn)
				idn[s[rn]] = maxn;
			idx[s[rn]] = pre[rn] >= lt ? pre[rn] : -maxn;
			update(1, tot, s[rn]);
			--rn;
		}
		while(ln < lt)
		{
			idn[s[ln]] = suf[ln] <= rt ? suf[ln] : maxn;
			if(idx[s[ln]] == ln)
				idx[s[ln]] = -maxn;
			update(1, tot, s[ln]);
			++ln;
		}
		while(ln > lt)
		{
			--ln;
			idn[s[ln]] = ln;
			if(idx[s[ln]] == -maxn)
				idx[s[ln]] = ln;
			update(1, tot, s[ln]);
		}
		ans[D[i]] = seg[id(1, tot)];
	}
	for(int i = 0; i < m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}