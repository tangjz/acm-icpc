#include <cstdio>
#include <cstring>
const int maxn = 1000003;
int n, z[maxn], pL[maxn], pR[maxn], lnk[maxn];
char str[maxn];
long long ans;
struct Edge {
	int nxt, v;
} e[maxn];
int main()
{
	scanf("%s", str);
	n = strlen(str);
	memset(lnk, -1, (n + 1) * sizeof(int));
	int S = n, T = n + 1;
	pR[S] = T;
	pL[T] = S;
	for(int i = 0, L = 0, R = 1, mx = 0; i < n; ++i)
	{
		if(z[i - L] < R - i)
			z[i] = z[i - L];
		else
		{
			int x = i < R ? R : i;
			for( ; str[x] == str[x - i]; ++x);
			z[i] = x - i;
			if(i < x)
			{
				L = i;
				R = x;
			}
		}
		for(int it = lnk[i]; it != -1; it = e[it].nxt)
		{
			int id = e[it].v;
			pL[pR[id]] = pL[id];
			pR[pL[id]] = pR[id];
		}
		int len = mx < z[i] ? mx : z[i];
		if(len > 0)
		{
			pL[i] = pL[T];
			pR[i] = T;
			pR[pL[i]] = i;
			pL[pR[i]] = i;
			e[i] = (Edge){lnk[i + len], i};
			lnk[i + len] = i;
		}
		if(pR[S] != T)
			ans += i - pR[S] + 1;
		if(mx < z[i])
			mx = z[i];
	}
	printf("%lld\n", ans);
	return 0;
}
