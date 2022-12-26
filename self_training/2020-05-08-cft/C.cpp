#include <bits/stdc++.h>
using namespace std;
const char *pat = "NWSE";
const int maxn = (int)1e5 + 1, dt[][2] = {
	{-1, 0}, {0, -1}, {1, 0}, {0, 1}
};
int main() {
	int t = 1;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int tot = 0;
		static pair<int, int> seq[maxn];
		static char buf[maxn];
		scanf("%s", buf);
		for(int i = 0, cx = 0, cy = 0, nx, ny; buf[i]; ++i, cx = nx, cy = ny)
			for(int j = 0; pat[j]; ++j)
				if(buf[i] == pat[j]) {
					nx = cx + dt[j][0];
					ny = cy + dt[j][1];
					seq[tot++] = make_pair(cx + nx, cy + ny);
					break;
				}
		int ans = tot;
		sort(seq, seq + tot);
		ans += (unique(seq, seq + tot) - seq) << 2;
		printf("%d\n", ans);
	}
	return 0;
}