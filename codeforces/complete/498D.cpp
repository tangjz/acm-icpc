#include <cstdio>
const int maxn = 262144;
int n, q, seg[maxn][60];
void build(int o, int L, int R)
{
	if(L == R)
	{
		int x;
		scanf("%d", &x);
		for(int i = 0; i < 60; ++i)
			seg[o][i] = (i % x == 0) + 1;
		return;
	}
	int M = L + R >> 1;
	build(o + o, L, M);
	build(o + o + 1, M + 1, R);
	for(int i = 0; i < 60; ++i)
		seg[o][i] = seg[o + o][i] + seg[o + o + 1][(i + seg[o + o][i]) % 60];
}
void update(int o, int L, int R, const int &id, const int &x)
{
	if(L == R)
	{
		for(int i = 0; i < 60; ++i)
			seg[o][i] = (i % x == 0) + 1;
		return;
	}
	int M = L + R >> 1;
	if(id <= M)
		update(o + o, L, M, id, x);
	else
		update(o + o + 1, M + 1, R, id, x);
	for(int i = 0; i < 60; ++i)
		seg[o][i] = seg[o + o][i] + seg[o + o + 1][(i + seg[o + o][i]) % 60];
}
int query(int o, int L, int R, int l, int r, int sta)
{
	if(L == l && R == r)
		return seg[o][sta];
	int M = L + R >> 1;
	if(r <= M)
		return query(o + o, L, M, l, r, sta);
	if(M < l)
		return query(o + o + 1, M + 1, R, l, r, sta);
	int ret = query(o + o, L, M, l, M, sta);
	return ret + query(o + o + 1, M + 1, R, M + 1, r, (sta + ret) % 60);
}
int main()
{
	scanf("%d", &n);
	build(1, 1, n);
	scanf("%d", &q);
	while(q--)
	{
		char op[2];
		int x, y;
		scanf("%s%d%d", op, &x, &y);
		if(op[0] == 'A')
			printf("%d\n", query(1, 1, n, x, y - 1, 0));
		else
			update(1, 1, n, x, y);
	}
	return 0;
}
