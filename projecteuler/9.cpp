#include <stdio.h>
#include <cstring>
const int maxn = 3001, maxm = maxn * maxn;
int f[maxn], Sqrt[maxm];
int main()
{
	memset(f, -1, sizeof f);
	for(int i = 1; i < maxn; ++i)
		Sqrt[i * i] = i;
	for(int i = 1; i < maxn; ++i)
		for(int j = i + 1; i + j < maxn; ++j)
		{
			int k = Sqrt[i * i + j * j];
			if(k && i + j + k < maxn)
			{
				int sum = i + j + k, prod = i * j * k;
				if(f[sum] < prod)
					f[sum] = prod;
			}
		}
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}
