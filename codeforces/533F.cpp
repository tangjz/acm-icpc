#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1, maxc = 27;
int n, m, a[maxn], b[maxn], fir[maxc], pos[maxc], f[maxn], cnt, ans[maxn];
char buf[maxn], pat[maxn];
inline bool match(int pos, int val) {
	return b[pos] == -1 ? val == -1 || val > pos : b[pos] == val;
}
inline bool hasPerm(char *txt) {
	static int perm[maxc];
	memset(perm, -1, sizeof perm);
	for(int i = 0; i < maxc; ++i) {
		if(fir[i] == -1)
			continue;
		int j = txt[fir[i]] - 'a';
		if(perm[i] == -1) {
			perm[i] = j;
		} else if(perm[i] != j) {
			return 0;
		}
		if(perm[j] == -1) {
			perm[j] = i;
		} else if(perm[j] != i) {
			return 0;
		}
	}
	return 1;
}
int main() {
	scanf("%d%d%s%s", &n, &m, buf, pat);
	memset(fir, -1, sizeof fir);
	memset(pos, -1, sizeof pos);
	for(int i = 0; i < m; ++i) {
		int ch = pat[i] - 'a';
		if(pos[ch] == -1) {
			b[i] = -1;
			fir[ch] = i;
		} else {
			b[i] = i - pos[ch];
		}
		pos[ch] = i;
	}
	for(int i = 1, j = 0; i < m; ++i) {
		for( ; j && !match(j, b[i]); j = f[j]);
		if(match(j, b[i]))
			++j;
		f[i + 1] = j;
	}
	memset(pos, -1, sizeof pos);
	for(int i = 0, j = 0; i < n; ++i) {
		int ch = buf[i] - 'a';
		a[i] = pos[ch] == -1 ? -1 : i - pos[ch];
		pos[ch] = i;
		for( ; j && !match(j, a[i]); j = f[j]);
		if(match(j, a[i]))
			++j;
		if(j == m) {
			if(hasPerm(buf + i - m + 1))
				ans[cnt++] = i - m + 1;
			j = f[j];
		}
	}
	printf("%d\n", cnt);
	for(int i = 0; i < cnt; ++i)
		printf("%d%c", ans[i] + 1, " \n"[i == cnt - 1]);
	return 0;
}