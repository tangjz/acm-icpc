#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int t, n, sz[maxn], mx[maxn][2], seq[maxn], ans;
vector<int> a[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		ans = sz[0] = maxn;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", seq + 0);
			for(int j = 1; j <= seq[0]; ++j)
				scanf("%d", seq + j);
			sort(seq + 1, seq + seq[0] + 1);
			sz[i] = unique(seq + 1, seq + seq[0] + 1) - seq - 1;
			if(sz[i] < seq[0])
				ans = min(ans, sz[i] + 1);
			a[i].reserve(sz[i]);
			for(int j = 1; j <= sz[i]; ++j) {
				a[i].push_back(seq[j]);
				int tmp = i;
				if(sz[mx[seq[j]][0]] > sz[tmp])
					swap(mx[seq[j]][0], tmp);
				if(sz[mx[seq[j]][1]] > sz[tmp])
					swap(mx[seq[j]][1], tmp);
			}
		}
		for(int i = 1; i <= n; ++i) {
			for(int j = 0; j < sz[i]; ++j)
				seq[j + 1] = mx[a[i][j]][0] == i ? sz[mx[a[i][j]][1]] : sz[mx[a[i][j]][0]];
			sort(seq + 1, seq + sz[i] + 1, greater<int>());
			for(int j = 1; j <= sz[i]; ++j)
				ans = min(ans, seq[j] + j);
		}
		printf("%d\n", ans);
		for(int i = 1; i <= n; ++i) {
			for(int j = 0; j < sz[i]; ++j)
				mx[a[i][j]][0] = mx[a[i][j]][1] = 0;
			vector<int>().swap(a[i]);
		}
	}
	return 0;
}
