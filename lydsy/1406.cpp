#include <cstdio>
#include <algorithm>
using namespace std;
const int maxs = 9, maxm = 1 << 10;
int n, cnt, pp[maxs], sum, ans[maxm];
void exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
pair<int, int> merge(pair<int, int> t1, pair<int, int> t2)
{
	int &r1 = t1.first, &m1 = t1.second, &r2 = t2.first, &m2 = t2.second;
	int x, y, r, m = m1 * m2;
	exgcd(m1, m2, x, y); //(m1, m2) = 1
	x = (long long)x * (r2 - r1) % m2;
	if(x < 0)
		x += m2;
	r = x * m1 + r1;
	return make_pair(r, m);
}
void dfs(int dep, pair<int, int> t)
{
	if(dep == cnt)
	{
		ans[sum++] = t.first;
		return;
	}
	dfs(dep + 1, merge(t, make_pair(1, pp[dep])));
	if(pp[dep] != 2)
		dfs(dep + 1, merge(t, make_pair(pp[dep] - 1, pp[dep])));
	if(!(pp[dep] & 1) && pp[dep] > 4)
	{
		dfs(dep + 1, merge(t, make_pair((pp[dep] >> 1) + 1, pp[dep])));
		dfs(dep + 1, merge(t, make_pair((pp[dep] >> 1) - 1, pp[dep])));
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 2; i <= n / i; ++i)
		if(n % i == 0)
		{
			pp[cnt] = 1;
			for( ; n % i == 0; n /= i)
				pp[cnt] *= i;
			++cnt;
		}
	if(n > 1)
		pp[cnt++] = n;
	dfs(0, make_pair(0, 1));
	if(!sum)
		puts("None");
	else
	{
		sort(ans, ans + sum);
		for(int i = 0; i < sum; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
