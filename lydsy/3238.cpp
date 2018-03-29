#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5, maxc = 27;
int len, tot, rt, curP, curC, curL, rem;
struct SuffixTrie {
	int L, R, fail, nxt[maxc | 1];
} e[maxn << 1 | 1];
char buf[maxn | 1];
int newNode(int L, int R) { // [L, R)
	e[tot].L = L;
	e[tot].R = R;
	e[tot].fail = rt;
	memset(e[tot].nxt, 0, sizeof e[0].nxt);
	return tot++;
}
void append(char ch) {
	buf[len++] = ch;
	++rem;
	int last = 0;
	while(rem) {
		if(!curL)
			curC = len - 1;
		int p = e[curP].nxt[buf[curC] - 'a'];
		while(p && curL >= e[p].R - e[p].L) {
			curC += e[p].R - e[p].L;
			curL -= e[p].R - e[p].L;
			curP = p;
			p = e[curP].nxt[buf[curC] - 'a'];
		}
		if(!p) {
			e[curP].nxt[buf[curC] - 'a'] = newNode(len - 1, maxn);
			if(last)
				e[last].fail = curP;
			last = curP;
		} else if(buf[e[p].L + curL] == ch) {
			++curL;
			if(last)
				e[last].fail = curP;
			break;
		} else {
			int u = newNode(e[p].L, e[p].L + curL);
			int v = newNode(len - 1, maxn);
			e[curP].nxt[buf[curC] - 'a'] = u;
			e[p].L += curL;
			e[u].nxt[buf[e[p].L] - 'a'] = p;
			e[u].nxt[ch - 'a'] = v;
			if(last)
				e[last].fail = u;
			last = u;
		}
		--rem;
		if(curP == rt && curL) {
			--curL;
			++curC;
		} else {
			curP = e[curP].fail;
		}
	}
}
LL ans;
int dfs(int u) {
	int ret = 0;
	bool chk = 1;
	for(int i = 0; i < maxc; ++i) {
		if(!e[u].nxt[i])
			continue;
		ret += dfs(e[u].nxt[i]);
		chk = 0;
	}
	ret += chk;
	ans -= ret * (ret - 1LL) * (e[u].R - e[u].L);
	return ret;
}
int main() {
	scanf("%s", buf);
	curP = rt = newNode(0, 0);
	e[rt].fail = rt;
	curL = 0;
	for(int i = 0; buf[i]; ++i)
		append(buf[i]);
	ans = (len - 1LL) * len * (len + 1) / 2;
	append('z' + 1); // '$'
	dfs(rt);
	printf("%lld\n", ans);
	return 0;
}
