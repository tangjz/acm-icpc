#include <cstdio>
typedef long long LL;
const int maxm = 25, prime[] = {
1000000007, 23333, 712442999, 369729667, 105231211,
24185591, 999690431, 767158789, 681101261, 305973581,
468220243, 117651889, 39421399, 9730333, 9478123,
9046913, 8706853, 8024843, 6826507, 5250107,
4609309, 3596357, 2329241, 1441553, 444803
};
int t, n, a[6], tot, d1[233], d2[233], ans[6][2];
int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
int inv(int x, int mod)
{
	int ret = 1, k = mod - 2;
	while(k)
	{
		if(k & 1)
			ret = ret * (LL)x % mod;
		x = x * (LL)x % mod;
		k >>= 1;
	}
	return ret;
}
bool calc(int p, int q, int mod)
{
	int x = (LL)(p + mod) * inv(q, mod) % mod, t = 1, sum = 0;
	for(int i = 0; i <= n; ++i)
	{
		sum = ((LL)(a[i] % mod + mod) * t + sum) % mod + mod;
		if(sum >= mod)
			sum -= mod;
		t = t * (LL)x % mod;
	}
	return !sum;
}
void solve(int i, int j)
{
	int flag = 0;
	for(int k = 0; k < maxm; ++k)
		if(!calc(i, j, prime[k]))
		{
			flag = 1;
			break;
		}
	if(!flag)
	{
		ans[tot][0] = i;
		ans[tot][1] = j;
		++tot;
	}
}
template<class T> T abs(const T& x)
{
	return x < 0 ? -x : x;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i <= n; ++i)
			scanf("%d", a + i);
		tot = d1[0] = d2[0] = 0;
		if(!a[0])
		{
			ans[tot][0] = 0;
			ans[tot][1] = 1;
			++tot;
			for(int i = 0; i <= n; ++i)
				if(a[i])
				{
					for(int j = 0; j + i <= n; ++j)
						a[j] = a[j + i];
					n -= i;
					break;
				}
		}
		int p = abs(a[0]), q = n ? abs(a[n]) : 0;
		for(int i = 1; i * i <= p; ++i)
			if(p % i == 0)
			{
				d1[++d1[0]] = i;
				if(i * i < p)
					d1[++d1[0]] = p / i;
			}
		for(int i = 1; i * i <= q; ++i)
			if(q % i == 0)
			{
				d2[++d2[0]] = i;
				if(i * i < q)
					d2[++d2[0]] = q / i;
			}
		for(int i = 1; i <= d1[0]; ++i)
			for(int j = 1; j <= d2[0]; ++j)
				if(gcd(d1[i], d2[j]) == 1)
				{
					solve(d1[i], d2[j]);
					solve(-d1[i], d2[j]);
				}
		for(int i = 0; i < tot; ++i)
		{
			int k = i;
			for(int j = i + 1; j < tot; ++j)
				if(ans[k][0] * ans[j][1] > ans[k][1] * ans[j][0])
					k = j;
			if(k != i)
			{
				int tmp;
				tmp = ans[i][0];
				ans[i][0] = ans[k][0];
				ans[k][0] = tmp;
				tmp = ans[i][1];
				ans[i][1] = ans[k][1];
				ans[k][1] = tmp;
			}
		}
		printf("%d\n", tot);
		for(int i = 0; i < tot; ++i)
			printf("%d/%d\n", ans[i][0], ans[i][1]);
		puts("");
	}
	return 0;
}
