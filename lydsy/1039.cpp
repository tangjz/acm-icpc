#include <cstdio>
#include <algorithm>
using namespace std;
const int maxm = 200010, maxs = 1650050;
struct Node
{
	int fz, fm, dot, det;
	bool operator < (const Node &x) const
	{
		if(fz != x.fz)
			return fz < x.fz;
		if(fm != x.fm)
			return fm < x.fm;
		if(dot != x.dot)
			return dot < x.dot;
		return det < x.det;
	}
	bool operator == (const Node &x) const
	{
		return fz == x.fz && fm == x.fm && dot == x.dot && det == x.det;
	}
} a[maxs], que[maxs];
int n, m, tot, idx[maxm << 1], fir[maxm << 1], sz[maxm << 1], q_tot;
int len, seq[maxs], Log[maxs], seg[maxs << 1], pL, pR, pV, ans[maxm];
int sa[maxs], rk[maxs], ht[maxs];
inline Node Make_Node(int x1, int y1, int x2, int y2)
{
	int a = x1 * x1 + y1 * y1, b = x2 * x2 + y2 * y2, c = x1 * x2 + y1 * y2, d = x1 * y2 - x2 * y1, r;
	r = __gcd(a, b);
	a /= r;
	b /= r;
	r = __gcd(abs(c), abs(d));
	c /= r;
	d /= r;
	return (Node){a, b, c, d};
}
bool check(int L, int R)
{
	for(int i = L; i < R; ++i)
		if(a[i].det)
			return 1;
	return 0;
}
void insert(int id, int size, int *x, int *y)
{
	idx[tot] = id;
	fir[tot] = len;
	sz[tot] = size - 2;
	for(int i = 2; i < size; ++i)
	{
		Node tmp = Make_Node(x[i - 1] - x[i - 2], y[i - 1] - y[i - 2], x[i] - x[i - 1], y[i] - y[i - 1]);
		a[len++] = tmp;
		que[q_tot++] = tmp;
	}
	++tot;
}
void init()
{
	int *tmpx = rk, *tmpy = ht;
	que[q_tot++] = (Node){0, 0, 0, 0};
	for(int i = 0; i < m; ++i)
	{
		int size;
		scanf("%d", &size);
		for(int j = 0; j < size; ++j)
			scanf("%d%d", tmpx + j, tmpy + j);
		if(size > n || size <= 2)
		{
			if(size <= n)
				ans[i] = n - size + 1;
			continue;
		}
		insert(i, size, tmpx, tmpy);
		a[len++] = (Node){0, 0, 0, 0};
		if(check(fir[tot - 1], len))
		{
			for(int j = 0; j < size; ++j)
				tmpy[j] = -tmpy[j];
			insert(i, size, tmpx, tmpy);
			a[len++] = (Node){0, 0, 0, 0};
		}
	}
	for(int i = 0; i < n; ++i)
		scanf("%d%d", tmpx + i, tmpy + i);
	insert(m, n, tmpx, tmpy);
	--tot;
	sort(que, que + q_tot);
	q_tot = unique(que, que + q_tot) - que;
	for(int i = 0; i < len; ++i)
		seq[i] = lower_bound(que, que + q_tot, a[i]) - que;
	seq[len] = -1;
}
void suffix_sort()
{
	int *x = rk, *y = ht, *c = Log;
	for(int i = 0; i < q_tot; ++i)
		c[i] = 0;
	for(int i = 0; i < len; ++i)
		++c[x[i] = seq[i]];
	for(int i = 1; i < q_tot; ++i)
		c[i] += c[i - 1];
	for(int i = len - 1; i >= 0; --i)
		sa[--c[x[i]]] = i;
	for(int k = 1; k < len; k <<= 1)
	{
		int p = 0;
		for(int i = len - k; i < len; ++i)
			y[p++] = i;
		for(int i = 0; i < len; ++i)
			if(sa[i] >= k)
				y[p++] = sa[i] - k;
		for(int i = 0; i < q_tot; ++i)
			c[i] = 0;
		for(int i = 0; i < len; ++i)
			++c[x[y[i]]];
		for(int i = 1; i < q_tot; ++i)
			c[i] += c[i - 1];
		for(int i = len - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1;
		x[sa[0]] = 0;
		for(int i = 1; i < len; ++i)
			x[sa[i]] = (y[sa[i - 1]] == y[sa[i]]
			&& (sa[i - 1] + k < len ? y[sa[i - 1] + k] : -1) == (sa[i] + k < len ? y[sa[i] + k] : -1) ? p - 1 : p++);
		if(p >= len)
			break;
		q_tot = p;
	}
	for(int i = 0; i < len; ++i)
		rk[sa[i]] = i;
	ht[0] = 0;
	for(int i = 0, j, k = 0; i < len; ++i)
	{
		if(k)
			--k;
		if(!rk[i])
			continue;
		for(j = sa[rk[i] - 1]; seq[i + k] == seq[j + k]; ++k);
		ht[rk[i]] = k;
	}
}
inline int seg_idx(int L, int R)
{
	return L + R | L != R;
}
void seg_init(int L, int R)
{
	int o = seg_idx(L, R);
	if(L == R)
	{
		seg[o] = ht[L];
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_init(L, M);
	seg_init(M + 1, R);
	seg[o] = min(seg[lch], seg[rch]);
}
void seg_findL(int L, int R, int x, int v, int &event)
{
	int o = seg_idx(L, R);
	if(L == R)
	{
		if(!event)
		{
			if(seg[o] >= v)
				pV = seg[o];
			else
			{
				pL = L;
				event = 2;
			}
		}
		else
			pL = L;
		++event;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(!event)
	{
		if(x <= M)
			seg_findL(L, M, x, v, event);
		else
		{
			seg_findL(M + 1, R, x, v, event);
			pV = min(pV, seg[lch]);
		}
		if(event == 1 && pV < v)
		{
			++event;
			seg_findL(L, M, x, v, event);
		}
		return;
	}
	if(seg[rch] >= v)
		seg_findL(L, M, x, v, event);
	else
		seg_findL(M + 1, R, x, v, event);
}
void seg_findR(int L, int R, int x, int v, int &event)
{
	int o = seg_idx(L, R);
	if(L == R)
	{
		if(!event)
		{
			if(seg[o] >= v)
				pV = seg[o];
			else
			{
				pR = R - 1;
				event = 2;
			}
		}
		else
			pR = R - 1;
		++event;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(!event)
	{
		if(x <= M)
		{
			seg_findR(L, M, x, v, event);
			pV = min(pV, seg[rch]);
		}
		else
			seg_findR(M + 1, R, x, v, event);
		if(event == 1 && pV < v)
		{
			++event;
			seg_findR(M + 1, R, x, v, event);
		}
		return;
	}
	if(seg[lch] < v)
		seg_findR(L, M, x, v, event);
	else
		seg_findR(M + 1, R, x, v, event);
}
void solve()
{
	seg_init(0, len - 1);
	int *cnt = ht;
	for(int i = 0; i < len; ++i)
		cnt[i] = (i ? cnt[i - 1] : 0) + (sa[i] >= fir[tot]);
	for(int i = 0; i < tot; ++i)
	{
		int &x = rk[fir[i]], &size = sz[i], event;
		seg_findL(0, len - 1, x, size, event = 0);
		if(event == 1)
			pL = 0;
		if(x + 1 < len)
		{
			seg_findR(0, len - 1, x + 1, size, event = 0);
			if(event == 1)
				pR = len - 1;
		}
		else
			pR = x;
		ans[idx[i]] += cnt[pR] - (pL ? cnt[pL - 1] : 0);
	}
	for(int i = 0; i < m; ++i)
		printf("%d\n", ans[i]);
}
int main()
{
	scanf("%d%d", &n, &m);
	if(n <= 2)
	{
		for(int i = 0; i < m; ++i)
		{
			int sz;
			scanf("%d", &sz);
			for(int j = 0; j < sz; ++j)
				scanf("%*d%*d");
			printf("%d\n", sz <= n ? n - sz + 1 : 0);
		}
		return 0;
	}
	init();
	suffix_sort();
	solve();
	return 0;
}
