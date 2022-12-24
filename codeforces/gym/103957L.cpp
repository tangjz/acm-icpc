#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 1001, maxm = 1000001;
int t, n, m, tot, a[maxm], x[maxm], y[maxm];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		tot = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j) {
				char buf[11];
				scanf("%s", buf);
				if(buf[0] == '?')
					continue;
				x[tot] = i;
				y[tot] = j;
				sscanf(buf, "%d", a + (tot++));
			}
		bool chk = !tot;
		if(!chk)
			for(int i = 1; i * i <= a[0]; ++i) {
				if(a[0] % i > 0)
					continue;
				int px = i, py = a[0] / i;
				if(px - x[0] > 0 && py - y[0] > 0) {
					int sx = px - x[0], sy = py - y[0];
					bool flg = 1;
					for(int j = 1; j < tot && flg; ++j)
						flg &= (LL)(sx + x[j]) * (sy + y[j]) == a[j];
					if((chk |= flg))
						break;
				}
				std::swap(px, py);
				if(px - x[0] > 0 && py - y[0] > 0) {
					int sx = px - x[0], sy = py - y[0];
					bool flg = 1;
					for(int j = 1; j < tot && flg; ++j)
						flg &= (LL)(sx + x[j]) * (sy + y[j]) == a[j];
					if((chk |= flg))
						break;
				}
			}
		printf("Case #%d: %s\n", Case, chk ? "Yes" : "No");
	}
	return 0;
}
