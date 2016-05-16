#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef unsigned int UL;
const int maxn = 20000;
int t, n, m, a[maxn], b[maxn], qx[maxn], qy[maxn], ans[maxn];
int tot, seq[maxn + 1 << 1], seg[maxn + 1 << 2];
inline int seg_idx(int L, int R)
{
	return L + R | L != R;
}
void update(int L, int R, int x, int v)
{
	while(L < R)
	{
		seg[seg_idx(L, R)] += v;
		int M = L + R >> 1;
		if(x <= seq[M])
			R = M;
		else
			L = M + 1;
	}
	seg[seg_idx(L, R)] += v;
}
int qL, qR;
int query(int L, int R)
{
	if(qL <= seq[L] && seq[R] <= qR)
		return seg[seg_idx(L, R)];
	int M = L + R >> 1, ret = 0;
	if(qL <= seq[M])
		ret += query(L, M);
	if(qR >= seq[M + 1])
		ret += query(M + 1, R);
	return ret;
}
inline int query(int L, int R, int l, int r)
{
	qL = l;
	qR = r;
	return query(L, R);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		int dig = 0;
		tot = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", a + i);
			seq[tot++] = a[i];
			for( ; 1 << dig <= a[i]; ++dig);
		}
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d", qx + i, qy + i);
			--qx[i];
			seq[tot++] = qy[i];
			for( ; 1 << dig <= qy[i]; ++dig);
		}
		seq[tot++] = 0;
		seq[tot++] = (1u << dig + 1) - 1;
		memset(ans, 0, m * sizeof(int));
		for(int all = (1u << dig + 1) - 1; dig >= 0; --dig, all >>= 1)
		{
			for(int i = 0; i < n; ++i)
				b[i] = a[i] & all;
			for(int i = 0; i < m; ++i)
				qy[i] = qy[i] & all;
			for(int i = 0; i < tot; ++i)
				seq[i] = seq[i] & all;
			std::sort(seq, seq + tot);
			tot = std::unique(seq, seq + tot) - seq;
			memset(seg, 0, (tot << 1) * sizeof(int));
			int cnt = 0;
			for(int i = 0; i < n; ++i)
			{
				cnt += query(0, tot - 1, std::max(0, (1 << dig) - b[i]), all - b[i]);
				if((1u << dig + 1) - b[i] + (1 << dig) <= seq[tot - 1])
					cnt += query(0, tot - 1, (1u << dig + 1) - b[i] + (1 << dig), seq[tot - 1]);
				update(0, tot - 1, b[i], 1);
			}
			for(int i = 0; i < m; ++i)
			{
				update(0, tot - 1, b[qx[i]], -1);
				cnt -= query(0, tot - 1, std::max(0, (1 << dig) - b[qx[i]]), all - b[qx[i]]);
				if((1u << dig + 1) - b[qx[i]] + (1 << dig) <= seq[tot - 1])
					cnt -= query(0, tot - 1, (1u << dig + 1) - b[qx[i]] + (1 << dig), seq[tot - 1]);
				b[qx[i]] = qy[i];
				cnt += query(0, tot - 1, std::max(0, (1 << dig) - b[qx[i]]), all - b[qx[i]]);
				if((1u << dig + 1) - b[qx[i]] + (1 << dig) <= seq[tot - 1])
					cnt += query(0, tot - 1, (1u << dig + 1) - b[qx[i]] + (1 << dig), seq[tot - 1]);
				update(0, tot - 1, b[qx[i]], 1);
				if(cnt & 1)
					ans[i] |= 1 << dig;
			}
		}
		for(int i = 0; i < m; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
