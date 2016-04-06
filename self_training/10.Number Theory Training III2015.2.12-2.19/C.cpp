#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxs = 150, mod = 10000, maxn = 10001, maxa = 200001;
struct BigInt
{
	int len, num[maxs];
	void read(int x)
	{
		for(int i = 0; i < len; ++i)
			num[i] = 0;
		for(len = 0; x; ++len, x /= mod)
			num[len] = x % mod;
		if(!len)
			++len;
	}
	void write()
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%4.4d", num[i]);
		putchar('\n');
	}
	BigInt operator * (const int &x) const
	{
		BigInt tmp = *this;
		for(int i = 0; i < len; ++i)
			tmp.num[i] *= x;
		for(int i = 0; i < len; ++i)
		{
			tmp.num[i + 1] += tmp.num[i] / mod;
			tmp.num[i] %= mod;
		}
		for( ; tmp.num[tmp.len]; ++tmp.len)
		{
			tmp.num[tmp.len + 1] = tmp.num[tmp.len] / mod;
			tmp.num[tmp.len] %= mod;
		}
		return tmp;
	}
	BigInt operator *= (const int &x)
	{
		return *this = *this * x;
	}
} Ans;
int n, k, tot, prime[maxa], vis[maxa], ptot, pnum[maxa];
int main()
{
	for(int i = 2; i < maxa; ++i)
	{
		if(!vis[i])
		{
			vis[i] = i;
			prime[tot++] = i;
		}
		for(int j = 0; j < tot && prime[j] < maxa / i; ++j)
		{
			vis[i * prime[j]] = prime[j];
			if(i % prime[j] == 0)
				break;
			if(i == vis[i])
				pnum[ptot++] = i * prime[j];
		}
	}
	sort(pnum, pnum + ptot);
	while(scanf("%d%d", &n, &k) == 2)
		if(k == 1)
			puts("1");
		else if(k == vis[k])
		{
			Ans.read(prime[--n]);
			for(int i = 2; i < k; ++i)
				Ans *= prime[n];
			Ans.write();
		}
		else
		{
			int kk = vis[k], num, pow;
			for(int i = 0, j = 0, cnt = 0; cnt < n; ++cnt)
				if((k - 1) * log(prime[i]) < (kk - 1) * log(pnum[j]))
				{
					pow = k - 1;
					num = prime[i++];
				}
				else
				{
					pow = kk - 1;
					num = pnum[j++];
				}
			Ans.read(num);
			for(int i = 1; i < pow; ++i)
				Ans *= num;
			Ans.write();
		}
	return 0;
}
