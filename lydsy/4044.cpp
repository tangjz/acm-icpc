#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 3, maxc = 4;
int t, n, tot, cur, len[maxn], fail[maxn], nxt[maxn][maxc + 1];
char buf[maxn], str[maxn];
int newNode(int length, int prev = 0) {
	len[tot] = length;
	fail[tot] = prev;
	memset(nxt[tot], 0, sizeof nxt[0]);
	return tot++;
}
void init() {
	n = tot = 0;
	cur = newNode(0);
	fail[cur] = newNode(-1, cur);
	buf[0] = '\0';
}
int slen, trans[257], half[maxn], f[maxn], ans;
void append(char ch) {
	int o = trans[buf[++n] = ch];
	for( ; buf[n - len[cur] - 1] != buf[n]; cur = fail[cur]);
	if(!nxt[cur][o]) {
		int p = newNode(len[cur] + 2), q = fail[cur];
		for( ; buf[n - len[q] - 1] != buf[n]; q = fail[q]);
		fail[p] = nxt[q][o];
		for(q = half[cur]; buf[n - len[q] - 1] != buf[n]; q = fail[q]);
		for(q = nxt[q][o]; len[q] > len[p] / 2; q = fail[q]);
		half[p] = q;
		nxt[cur][o] = p;
		if(!(len[p] & 1)) {
			f[p] = (cur ? f[cur] : len[p] / 2) + 1;
			if(!(len[half[p]] & 1))
				f[p] = min(f[p], f[q] + len[p] / 2 - len[q] + 1);
			ans = min(ans, f[p] + slen - len[p]);
		}
	}
	cur = nxt[cur][o];
}
int main() {
	trans['A'] = 0;
	trans['G'] = 1;
	trans['C'] = 2;
	trans['T'] = 3;
	scanf("%d", &t);
	while(t--) {
		scanf("%s", str);
		ans = slen = strlen(str);
		init();
		for(int i = 0; i < slen; ++i)
			append(str[i]);
		printf("%d\n", ans);
	}
	return 0;
}
