#include <stdio.h>
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
struct Fibonacci
{
	int num1, num2;
	Fibonacci operator * (const Fibonacci &x) const
	{
		return (Fibonacci){(int)(((LL)num1 * x.num1 + (LL)num2 * x.num2) % mod),
		(int)(((LL)num1 * x.num2 + (LL)num2 * (x.num1 + x.num2)) % mod)};
	}
	Fibonacci pow(int k)
	{
		Fibonacci ret = (Fibonacci){1, 0}, tmp = *this;
		while(k)
		{
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A = {0, 1};
struct Matrix
{
	int num[2][2];
	bool operator == (const Matrix &t) const
	{
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				if(num[i][j] != t.num[i][j])
					return 0;
		return 1;
	}
	Matrix operator + (const Matrix &t) const
	{
		Matrix ret = *this;
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				if((ret.num[i][j] += t.num[i][j]) >= mod)
					ret.num[i][j] -= mod;
		return ret;
	}
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {};
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j) if(num[i][j])
				for(int k = 0; k < 2; ++k) if(t.num[j][k])
					ret.num[i][k] = (ret.num[i][k] + (LL)num[i][j] * t.num[j][k]) % mod;
		return ret;
	}
} I = {1, 0, 0, 1};
struct Segment
{
	Matrix val, tag;
} seg[maxn << 1];
inline int seg_idx(int L, int R)
{
	return L + R | L < R;
}
inline void push_up(int rt, int lch, int rch)
{
	seg[rt].val = seg[lch].val + seg[rch].val;
}
inline void push_down(int rt, int lch, int rch)
{
	if(!(seg[rt].tag == I))
	{
		seg[lch].val = seg[lch].val * seg[rt].tag;
		seg[lch].tag = seg[lch].tag * seg[rt].tag;
		seg[rch].val = seg[rch].val * seg[rt].tag;
		seg[rch].tag = seg[rch].tag * seg[rt].tag;
		seg[rt].tag = I;
	}
}
inline void init(int L, int R)
{
	int rt = seg_idx(L, R);
	seg[rt].tag = I;
	if(L == R)
	{
		int x;
		scanf("%d", &x);
		Fibonacci tmp = A.pow(x);
		int tmp2 = tmp.num1 + tmp.num2;
		if(tmp2 >= mod)
			tmp2 -= mod;
		seg[rt].val = (Matrix){tmp.num1, tmp.num2, tmp.num2, tmp2};
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	init(L, M);
	init(M + 1, R);
	seg[rt].val = seg[lch].val + seg[rch].val;
}
inline void update(int L, int R, int l, int r, const Matrix &x)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		seg[rt].val = seg[rt].val * x;
		seg[rt].tag = seg[rt].tag * x;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	push_down(rt, lch, rch);
	if(l <= M)
		update(L, M, l, r, x);
	if(r > M)
		update(M + 1, R, l, r, x);
	push_up(rt, lch, rch);
}
inline Matrix query(int L, int R, int l, int r)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[rt].val;
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	Matrix ret = {};
	push_down(rt, lch, rch);
	if(l <= M)
		ret = ret + query(L, M, l, r);
	if(r > M)
		ret = ret + query(M + 1, R, l, r);
	push_up(rt, lch, rch);
	return ret;
}
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	init(1, n);
	while(m--)
	{
		int t, l, r, x;
		scanf("%d%d%d", &t, &l, &r);
		if(t == 1)
		{
			scanf("%d", &x);
			Fibonacci tmp = A.pow(x);
			int tmp2 = tmp.num1 + tmp.num2;
			if(tmp2 >= mod)
				tmp2 -= mod;
			Matrix tag = (Matrix){tmp.num1, tmp.num2, tmp.num2, tmp2};
			update(1, n, l, r, tag);
		}
		else
		{
			Matrix ret = query(1, n, l, r);
			printf("%d\n", ret.num[0][1]);
		}
	}
	return 0;
}
