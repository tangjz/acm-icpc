#include <cstdio>
const int maxn = 21;
int n, r[maxn], cnt, res;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", r + i);
		cnt += r[i];
	}
	if(cnt & 1)
	{
		puts("0");
		return 0;
	}
	for(int i = 0, j = 0, tot = 0; i < n - 1; ++i)
	{
		tot += r[i];
		while(tot > cnt >> 1)
			tot -= r[j++];
		if(tot == cnt >> 1)
			++res;
	}
	printf("%d\n", res * (res - 1) >> 1);
	return 0;
}
