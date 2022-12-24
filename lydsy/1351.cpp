#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1;
int n, x[maxn], y[maxn], s[maxn], c[maxn], dsu[maxn];
int dsu_find(int x) {
	return x == dsu[x] ? x : (dsu[x] = dsu_find(dsu[x]));
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d%d", x + i, y + i, s + i);
		dsu[i] = i;
	}
	for(int i = 1; i <= n; ++i) {
		int fz = s[i], fm = 1, ctr = 0, pos;
		for(int j = 1; j <= n; ++j) {
			if(i == j)
				continue;
			int tfz = s[j], tfm = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
			if(fz * tfm < tfz * fm) {
				fz = tfz;
				fm = tfm;
				ctr = 0;
			}
			if(fz * tfm == tfz * fm) {
				++ctr;
				pos = j;
			}
		}
		if(fz == fm * s[i])
			ctr = 0; 
		if(ctr == 1)
			dsu[dsu_find(i)] = dsu_find(pos);
		c[i] = ctr;
	}
	for(int i = 1; i <= n; ++i)
		if(c[i] == 1) {
			printf("%d\n", dsu_find(i));
		} else {
			puts(c[i] ? "D" : "K");
		}
	return 0;
}
