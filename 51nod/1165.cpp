#include <stdio.h>
#include <algorithm>
const int maxn = 10000000;
int f[maxn + 1], t, n;
int main()
{
	for(int i = 1; i <= maxn; i += 2)
		for(int j = 1, lim = std::min(maxn / i - i, i - 1), val = i * (i + 1); j <= lim; j += 2, val += i << 1)
			if(std::__gcd(i, j) == 1)
				++f[val];
	for(int i = maxn; i; --i)
		if(f[i])
			for(int j = i + i; j <= maxn; j += i)
				f[j] += f[i];
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}
