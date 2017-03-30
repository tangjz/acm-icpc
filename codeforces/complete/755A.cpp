#include <cstdio>
const int maxn = 1000003;
int tot, pr[maxn], d[maxn];
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= 1000; ++i)
	{
		int val = i * n + 1;
		if(d[val] != val)
		{
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}
