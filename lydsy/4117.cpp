#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 21;
int n;
long long fact[maxn];
double p[4][maxn], ans;
priority_queue<pair<double, long long>, vector<pair<double, long long> >, greater<pair<double, long long> > > Q;
int main()
{
	fact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		fact[i] = fact[i - 1] * i;
	while(scanf("%d", &n) == 1)
	{
		ans = 0;
		for(int i = 0; i < 4; ++i)
		{
			double pp;
			scanf("%lf", &pp);
			p[i][0] = 1;
			for(int j = 1; j <= n; ++j)
				p[i][j] = p[i][j - 1] * pp;
		}
		while(!Q.empty())
			Q.pop();
		for(int i = 0; i <= n; ++i)
			for(int j = i; j <= n; ++j)
				for(int k = j; k <= n; ++k)
					Q.push(make_pair(p[0][i] * p[1][j - i] * p[2][k - j] * p[3][n - k], -fact[n] / fact[i] / fact[j - i] / fact[k - j] / fact[n - k]));
		while(!Q.empty())
		{
			pair<double, long long> tmp1 = Q.top(), tmp2;
			Q.pop();
			if(-tmp1.second > 1)
			{
				if((-tmp1.second) & 1)
				{
					Q.push(make_pair(tmp1.first, -1LL));
					++tmp1.second;
				}
				ans += tmp1.first * -tmp1.second;
				Q.push(make_pair(tmp1.first * 2, tmp1.second >> 1));
			}
			else if(!Q.empty())
			{
				tmp2 = Q.top();
				Q.pop();
				ans += tmp1.first + tmp2.first;
				Q.push(make_pair(tmp1.first + tmp2.first, -1LL));
				if(-tmp2.second > 1)
					Q.push(make_pair(tmp2.first, ++tmp2.second));
			}
		}
		printf("%.6f\n", (double)ans);
	}
	return 0;
}
