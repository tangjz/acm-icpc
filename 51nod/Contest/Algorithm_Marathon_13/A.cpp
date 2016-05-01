#include <set>
#include <stdio.h>
const int maxn = 100001;
int n, p, s[3][maxn], ans;
std::set<int> e;
int main()
{
	scanf("%d%d", &n, &p);
	for(int i = 0; i < 3; ++i)
		for(int j = 1; j <= n; ++j)
		{
			scanf("%d", s[i] + j);
			s[i][j] += s[i][j - 1];
			if(s[i][j] >= p)
				s[i][j] -= p;
		}
	for(int i = 1; i <= n; ++i)
	{
		int val = s[0][i] - s[1][i - 1];
		if(val < 0)
			val += p;
		e.insert(val);
		val = s[1][i] + s[2][n] - s[2][i - 1];
		if(val < 0)
			val += p;
		else if(val >= p)
			val -= p;
		int tmp = val + *(--e.end());
		if(tmp >= p)
			tmp -= p;
		if(ans < tmp)
			ans = tmp;
		std::set<int>::iterator it = e.lower_bound(p - val);
		if(it != e.begin())
		{
			tmp = val + *(--it);
			if(ans < tmp)
				ans = tmp;
		}
	}
	printf("%d\n", ans);
	return 0;
}
