#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, INF = 0x3f3f3f3f;
int n, m, dt, que[maxn], msk[maxn], f[2][maxn];
void init() {
	int m1, m2;
	static int p1[maxn], p2[maxn];
	scanf("%d%d%d%d", &n, &m1, &m2, &dt);
	for(int i = 0; i < m1; ++i) {
		scanf("%d", p1 + i);
		que[m++] = p1[i];
	}
	for(int i = 0; i < m2; ++i) {
		scanf("%d", p2 + i);
		que[m++] = p2[i];
	}
	que[m++] = -1;
	sort(que, que + m);
	m = unique(que, que + m) - que;
	for(int i = 0; i < m1; ++i)
		msk[lower_bound(que, que + m, p1[i]) - que] |= 1;
	for(int i = 0; i < m2; ++i)
		msk[lower_bound(que, que + m, p2[i]) - que] |= 2;
}
void solve() {
	f[0][0] = 0;
	f[1][0] = INF;
	for(int i = 1; i < m; ++i) {
		int f0 = f[0][i - 1], f1 = f[1][i - 1];
		if(que[i - 1] + 1 < que[i]) { // switch before que[i]
			int las = que[i - 1] + 1 - dt;
			int g0 = max(f1, las), g1 = max(f0, las);
			f0 = min(f0, g0);
			f1 = min(f1, g1);
		}
		f[0][i] = msk[i] & 1 ? (f0 + dt < que[i] ? f0 + dt : INF) : f0;
		f[1][i] = msk[i] & 2 ? (f1 + dt < que[i] ? f1 + dt : INF) : f1;
		{ // switch at que[i]
			int las = que[i] - dt;
			int g0 = max(f[1][i], las), g1 = max(f[0][i], las);
			msk[i] == 2 && (f[0][i] = min(f[0][i], g0));
			msk[i] == 1 && (f[1][i] = min(f[1][i], g1));
		}
	}
}
void print() {
	if(f[0][m - 1] == INF && f[1][m - 1] == INF) {
		puts("No");
		return;
	}
	int m1 = 0, m2 = 0, o = f[0][m - 1] == INF;
	static int p1[maxn << 1 | 1], p2[maxn];
	for(int i = m - 1; i > 0; --i) {
		int f0 = f[0][i - 1], f1 = f[1][i - 1];
		if(que[i - 1] + 1 < que[i]) {
			int las = que[i - 1] + 1 - dt;
			int g0 = max(f1, las), g1 = max(f0, las);
			f0 = min(f0, g0);
			f1 = min(f1, g1);
		}
		int pre = !o ? f0 : f1, cur = msk[i] & (1 << o) ? (pre + dt < que[i] ? pre + dt : INF) : pre;
		if(f[o][i] != cur) {
			p1[m1++] = que[i];
			o = !o;
			pre = !o ? f0 : f1;
		}
		if(msk[i] & (1 << o)) {
			p2[m2++] = f[o][i] << 1 | o;
		}
		if(f[o][i - 1] != pre) {
			p1[m1++] = que[i - 1] + 1;
			o = !o;
		}
	}
	puts("Yes");
	printf("%d\n", m1);
	for(int i = m1 - 1; i >= 0; --i)
		printf("%d%c", p1[i], " \n"[i == 0]);
	printf("%d\n", m2);
	for(int i = m2 - 1; i >= 0; --i)
		printf("%d %d\n", p2[i] >> 1, (p2[i] & 1) + 1);
}
int main() {
	init();
	solve();
	print();
	return 0;
}
