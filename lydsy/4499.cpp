#include <cstdio>
#include <algorithm>
typedef std::pair<int, int> func;
typedef long long LL;
const int maxn = 200001, mod = 1000000007;
int n, m;
func seg[maxn << 1];
inline int calc(func f, int x)
{
	return ((LL)f.first * x + f.second) % mod;
}
inline func merge(func f, func g)
{
	return (func){(int)((LL)f.first * g.first % mod), (int)(((LL)f.second * g.first + g.second) % mod)};
}
inline int seg_idx(int L, int R)
{
	return L + R | L < R;
}
void build(int L, int R)
{
	int o = seg_idx(L, R);
	if(L == R)
	{
		scanf("%d%d", &seg[o].first, &seg[o].second);
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	build(L, M);
	build(M + 1, R);
	seg[o] = merge(seg[lch], seg[rch]);
}
void update(int L, int R, int x, func f)
{
	int o = seg_idx(L, R);
	if(L == R)
	{
		seg[o] = f;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		update(L, M, x, f);
	else
		update(M + 1, R, x, f);
	seg[o] = merge(seg[lch], seg[rch]);
}
func query(int L, int R, int l, int r)
{
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = L + R >> 1;
	if(r <= M)
		return query(L, M, l, r);
	if(l > M)
		return query(M + 1, R, l, r);
	return merge(query(L, M, l, r), query(M + 1, R, l, r));
}
int main()
{
	scanf("%d%d", &n, &m);
	build(1, n);
	while(m--)
	{
		int a, b, c;
		char op[2];
		scanf("%s%d%d%d", op, &a, &b, &c);
		if(op[0] == 'Q')
			printf("%d\n", calc(query(1, n, a, b), c));
		else
			update(1, n, a, (func){b, c});
	}
	return 0;
}
