#include <bits/stdc++.h>
using namespace std;
const int maxw = 13, maxd = 1 << 13 | 1, maxs = 531441;
int w, n, m, pw3[maxw], msk[maxd], cnt[maxd], ans[maxs], pat[maxw];
int dfs(int dep, int mask) {
	return dep < n ? dfs(dep + 1, mask) + dfs(dep + 1, mask + pat[dep]) : ans[mask];
}
int main() {
	scanf("%d%d%d", &w, &n, &m);
	pw3[0] = 1;
	for(int i = 1; i < w; ++i)
		pw3[i] = pw3[i - 1] * 3;
	for(int i = 1; i < (1 << w); ++i)
		msk[i] = msk[i >> 1] * 3 + (i & 1);
	for(int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		++cnt[x];
	}
	for(int i = 0; i < (1 << w); ++i)
		for(int j = 0; j < (1 << w); ++j)
			ans[msk[i] + msk[j]] += cnt[i] * cnt[j];
	while(m--) {
		char buf[maxw];
		scanf("%s", buf);
		int mask = 0;
		n = 0;
		for(int i = 0; i < w; ++i)
			switch(buf[w - 1 - i]) {
				case 'A' : {
					pat[n++] = pw3[i];
					break;
				}
				case 'O' : {
					break;
				}
				case 'X' : {
					pat[n++] = pw3[i] + pw3[i];
					break;
				}
				case 'a' : {
					mask += pw3[i] + pw3[i];
					break;
				}
				case 'o' : {
					mask += pw3[i];
					pat[n++] = pw3[i];
					break;
				}
				case 'x' : {
					mask += pw3[i];
					break;
				}
			}
		printf("%d\n", dfs(0, mask));
	}
	return 0;
}
