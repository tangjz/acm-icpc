#include <cmath>
#include <cstdio>
#include <cstring>
const int maxe = 80000, mod = 960991;
int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
int phi(int x)
{
	int ret = x, tmp = x;
	for(int i = 2; i * i <= tmp; ++i)
		if(tmp % i == 0)
		{
			ret -= ret / i;
			while(tmp % i == 0)
				tmp /= i;
		}
	if(tmp > 1)
		ret -= ret / tmp;
	return ret;
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
	if(p == 1)
		return 0;
	tot = 0;
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
	int pphi = phi(p);
	for(int i = 0, tmp = b, delta = pow(a, pphi - size % pphi, p); i < size; ++i)
	{
		for(int it = pre[tmp % mod]; it; it = e[it].nxt)
			if(e[it].num == tmp)
				return i * size + e[it].id;
		tmp = (long long)tmp * delta % p;
	}
	return -1;
}
int main()
{
	int k, p, n, res;
	while(scanf("%d%d%d", &k, &p, &n) != EOF)
	{
		if(n >= p)
		{
			puts("Orz,I can¡¯t find D!");
			continue;
		}
		int x = gcd(k, p), y = gcd(n, p);
		if(x != y && x % y == 0)
			res = -1;
		else
			res = bsgs(k % p, n, p);
		if(res == -1)
			puts("Orz,I can¡¯t find D!");
		else
			printf("%d\n", res);
	}
	return 0;
}
