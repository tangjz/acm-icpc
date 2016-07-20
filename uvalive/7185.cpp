#include <bitset>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 40000, maxm = 10001, maxs = 26, bdelta = 1 << 6;
int t, n, m, q, tot, que[maxm], L, R;
struct Trie
{
	int fail, ch[maxs];
	bool val;
} e[maxm];
char str[maxn + 1], tmp[maxm + 1];
size_t bsize;
struct Bitset
{
	typedef unsigned long long ULL;
	ULL data[maxn >> 6];
	inline void reset()
	{
		memset(data, 0, bsize * sizeof(ULL));
	}
	inline void set(size_t pos)
	{
		data[pos >> 6] |= 1ULL << (pos & (bdelta - 1));
	}
	void flip()
	{
		for(size_t i = 0; i < bsize; ++i)
			data[i] = ~data[i];
	}
	void shiftRightOne(Bitset &t)
	{
		t.data[0] = data[0] >> 1;
		for(size_t i = 1; i < bsize; ++i)
		{
			if(data[i] & 1)
				t.data[i - 1] |= 1ULL << bdelta - 1;
			t.data[i] = data[i] >> 1;
		}
	}
	void operator &= (const Bitset &t)
	{
		for(size_t i = 0; i < bsize; ++i)
			data[i] &= t.data[i];
	}
	void operator |= (const Bitset &t)
	{
		for(size_t i = 0; i < bsize; ++i)
			data[i] |= t.data[i];
	}
	inline bool test(size_t pos)
	{
		return (data[pos >> 6] >> (pos & (bdelta - 1))) & 1;
	}
} f[maxn], temp;
int scnt;
pair<int, int> sque[maxn];
inline void scan(int &x)
{
	register int ch;
	while((ch = getchar()) < '0' || ch > '9');
	for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch - '0'));
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%s", &n, &m, &q, str);
		tot = 0;
		memset(e + (tot++), 0, sizeof(Trie));
		for(int i = 0; i < m; ++i)
		{
			scanf("%s", tmp);
			int o = 0;
			for(int j = 0; tmp[j]; ++j)
			{
				tmp[j] -= 'a';
				if(!e[o].ch[tmp[j]])
				{
					e[o].ch[tmp[j]] = tot;
					memset(e + (tot++), 0, sizeof(Trie));
				}
				o = e[o].ch[tmp[j]];
			}
			e[o].val = 1;
		}
		L = R = 0;
		for(int i = 0; i < maxs; ++i)
			if(e[0].ch[i])
				que[R++] = e[0].ch[i];
		while(L < R)
		{
			int &u = que[L++];
			for(int i = 0; i < maxs; ++i)
				if(e[u].ch[i])
				{
					int &v = e[u].ch[i], k = e[u].fail;
					que[R++] = v;
					while(k && !e[k].ch[i])
						k = e[k].fail;
					e[v].fail = k = e[k].ch[i];
				}
		}
		scnt = 0;
		for(int i = 0; i < n; ++i)
		{
			str[i] -= 'a';
			sque[scnt++] = make_pair(i, 0);
		}
		bsize = (n - 1 >> 6) + 1;
		for(int i = 0; i < n; ++i)
		{
			int stmp = 0;
			f[i].reset();
			for(int j = 0, o; j < scnt; ++j)
				if((o = e[sque[j].second].ch[str[sque[j].first + i]]))
				{
					if(e[o].val)
						f[i].set(sque[j].first);
					sque[stmp++] = make_pair(sque[j].first, o);
				}
			scnt = stmp;
			if(i)
			{
				f[i - 1].shiftRightOne(temp);
				temp &= f[i - 1];
				f[i] |= temp;
			}
			f[i].flip();
		}
		while(q--)
		{
			scan(L), scan(R);
			putchar('0' + f[R - L].test(L - 1));
			putchar('\n');
		}
	}
	return 0;
}
