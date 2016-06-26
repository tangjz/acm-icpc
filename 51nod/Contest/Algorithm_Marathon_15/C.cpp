#include <vector>
#include <cstdio>
const int maxn = 100001, maxm = 10001;
int n, q, a[maxn], f[maxn], mu[maxn];
std::vector<int> fact[maxn];
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	mu[1] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i].push_back(i);
		f[i] += a[i];
		for(int j = i + i; j <= n; j += i)
		{
			mu[j] -= mu[i];
			fact[j].push_back(i);
			f[i] += a[j];
		}
	}
	while(q--)
	{
		int typ, idx, val;
		scanf("%d%d", &typ, &idx);
		if(typ == 1)
		{
			scanf("%d", &val);
			for(auto k : fact[idx])
				f[k] += val - a[idx];
			a[idx] = val;
		}
		else
		{
			val = 0;
			for(auto k : fact[idx])
				val += mu[k] * f[k];
			printf("%d\n", val);
		}
	}
	return 0;
}
