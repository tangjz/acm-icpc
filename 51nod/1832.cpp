#include <stdio.h>
typedef long long LL;
const int maxn = 10001, maxs = 335, BASE = (int)1e9, BLEN = 9, DT = 30;
int n, pre[maxn], suf[maxn], pid[maxn], sid[maxn], cnt, len, ans[maxs];
void dfs(int pL, int pR, int sL, int sR) {
	if(pL == pR)
		return;
	if(pre[pL + 1] == suf[sR - 1]) {
		++cnt;
		dfs(pL + 1, pR, sL, sR - 1);
		return;
	}
	int pM = pid[suf[sR - 1]], sM = sid[pre[pL + 1]];
	dfs(pL + 1, pM - 1, sL, sM);
	dfs(pM, pR, sM + 1, sR - 1);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", pre + i);
		pid[pre[i]] = i;
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%d", suf + i);
		sid[suf[i]] = i;
	}
	dfs(1, n, 1, n);
	len = ans[0] = 1;
	for( ; cnt > 0; cnt -= DT) {
		int val = 1 << (cnt < DT ? cnt : DT);
		LL rem = 0;
		for(int i = 0; i < len; ++i) {
			rem += (LL)ans[i] * val;
			ans[i] = rem % BASE;
			rem /= BASE;
		}
		for( ; rem > 0; ans[len++] = rem % BASE, rem /= BASE);
	}
	printf("%d", ans[len - 1]);
	for(int i = len - 2; i >= 0; --i)
		printf("%0*d", BLEN, ans[i]);
	putchar('\n');
	return 0;
}
