#include <set>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 201;
int n, m, q, mat[maxn][maxn], ans;
set<int> s;
int main()
{
	while(scanf("%d%d%d", &n, &m, &q) == 3)
	{
		ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				scanf("%d", mat[i] + j);
				mat[i][j] = (mat[i][j - 1] + mat[i][j]) % q;
				if(mat[i][j] < 0)
					mat[i][j] += q;
			}
		for(int i = 0; i <= m; ++i)
			for(int j = i + 1; j <= m; ++j)
			{
				s.clear();
				for(int k = 1, last = 0, now; k <= n; ++k)
				{
					s.insert(last);
					now = last + mat[k][j] - mat[k][i];
					if(now >= q)
						now -= q;
					else if(now < 0)
						now += q;
					set<int>::iterator it = s.upper_bound(now);
					if(it != s.end())
						last = now - *it;
					else
						last = now - *s.begin();
					if(last < 0)
						last += q;
					if(ans < last)
						ans = last;
					last = now;
				}
			}
		printf("%d\n", ans);
	}
	return 0;
}
