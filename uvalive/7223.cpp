#include <vector>
#include <string>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;
const int maxn = 5001, maxm = 5, maxs = 21, maxd = 26, maxc = 15981, maxo = 10000001;
unordered_map<string, int> Index;
int t, n, q, sz[maxn], plen[maxn][maxm], szA, szB;
char pat[maxn][maxm][maxs];
struct NFA {
	vector<int> nxt[maxd];
	void clear() {
		for(int i = 0; i < maxd; ++i)
			vector<int>().swap(nxt[i]);
	}
} A[maxc], B[maxc];
void buildNFA(int &slen, NFA seq[maxc], int len, char str[maxs])
{
	slen = 0;
	seq[slen++].clear();
	for(int i = 0; i < len; ++i)
	{
		seq[slen++].clear();
		seq[i].nxt[(int)(str[i] - 'A')].push_back(i + 1);
	}
	for(int L = 0; L < len; ++L)
		for(int R = L + 1; R <= len; ++R)
		{
			char tp = str[R];
			str[R] = '\0';
			int id = Index.count((string)(str + L)) ? Index[(string)(str + L)] : -1;
			if(id == -1)
			{
				str[R] = tp;
				continue;
			}
			for(int i = 0; i < sz[id]; ++i)
			{
				if(strcmp(pat[id][i], str + L) == 0)
					continue;
				int last = L;
				for(int j = 0; j < plen[id][i] - 1; ++j)
				{
					seq[slen++].clear();
					seq[last].nxt[(int)(pat[id][i][j] - 'A')].push_back(slen - 1);
					last = slen - 1;
				}
				seq[last].nxt[(int)(pat[id][i][plen[id][i] - 1] - 'A')].push_back(R);
			}
			str[R] = tp;
		}
	/*
	puts("print NFA");
	for(int i = 0; i < slen; ++i)
	{
		printf("state %d\n", i);
		for(int d = 0; d < maxd; ++d)
		{
			if(!seq[i].nxt[d].size())
				continue;
			printf("next %c :", 'A' + d);
			for(auto &j : seq[i].nxt[d])
				printf(" %d", j);
			putchar('\n');
		}
	}
	*/
}
unordered_set<int> Hash;
int que[maxo], fro[maxo], L, R, olen;
char ch[maxo], out[maxs * maxs];
bool eq[maxo];
inline int idx(int x, int y)
{
	return x * szB + y;
}
inline void rdx(int o, int &x, int &y)
{
	x = o / szB;
	y = o % szB;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		unordered_map<string, int>().swap(Index);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", sz + i);
			for(int j = 0; j < sz[i]; ++j)
			{
				scanf("%s", pat[i][j]);
				plen[i][j] = strlen(pat[i][j]);
				Index[(string)pat[i][j]] = i;
			}
		}
		scanf("%d", &q);
		printf("Case #%d:\n", Case);
		while(q--)
		{
			static char str[maxs];
			scanf("%s", str);
			int alen = strlen(str);
			buildNFA(szA, A, alen, str);
			scanf("%s", str);
			int blen = strlen(str);
			buildNFA(szB, B, blen, str);
			unordered_set<int>().swap(Hash);
			L = R = 0;
			int S = idx(0, 0), T = idx(alen, blen);
			bool flag = 0;
			Hash.insert(S);
			eq[R] = 0;
			que[R++] = S;
			//printf("bfs %d %d (#, 0)\n", 0, 0);
			for(int L2; L < R; L = L2)
			{
				for(L2 = L + 1; L2 < R && eq[L2]; ++L2);
				for(int d = 0; d < maxd; ++d)
				{
					bool fir = 1;
					for(int u = L; u < L2; ++u)
					{
						int udx = que[u], ux, uy;
						rdx(udx, ux, uy);
						for(auto &vx : A[ux].nxt[d])
							for(auto &vy : B[uy].nxt[d])
							{
								int vdx = idx(vx, vy);
								if(Hash.count(vdx))
									continue;
								Hash.insert(vdx);
								fro[R] = u;
								ch[R] = 'A' + d;
								eq[R] = fir ? (fir = 0) : 1;
								//printf("bfs %d %d (%c, %d)\n", vx, vy, ch[R], eq[R]);
								que[R++] = vdx;
								if(vdx == T)
								{
									flag = 1;
									goto finished;
								}
							}
					}
				}
			}
		finished:
			if(!flag)
			{
				puts("[ALIEN]");
				continue;
			}
			olen = 0;
			for(int i = R - 1; i; out[olen++] = ch[i], i = fro[i]);
			reverse(out, out + olen);
			out[olen] = '\0';
			puts(out);
		}
	}
	return 0;
}
