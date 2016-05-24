#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 8005;
int n, a[maxn], ord[maxn], que[maxn], pos[maxn], L[maxn], R[maxn], ans[maxn];
bool cmp(const int &x, const int &y)
{
	return a[x] < a[y];
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			ord[i] = i;
		}
		sort(ord + 1, ord + n + 1, cmp);
		memset(ans + 1, 0, n * sizeof(int));
		for(int i = 1; i <= n; ++i)
		{
			int sz = 0;
			for(int j = 1; j <= n; ++j)
				if(ord[j] >= i)
				{
					que[++sz] = ord[j];
					pos[ord[j]] = sz;
				}
			R[0] = 0;
			for(int j = 1; j <= sz; ++j)
			{
				L[j] = j - 1;
				R[j] = j + 1;
			}
			L[sz + 1] = sz;
			for(int j = n, mid = sz + 1 >> 1, rk = mid; j >= i; --j, --sz)
			{
				if(rk < (sz + 1 >> 1))
				{
					++rk;
					mid = R[mid];
				}
				else if(rk > (sz + 1 >> 1))
				{
					--rk;
					mid = L[mid];
				}
				if(sz & 1)
					++ans[que[mid]];
				if(pos[j] == mid)
				{
					--rk;
					mid = L[mid];
				}
				else if(pos[j] < mid)
					--rk;
				R[L[pos[j]]] = R[pos[j]];
				L[R[pos[j]]] = L[pos[j]];
			}
		}
		for(int i = 1; i <= n; ++i)
			printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
