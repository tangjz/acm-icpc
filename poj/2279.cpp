#include <cstdio>
#include <cstring>
const int maxn = 31;
int tot, pr[maxn], d[maxn], cnt[maxn];
int n, m, a[maxn], R[maxn][maxn], D[maxn][maxn];
bool can[maxn][maxn];
int main() {
	d[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	while(scanf("%d", &n) == 1 && n) {
		m = 0;
		for(int i = 0; i < n; ++i) {
			scanf("%d", a + i);
			memset(can[i], 0, (a[0] + 1) * sizeof(bool));
			for(int j = 0; j < a[i]; ++j)
				can[i][j] = 1;
			m += a[i];
		}
		memset(can[n], 0, (a[0] + 1) * sizeof(bool));
		for(int i = 1; i <= m; ++i)
			cnt[i] = 1;
		for(int i = n - 1; i >= 0; --i)
			for(int j = a[i] - 1; j >= 0; --j) {
				R[i][j] = can[i][j + 1] ? R[i][j + 1] + 1 : 1;
				D[i][j] = can[i + 1][j] ? D[i + 1][j] + 1 : 1;
				--cnt[R[i][j] + D[i][j] - 1];
			}
		unsigned ans = 1, tmp;
		for(int i = m; i > 1; --i)
			if(d[i] == i) {
				for(tmp = i; cnt[i] > 0; tmp *= tmp, cnt[i] >>= 1)
					(cnt[i] & 1) && (ans *= tmp);
			} else {
				cnt[d[i]] += cnt[i];
				cnt[i / d[i]] += cnt[i];
			}
		printf("%u\n", ans);
	}
	return 0;
}
