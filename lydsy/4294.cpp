#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL p;
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
LL mod_mul(LL x, LL y)
{
	LL ret = 0;
	if(x < y)
		swap(x, y);
	while(y)
	{
		if(y & 1)
			ret = mod_add(ret, x);
		x = mod_add(x, x);
		y >>= 1;
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
const int maxn = 20, maxs = 2001;
int L, R;
LL n, que[maxs];
char str[maxn];
int main()
{
	scanf("%s", &str);
	p = 1;
	for(int i = 0; str[i]; ++i, p *= 10)
		n = (n << 3) + (n << 1) + (str[i] - '0');
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
		if(md > p / 10)
			break;
	}
	if(L == R)
		puts("NIE");
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
		printf("%lld\n", ans + p * 6);
	}
	return 0;
}
