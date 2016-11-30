#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> point;
map<point, int> Hash;
int t, n, minx, maxx, xx;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		Hash.clear();
		minx = ~0u >> 1, maxx = -minx;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			++Hash[make_pair(x <<= 1, y <<= 1)];
			if(x < minx)
				minx = x;
			if(maxx < x)
				maxx = x;
		}
		xx = minx + maxx;
		bool flag = 0;
		for(map<point, int>::iterator it = Hash.begin(), jt = Hash.end(); it != jt; ++it)
		{
			point tmp = it -> first;
			tmp.first = xx - tmp.first;
			if(Hash.find(tmp) == jt || Hash[tmp] != it -> second)
			{
				flag = 1;
				break;
			}
		}
		puts(flag ? "NO" : "YES");
	}
	return 0;
}
