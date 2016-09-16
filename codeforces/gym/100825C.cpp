#include <cstdio>
typedef long long LL;
const int maxn = 9, maxm = 10, maxe = 200001, mod = 99991;
int n, m, posx[maxm], posy[maxm], sz[1 << maxm], pre = 1, cur;
LL t, pw[maxm + 1];
char op;
bool ban[1 << maxm];
struct HashMap
{
	int tot, systim, lnk[mod], tim[mod];
	struct Node
	{
		int nxt, state;
		LL val, ways;
	} e[maxe];
	void init()
	{
		tot = 0;
		++systim;
	}
	void insert(int state, LL val, LL ways)
	{
		int pos = (val << m | state) % mod;
		if(tim[pos] != systim)
		{
			tim[pos] = systim;
			lnk[pos] = -1;
		}
		for(int it = lnk[pos]; it != -1; it = e[it].nxt)
			if(e[it].state == state && e[it].val == val)
			{
				e[it].ways += ways;
				return;
			}
		e[tot] = (Node){lnk[pos], state, val, ways};
		lnk[pos] = tot++;
	}
} f[2];
int main()
{
	for(int i = 1; i < 1 << maxm; ++i)
		sz[i] = sz[i >> 1] + (i & 1);
	while(scanf("%d%d%lld %c", &n, &m, &t, &op) == 4)
	{
		for(int i = 0; i < m; ++i)
			scanf("%d%d", posx + i, posy + i);
		if(op == '-')
		{
			int ans = 0;
			for(int i = 1; i <= n; ++i)
				for(int j = i + 1; j <= n; ++j)
					if(j == i + t)
						++ans;
			printf("%d\n", ans << 1);
			continue;
		}
		if(op == '/')
		{
			int ans = 0;
			for(int i = 1; i <= n; ++i)
				for(int j = i + 1; j <= n; ++j)
					if(j == i * t)
						++ans;
			printf("%d\n", ans << 1);
			continue;
		}
		int all = (1 << m) - 1;
		for(int i = 1; i <= all; ++i)
			for(int j = 0, lbt = -1; j < m; ++j)
			{
				if(!(i & (1 << j)))
					continue;
				if(lbt == -1)
				{
					if((ban[i] = ban[i ^ (1 << j)]))
						break;
					lbt = j;
				}
				else if(posx[lbt] == posx[j] || posy[lbt] == posy[j])
				{
					ban[i] = 1;
					break;
				}
			}
		f[cur].init();
		f[cur].insert(0, op == '*', 1);
		for(int i = 1; i <= n; ++i)
		{
			pre ^= 1;
			cur ^= 1;
			f[cur].init();
			pw[0] = op == '*';
			for(int j = 1; j <= m; ++j)
				pw[j] = op == '*' ? pw[j - 1] * i : pw[j - 1] + i;
			for(int it = 0; it < f[pre].tot; ++it)
			{
				int pmsk = f[pre].e[it].state;
				LL pval = f[pre].e[it].val, pways = f[pre].e[it].ways;
				f[cur].insert(pmsk, pval, pways);
				for(int s = pmsk ^ all, j = s; j; j = (j - 1) & s)
				{
					if(ban[j])
						continue;
					LL cval = op == '*' ? pval * pw[sz[j]] : pval + pw[sz[j]];
					if(cval > t || (op == '*' && t % cval != 0))
						continue;
					f[cur].insert(pmsk | j, cval, pways);
				}
			}
		}
		LL ans = 0;
		for(int it = 0; it < f[cur].tot; ++it)
			if(f[cur].e[it].state == all && f[cur].e[it].val == t)
				ans += f[cur].e[it].ways;
		printf("%lld\n", ans);
	}
	return 0;
}
