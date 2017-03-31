#include <set>
#include <map>
#include <stdio.h>
using namespace std;
typedef pair<int, int> point;
const int maxn = 100001, mod = 1000000009;
int n, x[maxn], y[maxn], ans;
map<point, int> Hash;
set<int> Cube;
bool check(int x, int y)
{
	for(int d1 = -1; d1 <= 1; ++d1)
	{
		if(!Hash.count({x + d1, y + 1}))
			continue;
		int cnt = 0;
		for(int d2 = -1; d2 <= 1; ++d2)
			if(Hash.count({x + d1 + d2, y}))
				++cnt;
		if(cnt == 1)
			return 0;
	}
	return 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", x + i, y + i);
		Hash[{x[i], y[i]}] = i;
	}
	for(int i = 0; i < n; ++i)
		if(check(x[i], y[i]))
			Cube.insert(i);
	for(int i = 0; i < n; ++i)
	{
		int now = i & 1 ? *Cube.begin() : *Cube.rbegin();
		ans = ((long long)ans * n + now) % mod;
		Cube.erase(now);
		Hash.erase({x[now], y[now]});
		for(int d = -2, k; d <= 2; ++d)
			if(Hash.count({x[now] + d, y[now]}) && Cube.count(k = Hash[{x[now] + d, y[now]}]) && !check(x[now] + d, y[now]))
				Cube.erase(k);
		if(!y[now])
			continue;
		for(int d = -1, k; d <= 1; ++d)
			if(Hash.count({x[now] + d, y[now] - 1}) && !Cube.count(k = Hash[{x[now] + d, y[now] - 1}]) && check(x[now] + d, y[now] - 1))
				Cube.insert(k);
	}
	printf("%d\n", ans);
	return 0;
}
