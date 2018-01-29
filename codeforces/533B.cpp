#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 200001;
const long long INF = (long long)1e11;
int n, p[maxn], a[maxn];
vector<int> e[maxn];
long long f[maxn][2];
void dfs(int u)
{
	f[u][0] = 0;
	f[u][1] = -INF;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int &v = *it;
		dfs(v);
		long long tmp1 = max(f[u][0] + f[v][0], f[u][1] + f[v][1]), tmp2 = max(f[u][0] + f[v][1], f[u][1] + f[v][0]);
		f[u][0] = tmp1;
		f[u][1] = tmp2;
	}
	f[u][1] = max(f[u][1], f[u][0] + a[u]);
}
int main()
{
	scanf("%d", &n);
	++n;
	for(int i = 1; i < n; ++i)
	{
		scanf("%d%d", p + i, a + i);
		if(p[i] == -1)
			++p[i];
		e[p[i]].push_back(i);
	}
	dfs(0);
	printf("%I64d\n", f[0][1]);
	return 0;
}
