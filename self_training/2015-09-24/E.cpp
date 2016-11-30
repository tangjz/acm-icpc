#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10, INF = ~0u >> 1;
struct Exp
{
	int len, num[maxn];
	char op[maxn];
} val[maxn];
int t;
char str[maxn];
inline int calc(int x, char op, int y)
{
	if(op == '+')
		return x + y;
	if(op == '-')
		return x - y;
	return x * y;
}
pair<int, int> dfs(int dep, int flag)
{
	if(!val[dep].len)
		return make_pair(val[dep].num[0], -1);
	pair<int, int> ret = make_pair(flag ? INF : -INF, -1), tmp;
	for(int i = 0; i < val[dep].len; ++i)
	{
		int x = calc(val[dep].num[i], val[dep].op[i], val[dep].num[i + 1]);
		memcpy(val + dep + 1, val + dep, sizeof val[0]);
		--val[dep + 1].len;
		val[dep + 1].num[i] = x;
		for(int j = i + 1; j < val[dep].len; ++j)
		{
			val[dep + 1].num[j] = val[dep + 1].num[j + 1];
			val[dep + 1].op[j - 1] = val[dep + 1].op[j];
		}
		tmp = dfs(dep + 1, flag ^ 1);
		if(flag && ret.first > tmp.first)
		{
			ret.first = tmp.first;
			ret.second = i;
		}
		else if(!flag && ret.first < tmp.first)
		{
			ret.first = tmp.first;
			ret.second = i;
		}
	}
	return ret;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &val[0].len, &val[0].num[0]);
		for(int i = 0; i < val[0].len; ++i)
		{
			scanf("%s%d", str, &val[0].num[i + 1]);
			val[0].op[i] = str[0];
		}
		pair<int, int> r1 = dfs(0, 0), r2 = dfs(0, 1);
		printf("Case %d:\n", Case);
		printf("Player 1 (%d%c%d) leads to %d\n", val[0].num[r1.second], val[0].op[r1.second], val[0].num[r1.second + 1], r1.first);
		printf("Player 2 (%d%c%d) leads to %d\n", val[0].num[r2.second], val[0].op[r2.second], val[0].num[r2.second + 1], r2.first);
		if(r1.first + r2.first)
			printf("Player %d wins\n", r1.first + r2.first > 0 ? 1 : 2);
		else
			puts("Tie");
	}
	return 0;
}
