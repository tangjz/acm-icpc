#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 9, maxm = 10;
int n, m, posx[maxm], posy[maxm], sz[1 << maxm], pre = 1, cur;
LL t, pw[maxm + 1];
char op;
map<pair<int, LL>, LL> f[2];
bool ban[1 << maxm];

int main()
{
	scanf("%d%d%I64d %c", &n, &m, &t, &op);
	if(op == '-')
	{
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = i + 1; j <= n; ++j)
				if(j == i + t)
					++ans;
		printf("%d\n", ans << 1);
		return 0;
	}
	if(op == '/')
	{
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = i + 1; j <= n; ++j)
				if(j == i * t)
					++ans;
		printf("%d\n", ans << 1);
		return 0;
	}
	for(int i = 0; i < m; ++i)
		scanf("%d%d", posx + i, posy + i);
	int all = (1 << m) - 1;
	for(int i = 1; i <= all; ++i)
		for(int j = 0, lbt = -1; j < m; ++j)
		{
			if(!(i & (1 << j)))
				continue;
			++sz[i];
			if(lbt == -1)
			{
				if(ban[i ^ (1 << j)])
				{
					ban[i] = 1;
					break;
				}
				lbt = j;
			}
			else if(posx[lbt] == posx[j] || posy[lbt] == posy[j])
			{
				ban[i] = 1;
				break;
			}
		}
	f[cur][make_pair(0, op == '*')] = 1;
	for(int i = 1; i <= n; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		map<pair<int, LL>, LL>().swap(f[cur]);
		pw[0] = op == '*';
		for(int j = 1; j <= m; ++j)
			pw[j] = op == '*' ? pw[j - 1] * i : pw[j - 1] + i;
		for(map<pair<int, LL>, LL>::iterator it = f[pre].begin(); it != f[pre].end(); ++it)
		{
			pair<int, LL> pmsk = it -> first;
			LL ways = it -> second;
			f[cur][pmsk] += ways;
			for(int s = pmsk.first ^ all, j = s; j; j = (j - 1) & s)
			{
				if(ban[j])
					continue;
				pair<int, LL> cmsk = make_pair(pmsk.first | j, op == '*' ? pmsk.second * pw[sz[j]] : pmsk.second + pw[sz[j]]);
				if(cmsk.second > t || (op == '*' && t % cmsk.second != 0))
					continue;
				f[cur][cmsk] += ways;
			}
		}
	}
	printf("%I64d\n", f[cur][make_pair(all, t)]);
	return 0;
}
