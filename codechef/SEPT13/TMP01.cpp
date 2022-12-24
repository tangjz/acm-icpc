#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;
int len, tot, rt, curP, curC, curL, rem, que[maxn], qL, qR;
LL sum;
struct Node {
	int L, R, par, fail;
	map<char, int> nxt;
	int next(char ch) {
		map<char, int>::iterator it = nxt.find(ch);
		return it == nxt.end() ? 0 : it -> second;
	}
} e[maxn << 1 | 1];
char buf[maxn];
int newNode(int L, int R, int par) { // [L, R)
	e[tot] = (Node){L, R, par, rt, map<char, int>()};
	return tot++;
}
void append(char ch) {
	buf[len++] = ch, ++rem;
	for(int last = 0; rem; --rem) {
		!curL && (curC = len - 1);
		int p = e[curP].next(buf[curC]);
		while(p && curL >= e[p].R - e[p].L) {
			curC += e[p].R - e[p].L;
			curL -= e[p].R - e[p].L;
			curP = p;
			p = e[curP].next(buf[curC]);
		}
		if(!p) {
			int u = e[curP].nxt[buf[curC]] = newNode(len - 1, maxn, curP);
			sum += e[u].R - e[u].L;
			que[qR++] = u;
			last && (e[last].fail = curP);
			last = curP;
		} else if(buf[e[p].L + curL] == ch) {
			++curL;
			last && (e[last].fail = curP);
			break;
		} else {
			int u = newNode(e[p].L, e[p].L + curL, curP);
			int v = newNode(len - 1, maxn, u);
			sum += e[v].R - e[v].L;
			que[qR++] = v;
			e[p].par = u;
			e[curP].nxt[buf[curC]] = u;
			e[p].L += curL;
			e[u].nxt[buf[e[p].L]] = p;
			e[u].nxt[ch] = v;
			last && (e[last].fail = u);
			last = u;
		}
		curP == rt && curL ? (--curL, ++curC) : (curP = e[curP].fail);
	}
}
void remove() {
	if(curL) {
		int p = e[curP].next(buf[curC]);
		while(p && curL >= e[p].R - e[p].L) {
			curC += e[p].R - e[p].L;
			curL -= e[p].R - e[p].L;
			curP = p;
			p = e[curP].next(buf[curC]);
		}
	}
	int pos = que[qL++];
	while(pos != curP && !e[pos].nxt.size()) {
		e[e[pos].par].nxt.erase(buf[e[pos].L]);
		sum -= e[pos].R - e[pos].L;
		pos = e[pos].par;
	}
	if(rem && pos == curP) {
		if(!curL && !e[pos].nxt.size()) {
			if(e[pos].R < maxn) {
				e[pos].L += len - e[pos].R;
				e[pos].R = maxn;
				sum += maxn - len;
				que[qR++] = pos;
			}
		} else if(curC < len && !e[pos].next(buf[curC])) {
			int u = e[pos].nxt[buf[curC]] = newNode(len - curL, maxn, pos);
			sum += e[u].R - e[u].L;
			que[qR++] = u;
		} else {
			return;
		}
		curP == rt && curL ? (--curL, ++curC) : (curP = e[curP].fail);
		--rem;
	}
}
int main() {
	curP = rt = newNode(0, 0, 0);
	e[rt].fail = rt;
	curL = 0;
	int q, ans = 0;
	scanf("%d", &q);
	while(q--) {
		char op[3];
		scanf("%s", op);
		if(op[0] == '+') {
			scanf("%s", op);
			append(op[0]);
		} else {
			remove();
		}
		ans = (ans + sum + (LL)(qR - qL) * (len - maxn)) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
