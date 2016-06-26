#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 31623;
std::pair<int, int> a[maxn];
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
int mod_inv(int x, int p)
{
	return x <= 1 ? x : p - p / x * (LL)mod_inv(p % x, p) % p;
}
int bsgs(int x, int v, int p)
{
	int size = (int)ceil(sqrt(p + 0.1));
	for(int i = 0; i < size; ++i)
		a[i] = std::make_pair(i ? (LL)a[i - 1].first * x % p : 1, i);
	std::sort(a, a + size);
	for(int i = 0, w = v, ww = mod_pow(x, p - size - 1, p); i * size < p; ++i, w = (LL)w * ww % p)
	{
		std::pair<int, int> tmp = *std::lower_bound(a, a + size, std::make_pair(w, 0));
		if(tmp.first == w)
			return i * size + tmp.second;
	}
	return -2;
}
int main()
{
	int t, mod, a, b, x, m;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d%d", &mod, &a, &b, &x, &m);
		if(!a)
			puts(x == m ? "1" : (b == m ? "2" : "-1"));
		else if(a == 1)
			if(!b)
				puts(x == m ? "1" : "-1");
			else
			{
				int tmp = (LL)(m - x) * mod_inv(b, mod) % mod;
				if(tmp < 0)
					tmp += mod;
				printf("%d\n", tmp + 1);
			}
		else
		{
			int tmp = (LL)b * mod_inv(a - 1, mod) % mod, t1 = x + tmp;
			if(t1 >= mod)
				t1 -= mod;
			if(t1 % mod == 0)
				puts(x == m ? "1" : "-1");
			else
				printf("%d\n", bsgs(a, (LL)(m + tmp) * mod_inv(t1, mod) % mod, mod) + 1);
		}
	}
	return 0;
}
