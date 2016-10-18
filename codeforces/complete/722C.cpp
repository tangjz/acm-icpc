#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100010;
int n, a[maxn], p[maxn], dsu[maxn];
LL L[maxn], R[maxn], C[maxn], sum, ans[maxn];
bool vis[maxn];
int find(int x)
{
	return dsu[x] < 0 ? x : dsu[x] = find(dsu[x]);
}
void merge(int u, int v)
{
	if(dsu[u] < dsu[v])
		dsu[v] = u;
	else if(dsu[u] > dsu[v])
		dsu[u] = v;
	else
	{
		dsu[v] = u;
		--dsu[u];
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", p + i);
	memset(dsu, -1, sizeof dsu);
	for(int i = n; i >= 1; --i)
	{
		LL pL = a[p[i]], pR = a[p[i]], pC = a[p[i]];
		vis[p[i]] = 1;
		if(vis[p[i] - 1])
		{
			int u = find(p[i] - 1);
			pL = max(L[u], C[u] + pL);
			pR = max(pR, pC + R[u]);
			pC += C[u];
			merge(u, find(p[i]));
		}
		if(vis[p[i] + 1])
		{
			int u = find(p[i] + 1);
			pL = max(pL, pC + L[u]);
			pR = max(R[u], C[u] + pR);
			pC += C[u];
			merge(u, find(p[i]));
		}
		int u = find(p[i]);
		L[u] = pL;
		R[u] = pR;
		C[u] = pC;
		sum = max(sum, max(max(pL,  pR), pC));
		ans[i - 1] = sum;
	}
	for(int i = 1; i <= n; ++i)
		printf("%I64d\n", ans[i]);
	return 0;
}
