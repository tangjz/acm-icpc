#include <stdio.h>
#include <cstring>
typedef long long LL;
typedef unsigned long long ULL;
const int maxm = 1000003;
int L[maxm + 2], R[maxm + 2];
bool vis[maxm];
int main()
{
	int t, n, m, x, A, B, p, cnt;
	ULL sum, ans;
    scanf("%d", &t);
    while(t--)
	{
		scanf("%d%d%d%d%d%d", &n, &m, &x, &A, &B, &p);
		cnt = 0;
		sum = ans = 0;
		memset(L, -1, (p + 2) * sizeof(int));
		memset(R, -1, (p + 2) * sizeof(int));
		memset(vis, 0, p * sizeof(bool));
		int S = p, T = p + 1;
		R[S] = T;
		L[T] = S;
		for(int i = 1; i <= m; ans += (i++) * sum, x = ((LL)A * x + B) % p)
			if(!vis[x])
			{
				if(cnt == n)
				{
					int y = R[S];
					L[R[y]] = L[y];
					R[L[y]] = R[y];
					--cnt;
					sum -= y;
					vis[y] = 0;
				}
				L[x] = L[T];
				R[x] = T;
				R[L[x]] = x;
				L[R[x]] = x;
				++cnt;
				sum += x;
				vis[x] = 1;
			}
			else if(R[x] != T)
			{
				L[R[x]] = L[x];
				R[L[x]] = R[x];
				L[x] = L[T];
				R[x] = T;
				R[L[x]] = x;
				L[R[x]] = x;
			}
		printf("%llu\n", ans);
	}
	return 0;
}

