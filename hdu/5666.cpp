#include <cstdio>
typedef long long LL;
LL mod_mul(LL x, LL y, LL p)
{
	x %= p;
	y %= p;
	LL ret = 0;
	while(y)
	{
		if(y & 1)
			ret = (ret + x) % p;
		x = (x + x) % p;
		y >>= 1;
	}
	return ret;
}
int main()
{
	int t;
	LL p, q, r;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%I64d%I64d", &q, &p);
		r = q - 2;
		--q;
		if(r & 1)
			q >>= 1;
		else
			r >>= 1;
		printf("%I64d\n", mod_mul(q, r, p));
	}
	return 0;
}
