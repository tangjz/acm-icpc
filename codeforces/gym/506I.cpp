#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 51, maxm = 5001, maxs = 27, mod = 960991;
int t, n, m, cnt[maxn], pcnt[maxn][maxs], pen[maxn], last[maxn][maxs][2], id[maxn], tot, Hash[mod];
char name[maxn][maxs];
bool pvis[maxn][maxs];
struct Node
{
	int nxt, id;
	unsigned long long val;
} e[maxn];
bool equiv(const int &x, const int &y)
{
	if(cnt[x] != cnt[y] || pen[x] != pen[y])
		return 0;
	for(int i = 0; i < cnt[x]; ++i)
		if(last[x][i][0] != last[y][i][0] || last[x][i][1] != last[y][i][1])
			return 0;
	return 1;
}
bool cmp(const int &x, const int &y)
{
	if(cnt[x] != cnt[y])
		return cnt[x] > cnt[y];
	if(pen[x] != pen[y])
		return pen[x] < pen[y];
	for(int i = cnt[x] - 1; i >= 0; --i)
		if(last[x][i][0] != last[y][i][0])
			return last[x][i][0] < last[y][i][0];
		else if(last[x][i][1] != last[y][i][1])
			return last[x][i][1] < last[y][i][1];
	return strcmp(name[x], name[y]) < 0;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		memset(cnt, 0, sizeof cnt);
		memset(pcnt, 0, sizeof pcnt);
		memset(pen, 0, sizeof pen);
		memset(pvis, 0, sizeof pvis);
		memset(Hash, 0, sizeof Hash);
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", name[i]);
			unsigned long long val = 0;
			for(int j = 0; name[i][j]; ++j)
				val = val * 29 + name[i][j] - 'a' + 1;
			int pos = val % mod;
			e[++tot] = (Node){Hash[pos], i, val};
			Hash[pos] = tot;
			id[i] = i;
		}
		while(m--)
		{
			int tt, nameid;
			char str[maxs], proid;
			scanf("%d%s %c", &tt, str, &proid);
			unsigned long long val = 0;
			for(int j = 0; str[j]; ++j)
				val = val * 29 + str[j] - 'a' + 1;
			int pos = val % mod;
			for(int it = Hash[pos]; it; it = e[it].nxt)
				if(e[it].val == val)
				{
					nameid = e[it].id;
					break;
				}
			scanf("%s", str);
			if(str[0] == 'r')
				++pcnt[nameid][proid - 'A'];
			else
			{
				if(!pvis[nameid][proid - 'A'])
				{
					pen[nameid] += tt + pcnt[nameid][proid - 'A'] * 20;
					pvis[nameid][proid - 'A'] = 1;
					last[nameid][cnt[nameid]][0] = tt;
					last[nameid][cnt[nameid]++][1] = pen[nameid];
				}
				
			}
		}
		sort(id, id + n, cmp);
		for(int i = 0, pre; i < n; ++i)
		{
			if(!i || !equiv(id[i - 1], id[i]))
				pre = i + 1;
			printf("%d %s %d %d\n", pre, name[id[i]], cnt[id[i]], pen[id[i]]);
		}
	}
	return 0;
}
