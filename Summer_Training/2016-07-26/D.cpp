#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL p = 10000000000000LL;
LL mod_add(LL x, LL y)
{
	x += y;
	if(x >= p)
		x -= p;
	return x;
}
LL mod_sub(LL x, LL y)
{
	x -= y;
	if(x < 0)
		x += p;
	return x;
}
const int delen = 19, delta = 1 << delen, deltb = delta - 1;
LL mod_mul(LL x, LL y)
{
	LL ret = 0;
	if(x < y)
		swap(x, y);
	while(y)
	{
		if(y & deltb)
			ret = mod_add(ret, x * (y & deltb) % p);
		x = x * delta % p;
		y >>= delen;
	}
	return ret;
}
struct Fibonacci
{
	LL num1, num2;
	bool operator == (const Fibonacci &x) const
	{
		return num1 == x.num1 && num2 == x.num2;
	}
	Fibonacci operator * (const Fibonacci &x) const
	{
		return (Fibonacci){mod_add(mod_mul(num1, x.num1), mod_mul(num2, x.num2)),
		mod_add(mod_mul(num1, x.num2), mod_mul(num2, mod_add(x.num1, x.num2)))};
	}
	Fibonacci pow(LL k)
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
} A = {0, 1}, I = {1, 0};
const int maxs = 2001;
int L, R;
LL n, que[maxs];
int main()
{
	scanf("%I64d", &n);
	que[R++] = 0;
	for(LL md = 10, sd = 1; md <= p; md *= 10)
	{
		int RR = R, sz = md <= 10 ? 60 : md <= 1000 ? 5 : 10;
		while(L != R)
		{
			LL now = que[L++];
			if(L == maxs)
				L = 0;
			for(int i = 0; i < sz; ++i, now += sd)
				if((n - A.pow(now).num2) % md == 0)
				{
					que[RR++] = now;
					if(RR == maxs)
						RR = 0;
				}
		}
		R = RR;
		sd *= sz;
	}
	if(L == R)
		puts("-1");
	else
	{
		LL ans = que[L];
		while(L != R)
		{
			if(ans > que[L])
				ans = que[L];
			if(++L == maxs)
				L = 0;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
