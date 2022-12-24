/*
 * N^2预处理 N^2回答询问
 */
#include <cstdio>
int n, sone[30], sg[30], Hash[20000], ans[3], sum;
bool found;
int main()
{
	int i, j, k, t, SG;
	sg[1] = 0;
	for(i = 2; i <= 25; i++)
	{
		for(j = 1; j < i; ++j)
			for(k = 1; k <= j; ++k) Hash[sg[j]^sg[k]] = i;
		for(j = 0; j <= 10000; ++j) if(Hash[j] != i) break;
		sg[i] = j;
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(i = 1; i <= n; ++i) scanf("%d", &sone[i]);
		SG = 0; sum = 0; found = 0;
		for(i = n; i >= 1; --i) if(sone[i] & 1) SG ^= sg[n - i + 1];
		for(i = 1; i <= n; ++i)
			for(j = i + 1; j <= n; ++j)
				for(k = j; k <= n; ++k)
					if(!(SG ^ sg[n - i + 1] ^ sg[n - j + 1] ^ sg[n - k + 1]))
			  		{
						++sum;
						if(!found) found = 1, ans[0] = i - 1, ans[1] = j - 1, ans[2] = k - 1;
			  		}
		if(found) printf("%d %d %d\n", ans[0], ans[1], ans[2]);
		else printf("-1 -1 -1\n");
		printf("%d\n", sum);
	}
	return 0;
}
