#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 301, maxm = 44851;
int n, m, a[maxm], b[maxn], tot, ans[maxn][maxn];
int main()
{
	scanf("%d", &n);
	m = n * (n - 1) >> 1;
	for(int i = 0; i < m; ++i)
		scanf("%d", a + i);
	sort(a, a + m);
	for(int i = 2; i < n; ++i)
	{
		if(i > 2 && a[i - 1] == a[i])
			continue;
		if((a[0] + a[1] + a[i]) & 1)
			continue;
		int sum = a[0] + a[1] + a[i] >> 1;
		b[0] = sum - a[i];
		b[1] = sum - a[1];
		b[2] = sum - a[0];
		if(b[0] <= 0 || b[1] <= 0 || b[2] <= 0)
			continue;
		multiset<int> Q;
		Q.clear();
		for(int j = 2; j < m; ++j)
			if(i != j)
				Q.insert(a[j]);
		bool flag = 0;
		for(int j = 3; j < n && !flag; ++j)
		{
			b[j] = *Q.begin() - b[0];
			if(b[j] <= 0)
				flag = 1;
			for(int k = 0; k < j && !flag; ++k)
				if(!Q.count(b[k] + b[j]))
					flag = 1;
				else
					Q.erase(Q.find(b[k] + b[j]));
		}
		if(flag)
			continue;
		for(int j = 0; j < n; ++j)
			ans[tot][j] = b[j];
		++tot;
	}
	printf("%d\n", tot);
	for(int i = 0; i < tot; ++i, puts(""))
		for(int j = 0; j < n; ++j)
			printf("%d ", ans[i][j]);
	return 0;
}
