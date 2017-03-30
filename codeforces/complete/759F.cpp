#include <stdio.h>
#include <cassert>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
typedef std::pair<int, int> Node;
int mod_inv(int x)
{
	return x <= 1 ? x : (int)(mod - mod / x * (LL)mod_inv(mod % x) % mod);
}
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
Node merge(Node a, Node b)
{
	return (Node){(int)(((LL)a.first * b.second + b.first) % mod), (int)(((LL)a.second * b.second) % mod)};
}
Node pow(Node x, int k)
{
	Node ret = (Node){0, 1}, tmp = (Node){1, x.second};
	for( ; k > 0; k >>= 1, tmp = merge(tmp, tmp))
		if(k & 1)
			ret = merge(ret, tmp);
	return (Node){(int)((LL)x.first * ret.first % mod), ret.second};
}
Node gen(int L, int R, int L1, int R1, int pw) // [L, R), L != R, |L| = |R-1| = len, 10^len = pw
{
	if(pw == 1)
		return (Node){(int)((((L + R - 1LL) * (R - L)) >> 1) % mod), 1};
	int ivs = mod_inv(pw - 1), ppw = mod_pow(pw, L1 < R1 ? R1 - L1 : R1 - L1 + mod - 1);
	int ret = ((LL)L * ppw - R + (ppw - 1LL) * ivs) % mod * ivs % mod;
	if(ret < 0)
		ret += mod;
	return (Node){ret, ppw};
}
struct Number {
	int val, val1, pw;
} num;
int typ;
char str[maxn], *ptr = str;
void nxtSym()
{
	switch(*ptr) {
		case '\0' : typ = 0; break;
		case '+' : typ = 1; ++ptr; break;
		case '-' : typ = 2; ++ptr; break;
		case '(' : typ = 3; ++ptr; break;
		case ')' : typ = 4; ++ptr; break;
		default : // number
			typ = 5;
			num.val = num.val1 = 0;
			num.pw = 1;
			for( ; *ptr >= '0' && *ptr <= '9'; ++ptr)
			{
				num.val = (10LL * num.val + (*ptr - '0')) % mod;
				num.val1 = (10LL * num.val1 + (*ptr - '0')) % (mod - 1);
				num.pw = 10LL * num.pw % mod;
			}
	}
}
Node expression();
Node term()
{
	assert(typ == 5);
	Number cur = num;
	nxtSym();
	if(typ == 2)
	{
		nxtSym();
		assert(typ == 5);
		Number nxt = num;
		nxtSym();
		if(cur.pw == nxt.pw)
		{
			if((++nxt.val) >= mod)
				nxt.val -= mod;
			if((++nxt.val1) >= mod - 1)
				nxt.val1 -= mod - 1;
			return gen(cur.val, nxt.val, cur.val1, nxt.val1, cur.pw);
		}
		int dig = 1, dig1 = 1;
		while(dig != cur.pw)
		{
			dig = 10LL * dig % mod;
			dig1 = 10LL * dig1 % (mod - 1);
		}
		Node ret = gen(cur.val, dig, cur.val1, dig1, cur.pw);
		while(dig != nxt.pw)
		{
			int nxtdig = 10LL * dig % mod, nxtdig1 = 10LL * dig1 % (mod - 1);
			if(nxtdig == nxt.pw)
			{
				if((++nxt.val) >= mod)
					nxt.val -= mod;
				if((++nxt.val1) >= mod - 1)
					nxt.val1 -= mod - 1;
				ret = merge(ret, gen(dig, nxt.val, dig1, nxt.val1, nxtdig));
			}
			else
				ret = merge(ret, gen(dig, nxtdig, dig1, nxtdig1, nxtdig));
			dig = nxtdig;
			dig1 = nxtdig1;
		}
		return ret;
	}
	if(typ == 3)
	{
		nxtSym();
		Node ret = expression();
		assert(typ == 4);
		nxtSym();
		return pow(ret, cur.val1);
	}
	return (Node){cur.val, cur.pw};
}
Node expression()
{
	Node ret = term();
	while(typ == 1)
	{
		nxtSym();
		ret = merge(ret, term());
	}
	return ret;
}
int main()
{
	scanf("%s", str);
	nxtSym();
	Node ret = expression();
	printf("%d\n", ret.first);
	return 0;
}
