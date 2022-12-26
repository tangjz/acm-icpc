#include <cmath>
#include <cstdio>
#include <cstring>
const int maxe = 32000, mod = 960991;
int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
void exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= (a / b) * x;
}
int inv(int a, int p)
{
	int x, y;
	exgcd(a, p, x, y);
	if(x < 0)
		x += p;
	return x;
}
int pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % p;
		x = (long long)x * x % p;
		k >>= 1;
	}
	return ret;
}
struct Node
{
	int nxt, num, id;
} e[maxe];
int tot, pre[mod];
int bsgs(int a, int b, int p)
{
	tot = 0;
	memset(e, 0, sizeof e);
	memset(pre, 0, sizeof pre);
	int size = (int)sqrt(p) + 1;
	for(int i = 0, tmp = 1; i < size; ++i)
	{
		bool flag = 0;
		for(int it = pre[tmp % mod]; it; it = e[it].nxt)
			if(e[it].num == tmp)
			{
				flag = 1;
				break;
			}
		if(!flag)
		{
			e[++tot] = (Node){pre[tmp % mod], tmp, i};
			pre[tmp % mod] = tot;
		}
		tmp = (long long)tmp * a % p;
	}
	for(int i = 0, tmp = b, delta = inv(pow(a, size, p), p); i < size; ++i)
	{
		for(int it = pre[tmp % mod]; it; it = e[it].nxt)
			if(e[it].num == tmp)
				return i * size + e[it].id;
		tmp = (long long)tmp * delta % p;
	}
	return -1;
}
int exbsgs(int a, int b, int p)
{
	for(int i = 0, tmp = 1; i < 100; ++i)
	{
		if(tmp == b)
			return i;
		tmp = (long long)tmp * a % p;
	}
	int n = 0, r, d = 1;
	while((r = gcd(a, p)) != 1)
	{
		if(b % r != 0)
			return -1;
		p /= r;
		b /= r;
		d = (long long)d * (a / r) % p;
		++n;
	}
	int ret = bsgs(a, (long long)b * inv(d, p) % p, p);
	if(ret == -1)
		return -1;
	return ret + n;
}
int main()
{
	int x, z, k;
	while(scanf("%d%d%d", &x, &z, &k) != EOF && x + z + k)
	{
		int res = exbsgs(x % z, k % z, z);
		if(res == -1)
			puts("No Solution");
		else
			printf("%d\n", res);
	}
	return 0;
}
