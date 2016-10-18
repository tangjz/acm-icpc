#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 500001;
int n, r;
LL a[maxn], s;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		LL x, y;
		scanf("%I64d%I64d", &x, &y);
		a[i] = x ^ y;
		s ^= x;
	}
	for(int i = 0; i < 60; ++i)
	{
		int k = -1;
		for(int j = r; j < n; ++j)
			if((a[j] >> i) & 1)
			{
				k = j;
				break;
			}
		if(k == -1)
			continue;
		std::swap(a[r], a[k]);
		for(int j = 0; j < n; ++j)
			if(j != r && ((a[j] >> i) & 1))
				a[j] ^= a[r];
		++r;
	}
	for(int i = 0; i < r; ++i)
		if(s & (a[i] & -a[i]))
			s ^= a[i];
	if(s)
		puts("1/1");
	else
		printf("%I64d/%I64d\n", (1LL << r) - 1, 1LL << r);
	return 0;
}
