/*
 * 曼哈顿距离最小 中位数
 */
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> Point;
int n, x[10000], y[10000], x1, x2, y1, y2, sum, cnt;
Point p[10000];
set<Point> Hash;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", x + i, y + i);
		p[i] = make_pair(x[i], y[i]);
		Hash.insert(p[i]);
	}
	sort(x, x + n);
	sort(y, y + n);
	if(n & 1)
	{
		x1 = x[n >> 1], y1 = y[n >> 1];
		if(Hash.find(make_pair(x1, y1)) != Hash.end())
		{
			for(int i = 0; i < n; ++i) sum += abs(x1 - x[i]) + abs(y1 - y[i]);
			++sum;
			x1 = x[(n >> 1) - 1], x2 = x[(n >> 1) + 1];
			for(int i = x1; i <= x2; ++i)
				if(Hash.find(make_pair(i, y1)) == Hash.end()) ++cnt;
			y1 = y[(n >> 1) - 1], y2 = y[(n >> 1) + 1];
			for(int i = y1; i <= y2; ++i)
				if(Hash.find(make_pair(x1, i)) == Hash.end()) ++cnt;
		}
		else
		{
			for(int i = 0; i < n; ++i) sum += abs(x1 - x[i]) + abs(y1 - y[i]);
			cnt = 1;
		}
	}
	else
	{
		x1 = x[(n >> 1) - 1], x2 = x[(n >> 1)];
		y1 = y[(n >> 1) - 1], y2 = y[(n >> 1)];
		cnt = (x2 - x1 + 1) * (y2 - y1 + 1);
		for(int i = 0; i < n; ++i) sum += abs(x1 - x[i]) + abs(y1 - y[i]);
		for(int i = 0; i < n; ++i)
			if(p[i].first >= x1 && p[i].first <= x2 && p[i].second >= y1 && p[i].second <= y2) --cnt;
	}
	printf("%d %d\n", sum, cnt);
	return 0;
}
