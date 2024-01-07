#include <stdio.h>
#include <cstring>
const int maxn = 1000010, mod = 5800079, maxd = 26;
int t, sys_tim, n, tot, ban[maxn], f[maxn], s[maxn], *que = s, L, R;
char str[maxn];
int e_tot, tim[mod], lnk[mod];
struct Hash
{
	int nxt, idx, val;
} e[maxn];
int m_tot, m_lnk[maxn];
struct Edge
{
	int nxt, v;
	char ch;
} m_e[maxn];
inline void add_edge(int u, int v, char ch)
{
	m_e[m_tot] = (Edge){m_lnk[u], v, ch};
	m_lnk[u] = m_tot++;
}
inline int insert(int idx)
{
	int pos = idx % mod;
	if(tim[pos] != sys_tim)
	{
		lnk[pos] = -1;
		tim[pos] = sys_tim;
	}
	e[e_tot] = (Hash){lnk[pos], idx, tot};
	lnk[pos] = e_tot++;
	m_lnk[tot] = -1;
	ban[tot] = 0;
	return tot++;
}
inline int find(int idx)
{
	int pos = idx % mod;
	if(tim[pos] != sys_tim)
	{
		lnk[pos] = -1;
		tim[pos] = sys_tim;
	}
	for(int it = lnk[pos]; it != -1; it = e[it].nxt)
		if(e[it].idx == idx)
			return e[it].val;
	return -1;
}
int main()
{
	scanf("%d ", &t);
	while(t--)
	{
		++sys_tim;
		e_tot = m_tot = 0;
		m_lnk[0] = -1;
		ban[0] = f[0] = 0;
		tot = 1;
		scanf("%d ", &n);
		while(n--)
		{
			int rt = 0, len;
			scanf("%s ", str);
			len = strlen(str);
			for(int i = 0; i < len; ++i)
			{
				str[i] -= 'a';
				int idx = rt * maxd + str[i], nxt = find(idx);
				if(nxt == -1)
				{
					nxt = insert(idx);
					add_edge(rt, nxt, str[i]);
				}
				rt = nxt;
			}
			ban[rt] = len;
		}
		L = R = 0;
		for(int it = m_lnk[0]; it != -1; it = m_e[it].nxt)
		{
			int v = m_e[it].v;
			que[R++] = v;
			f[v] = 0;
		}
		while(L < R)
		{
			int u = que[L++];
			for(int it = m_lnk[u]; it != -1; it = m_e[it].nxt)
			{
				int v = m_e[it].v, i = m_e[it].ch;
				que[R++] = v;
				for(f[v] = f[u]; f[v] && find(f[v] * maxd + i) == -1; f[v] = f[f[v]]);
				int nxt = find(f[v] * maxd + i);
				if(nxt != -1)
					f[v] = nxt;
				ban[v] = ban[v] ? ban[v] : ban[f[v]];
			}
		}
		gets(str);
		n = strlen(str);
		memset(s, 0, (n + 1) * sizeof(int));
		for(int i = 0, rt = 0; i < n; ++i)
			if(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z')
			{
				int ch = str[i] >= 'a' && str[i] <= 'z' ? str[i] - 'a' : str[i] - 'A';
				for( ; rt && find(rt * maxd + ch) == -1; rt = f[rt]);
				int nxt;
				if((nxt = find(rt * maxd + ch)) != -1)
					rt = nxt;
				if(ban[rt])
				{
					++s[i - ban[rt] + 1];
					--s[i + 1];
				}
			}
			else
				rt = 0;
		for(int i = 0; i < n; ++i)
		{
			if(i)
				s[i] += s[i - 1];
			if(s[i] > 0)
				str[i] = '*';
		}
		puts(str);
	}
	return 0;
}
