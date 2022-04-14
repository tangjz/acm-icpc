#include <cstdio>
const int maxn = 131072;
int n, m, seg[maxn << 1];
void update(int id, int L, int R, int l, int r, int val)
{
	if(l == L && r == R)
	{
		seg[id] |= val;
		return;
	}
	int M = L + R >> 1;
	if(r <= M)
		update(id << 1, L, M, l, r, val);
	else if(M < l)
		update((id << 1) + 1, M + 1, R, l, r, val);
	else
	{
		update(id << 1, L, M, l, M, val);
		update((id << 1) + 1, M + 1, R, M + 1, r, val);
	}
}
int query(int id, int L, int R, int l, int r)
{
	if(l == L && r == R)
		return seg[id];
	int M = L + R >> 1;
	if(r <= M)
		return query(id << 1, L, M, l, r);
	if(M < l)
		return query((id << 1) + 1, M + 1, R, l, r);
	return query(id << 1, L, M, l, M) & query((id << 1) + 1, M + 1, R, M + 1, r);
}
void print(int id, int L, int R)
{
	if(id ^ 1)
		seg[id] |= seg[id >> 1];
	if(L == R)
	{
		printf("%d ", seg[id]);
		return;
	}
	int M = L + R >> 1;
	print(id << 1, L, M);
	print((id << 1) + 1, M + 1, R);
}
int l[maxn], r[maxn], q[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
	{
		scanf("%d%d%d", l + i, r + i, q + i);
		update(1, 1, n, l[i], r[i], q[i]);
	}
	for(int i = 0; i < m; ++i)
		if(query(1, 1, n, l[i], r[i]) != q[i])
		{
			puts("NO");
			return 0;
		}
	puts("YES");
	print(1, 1, n);
	return 0;
}