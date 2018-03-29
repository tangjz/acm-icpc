#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> Info;
const int maxn = (int)5e3 + 1, mod = (int)1e9 + 7;
int n, a[maxn], m, seq[maxn], pos[maxn];
Info f[maxn][maxn], dif[maxn], ans;
void merge(Info &lft, Info rht) {
	if(lft.first < rht.first) {
		lft = rht;
	} else if(lft.first == rht.first) {
		(lft.second += rht.second) >= mod && (lft.second -= mod);
	}
}
int main() {
	while(scanf("%d", &n) == 1) {
		for(int i = 0; i < n; ++i) {
			scanf("%d", a + i);
			f[i][i] = (Info){1, 1};
			seq[i] = a[i];
		}
		sort(seq, seq + n);
		m = unique(seq, seq + n) - seq;
		for(int i = 0; i < n; ++i)
			a[i] = lower_bound(seq, seq + m, a[i]) - seq;
		for(int i = 0; i < m; ++i)
			pos[i] = n;
		for(int i = n - 1; i >= 0; --i) {
			Info tmp = (Info){0, 1};
			for(int j = 0; j < m; ++j)
				dif[j] = (Info){0, 0};
			for(int j = i + 1; j < n; ++j)
				if(a[j] <= a[i]) {
					if(a[j] == a[i])
						f[i][j] = (Info){tmp.first + 2, tmp.second};
					int val = a[j], idx = pos[val];
					if(idx <= j) {
						assert(a[idx] == a[j]);
						merge(tmp, dif[val]);
						merge(tmp, f[idx][j]);
						dif[val] = f[idx][j];
						if(dif[val].second)
							dif[val].second = mod - dif[val].second;
					}
				}
			pos[a[i]] = i;
		}
		ans = (Info){0, 0};
		for(int i = 0, j; i < m; ++i) {
			for(j = n - 1; j >= 0 && a[j] != i; --j);
			merge(ans, f[pos[i]][j]);
		}
		printf("%d %d\n", ans.first, ans.second);
	}
	return 0;
}
