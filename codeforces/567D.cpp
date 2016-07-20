#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200010;
int n, k, a, m, x[maxn], id[maxn], L[maxn], R[maxn], sum;
bool cmp(const int &p, const int &q)
{
	return x[p] < x[q];
}
int main()
{
	scanf("%d%d%d%d", &n, &k, &a, &m);
	for(int i = 0; i < m; ++i)
		scanf("%d", x + i), id[i] = i;
	sort(id, id + m, cmp);
	for(int i = 0; i < m; ++i)
	{
		if(i > 0)
			L[x[id[i]]] = x[id[i - 1]];
		else
			L[x[id[i]]] = 0;
		if(i < m - 1)
			R[x[id[i]]] = x[id[i + 1]];
		else
			R[x[id[i]]] = n + 1;
		if(!i)
			sum += (x[id[i]] - L[x[id[i]]]) / (a + 1);
		sum += (R[x[id[i]]] - x[id[i]]) / (a + 1);
	}
	if(sum >= k)
	{
		puts("-1");
		return 0;
	}
	for(int i = m - 1; i >= 0; --i)
	{
		int &lx = L[x[i]], &rx = R[x[i]];
		R[lx] = rx;
		L[rx] = lx;
		sum -= (rx - x[i]) / (a + 1);
		sum -= (x[i] - lx) / (a + 1);
		sum += (rx - lx) / (a + 1);
		if(sum >= k)
		{
			printf("%d\n", i + 1);
			break;
		}
	}
	return 0;
}

