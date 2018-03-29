#include <bits/stdc++.h>
using namespace std;
const int maxn = 101, maxl = 7;
int n, pre[maxn], suf[maxn];
char buf[maxn][maxl + 2], f[maxn][maxn][maxl][maxn][maxl], ans[maxn];

bool F(int len, int pL, int qL, int pR, int qR) {
	if(!len)
		return pL > pR;
	char &ret = f[len][pL][qL][pR][qR];
	if(ret != -1)
		return ret;
	int pL2 = pL, qL2 = qL + 1, pR2 = pR, qR2 = qR - 1;
	qL2 == maxl && (++pL2, qL2 = pre[pL2]);
	qR2 == -1 && (--pR2, qR2 = suf[pR2]);
	if(buf[pL][qL] == buf[pR][qR])
		ret = F(len - 1, pL2, qL2, pR2, qR2);
	else
		ret = F(len - 1, pL2, qL2, pR, maxl - 1) || F(len - 1, pL, 0, pR2, qR2);
	return ret;
}

int main() {
	while(scanf("%d", &n) == 1) {
		memset(f, -1, sizeof f);
		for(int i = 0; i < n; ++i) {
			scanf("%s", buf[i]);
			assert(strlen(buf[i]) == maxl);
			for(int j = 0; j < maxl; ++j)
				for(int k = j + 1; k < maxl; ++k)
					assert(buf[i][j] != buf[i][k]);
		}
		for(int i = 1; i < n; ++i) {
			pre[i] = 0;
			suf[i - 1] = maxl - 1;
			for(int j = maxl - 1; j > 0; --j)
				if(strncmp(buf[i - 1] + maxl - j, buf[i], j) == 0) {
					pre[i] = j;
					suf[i - 1] = maxl - 1 - j;
					break;
				}
		}
		for(int i = 1; i < maxn; ++i) {
			if(!F(i, 0, 0, n - 1, maxl - 1))
				continue;
			int pL = 0, qL = 0, pR = n - 1, qR = maxl - 1;
			for(int j = 0; j < i; ++j) {
				int pL2 = pL, qL2 = qL + 1, pR2 = pR, qR2 = qR - 1;
				qL2 == maxl && (++pL2, qL2 = pre[pL2]);
				qR2 == -1 && (--pR2, qR2 = suf[pR2]);
				if(buf[pL][qL] == buf[pR][qR]) {
					ans[j] = buf[pL][qL];
				} else {
					bool lft = F(i - j - 1, pL2, qL2, pR, maxl - 1), rht = F(i - j - 1, pL, 0, pR2, qR2);
					ans[j] = !rht || (lft && buf[pL][qL] < buf[pR][qR]) ? buf[pL][qL] : buf[pR][qR];
				}
				buf[pL][qL] == ans[j] ? (pL = pL2, qL = qL2) : (qL = 0);
				buf[pR][qR] == ans[j] ? (pR = pR2, qR = qR2) : (qR = maxl - 1);
			}
			for(int j = 0; j < i - 1; ++j)
				ans[i * 2 - 2 - j] = ans[j];
			ans[i * 2 - 1] = '\0';
			break;
		}
		puts(ans);
	}
	return 0;
}
