#include <cstdio>
const int maxn = 3000001;
int n, m, a[maxn], que[2][maxn], L[2], R[2], ans;
int main()
{
	scanf("%d%d", &m, &n);
	for(int i = 0, j = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		while(L[0] < R[0] && a[que[0][R[0] - 1]] < a[i])
			--R[0];
		que[0][R[0]++] = i;
		while(L[1] < R[1] && a[que[1][R[1] - 1]] > a[i])
			--R[1];
		que[1][R[1]++] = i;
		for( ; j <= i && a[que[0][L[0]]] - a[que[1][L[1]]] > m; ++j)
		{
			if(j == que[0][L[0]])
				++L[0];
			if(j == que[1][L[1]])
				++L[1];
		}
		if(ans < i - j + 1)
			ans = i - j + 1;
	}
	printf("%d\n", ans);
	return 0;
}
