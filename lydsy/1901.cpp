#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200010, maxo = 1600100;
int n, m, tot, sz;
int val[maxn], que[maxn];
int A[maxn], B[maxn], K[maxn], root[maxn];
int sum[maxo], ls[maxo], rs[maxo], belong[maxo];
int l[30], r[30], a, b;
void update(int idx, int last, int L, int R, int &rt, int pos, int x)
{
	if(belong[last] == idx)
		rt = last;
	else
	{
		rt = ++sz;
		belong[rt] = idx;
	}
	sum[rt] = sum[last] + x;
	ls[rt] = ls[last];
	rs[rt] = rs[last];
	if(L == R)
		return;
	int M = L + R >> 1;
	if(pos <= M)
		update(idx, ls[last], L, M, ls[rt], pos, x);
	else
		update(idx, rs[last], M + 1, R, rs[rt], pos, x);
}
int query(int L, int R, int k)
{
	if(L == R)
		return L;
	int cnt = 0;
	for(int i = 1; i <= b; ++i)
		cnt += sum[ls[r[i]]];
	for(int i = 1; i <= a; ++i)
		cnt -= sum[ls[l[i]]];
	int M = L + R >> 1;
	if(cnt >= k)
	{
		for(int i = 1; i <= a; ++i)
			l[i] = ls[l[i]];
		for(int i = 1; i <= b; ++i)
			r[i] = ls[r[i]];
		return query(L, M, k);
	}
	else
	{
		for(int i = 1; i <= a; ++i)
			l[i] = rs[l[i]];
		for(int i = 1; i <= b; ++i)
			r[i] = rs[r[i]];
		return query(M + 1, R, k - cnt);
	}
}
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		sz = tot = 0;
		memset(K, 0, sizeof K);
		memset(root, 0, sizeof root);
		scan(m);
		for(int i = 1; i <= n; ++i)
		{
			scan(val[i]);
			que[tot++] = val[i];
		}
		for(int i = 1; i <= m; ++i)
		{
			char op[2];
			scanf("%s", op);
			scan(A[i]);
			scan(B[i]);
			if(op[0] == 'Q')
				scan(K[i]);
			else
				que[tot++] = B[i];
		}
		sort(que, que + tot);
		tot = unique(que, que + tot) - que;
		for(int i = 1; i <= n; ++i)
		{
			val[i] = lower_bound(que, que + tot, val[i]) - que + 1;
			for(int x = i; x <= n; x += x & -x)
				update(x, root[x], 1, tot, root[x], val[i], 1);
		}
		for(int i = 1; i <= m; ++i)
			if(K[i])
			{
				a = b = 0;
				for(int x = A[i] - 1; x > 0; x -= x & -x)
					l[++a] = root[x];
				for(int x = B[i]; x > 0; x -= x & -x)
					r[++b] = root[x];
				printf("%d\n", que[query(1, tot, K[i]) - 1]);
			}
			else
			{
				for(int x = A[i]; x <= n; x += x & -x)
					update(x, root[x], 1, tot, root[x], val[A[i]], -1);
				val[A[i]] = lower_bound(que, que + tot, B[i]) - que + 1;
				for(int x = A[i]; x <= n; x += x & -x)
					update(x, root[x], 1, tot, root[x], val[A[i]], 1);
			}
	}
	return 0;
}
