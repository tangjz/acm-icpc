#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> point;
int solve(set<point> &x, set<point> &y)
{
	if(x.size() == 1)
		return 1;
	set<point> xx, yy;
	set<point>::iterator x1 = x.begin(), y1 = y.begin();
	set<point>::reverse_iterator x2 = x.rbegin(), y2 = y.rbegin();
	do
	{
		int tmp;
		tmp = x1 -> first;
		if((++x1) -> first - tmp > 1)
		{
			for(point it = *x.begin(); it.first <= tmp; it = *x.begin())
			{
				point jt = make_pair(it.second, it.first);
				x.erase(it);
				xx.insert(it);
				y.erase(jt);
				yy.insert(jt);
			}
			return solve(x, y) + solve(xx, yy);
		}
		tmp = x2 -> first;
		if(tmp - (++x2) -> first > 1)
		{
			for(point it = *x.rbegin(); it.first >= tmp; it = *x.rbegin())
			{
				point jt = make_pair(it.second, it.first);
				x.erase(it);
				xx.insert(it);
				y.erase(jt);
				yy.insert(jt);
			}
			return solve(x, y) + solve(xx, yy);
		}
		tmp = y1 -> first;
		if((++y1) -> first - tmp > 1)
		{
			for(point it = *y.begin(); it.first <= tmp; it = *y.begin())
			{
				point jt = make_pair(it.second, it.first);
				y.erase(it);
				yy.insert(it);
				x.erase(jt);
				xx.insert(jt);
			}
			return solve(x, y) + solve(xx, yy);
		}
		tmp = y2 -> first;
		if(tmp - (++y2) -> first > 1)
		{
			for(point it = *y.rbegin(); it.first >= tmp; it = *y.rbegin())
			{
				point jt = make_pair(it.second, it.first);
				y.erase(it);
				yy.insert(it);
				x.erase(jt);
				xx.insert(jt);
			}
			return solve(x, y) + solve(xx, yy);
		}
	} while(*x1 < *x2);
	return 1;
}
int main()
{
	int n, x, y;
	set<point> xx, yy;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d%d", &x, &y);
		xx.insert(make_pair(x, y));
		yy.insert(make_pair(y, x));
	}
	printf("%d\n", solve(xx, yy));
	return 0;
}
