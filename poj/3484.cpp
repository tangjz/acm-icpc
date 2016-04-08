#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned int LL;
vector<LL> x, y, z;
bool check(LL lim)
{
	LL flag = 0;
	for(int i = 0, j = (int)x.size(); i < j; ++i)
		if(lim >= x[i])
			flag ^= ((min(lim, y[i]) - x[i]) / z[i] + 1) & 1;
	return flag;
}
void solve()
{
	LL l = ~0u, r = 0, m, flag = 0;
	for(int i = 0, j = (int)x.size(); i < j; ++i)
	{
		if(l > x[i])
			l = x[i];
		if(r < y[i])
			r = y[i];
		flag ^= ((y[i] - x[i]) / z[i] + 1) & 1;
	}
	if(!flag)
		puts("no corruption");
	else
	{
		while(l < r)
		{
			m = l + r >> 1;
			if(check(m))
				r = m;
			else
				l = m + 1;
		}
		LL cnt = 0;
		for(int i = 0, j = (int)x.size(); i < j; ++i)
			if(x[i] <= l && l <= y[i] && (l - x[i]) % z[i] == 0)
				++cnt;
		printf("%u %u\n", l, cnt);
	}
	x.clear();
	y.clear();
	z.clear();
}
char str[1024];
int main()
{
	LL a, b, c;
	bool flag = 0;
	while(gets(str) != NULL)
		if(sscanf(str, "%u%u%u", &a, &b, &c) == 3)
		{
			flag = 1;
			if(a > b)
				continue;
			x.push_back(a);
			y.push_back(b);
			z.push_back(c);
		}
		else if(flag)
		{
			solve();
			flag = 0;
		}
	if(flag)
		solve();
	return 0;
}