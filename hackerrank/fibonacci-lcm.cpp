#include <map>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 101, mod = 1000000007;
struct Fibonacci
{
	int num1, num2;
	bool operator == (const Fibonacci &x) const
	{
		return num1 == x.num1 && num2 == x.num2;
	}
	Fibonacci operator * (const Fibonacci &x) const
	{
		return (Fibonacci){((LL)num1 * x.num1 + (LL)num2 * x.num2) % mod,
		((LL)num1 * x.num2 + (LL)num2 * (x.num1 + x.num2)) % mod};
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
int Fib(int x)
{
	return A.pow(x).num2;
}
int n, a[maxn];
int inv(int x)
{
	return x <= 1 ? x : mod - (LL)mod / x * inv(mod % x) % mod;
}
map<pair<int, int>, int> Hash;
int dfs(int g, int i)
{
	pair<int, int> idx = make_pair(g, i);
	if(Hash.count(idx))
		return Hash[idx];
	if(!i)
		return Hash[idx] = 1;
	int r = __gcd(g, a[i - 1]);
	if(g == r)
		return Hash[idx] = Fib(r);
	return Hash[idx] = (LL)Fib(r) * dfs(g, i - 1) % mod * inv(dfs(r, i - 1)) % mod;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	n = unique(a, a + n) - a;
	printf("%d\n", dfs(0, n));
	return 0;
}
