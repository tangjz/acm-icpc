#include <bits/stdc++.h>
const int maxn = 101, maxk = 5;
int n, m, col[maxn], cnt[maxn], pre[maxn], f[maxk][maxn][maxn];
inline void upd(int &x, int y) {
	x > y && (x = y);
}
int F(int L, int R, int x) {
	if(L > R)
		return 0;
	upd(x, m - cnt[R]);
	int &ret = f[x][L][R];
	if(ret == -1) {
		ret = x < m - cnt[R] ? F(L, R, x + 1) + 1 : F(L, R - 1, 0);
		for(int M = pre[R]; M >= L; M = pre[M])
			upd(ret, F(L, M, x + cnt[R]) + F(M + 1, R - 1, 0));
	}
	return ret;
}
int main() {
	int t, x, *pos = f[0][0];
	scanf("%d%d", &t, &m);
	memset(pos, -1, sizeof(f[0][0]));
	while(t--) {
		scanf("%d", &x);
		if(!n || col[n - 1] != x) {
			col[n] = x;
			cnt[n] = 1;
			pre[n] = pos[x];
			pos[x] = n++;
		} else if(cnt[n - 1] < m) {
			++cnt[n - 1];
		}
	}
	memset(f, -1, sizeof f);
	printf("%d\n", F(0, n - 1, 0));
	return 0;
}
