#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long LL;
const int maxn = 100000, maxd = 100, maxt = 1;
int n, d, mod, a[maxn][maxd], b[maxn], c[maxn], e[maxn], f[maxn];
inline void scan(int &x)
{
	register int ch;
	while((ch = getchar()) < '0' || ch > '9');
	for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch - '0'));
}
int main()
{
	int p = -1, q = -1;
	scan(n), scan(d), scan(mod);
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < d; ++j)
		{
			scan(a[i][j]);
			a[i][j] %= mod;
			b[i] += a[i][j] * a[i][j];
		}
		b[i] = ((mod & 1 ? (LL)b[i] * b[i] : b[i]) + n - 1) % mod;
	}
	if((LL)n * n * d <= (LL)1e8)
	{
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
			{
				int val = 0;
				for(int k = 0; k < d; ++k)
					val += a[i][k] * a[j][k];
				if(val % mod == 0)
				{
					p = i + 1;
					q = j + 1;
					break;
				 }
			}
		printf("%d %d\n", p, q);
		return 0;
	}
	//srand(time(NULL));
	for(int t = 0; t < maxt; ++t)
	{
		for(int i = 0; i < n; ++i)
			c[i] = 1; //rand() % mod;
		if(mod & 1) // mod = 3
		{
			int len = d * d;
			memset(e, 0, len * sizeof(int));
			for(int i = 0; i < n; ++i)
				for(int j = 0, k = 0, o = 0; j < d; ++o, (k == d - 1 ? (++j, k = 0) : ++k))
					e[o] += c[i] * a[i][j] * a[i][k];
			for(int i = 0; i < len; ++i)
				e[i] %= mod;
			memset(f, 0, n * sizeof(int));
			for(int i = 0; i < n; ++i)
				for(int j = 0, k = 0, o = 0; j < d; ++o, (k == d - 1 ? (++j, k = 0) : ++k))
					f[i] += e[o] * a[i][j] * a[i][k];
			for(int i = 0; i < n; ++i)
				if((f[i] - b[i] * c[i]) % mod)
				{
					for(int j = 0; j < n; ++j)
					{
						if(i == j)
							continue;
						int val = 0;
						for(int k = 0; k < d; ++k)
							val += a[i][k] * a[j][k];
						if(val % mod == 0)
						{
							p = i + 1;
							q = j + 1;
							break;
						}
					}
					if(p != -1)
						break;
				}
		}
		else // mod = 2
		{
			memset(e, 0, d * sizeof(int));
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < d; ++j)
					e[j] ^= c[i] & a[i][j];
			memset(f, 0, n * sizeof(int));
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < d; ++j)
					f[i] ^= e[j] & a[i][j];
			for(int i = 0; i < n; ++i)
				if(f[i] != (b[i] & c[i]))
				{
					for(int j = 0; j < n; ++j)
					{
						if(i == j)
							continue;
						int val = 0;
						for(int k = 0; k < d; ++k)
							val ^= a[i][k] & a[j][k];
						if(!val)
						{
							p = i + 1;
							q = j + 1;
							break;
						}
					}
					if(p != -1)
						break;
				}
		}
		if(p != -1)
			break;
	}
	if(p > q)
	{
		int t = p;
		p = q;
		q = t;
	}
	printf("%d %d\n", p, q);
	return 0;
}
