#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = (int)3e5 + 1, maxd = 26, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n, m;
		static int cnt[maxn], upp[maxn];
		scanf("%d%d", &n, &m);
		memset(cnt + 1, 0, m * sizeof(int));
		for(int i = 1; i <= n; ++i) {
			int x;
			scanf("%d", &x);
			++cnt[x];
		}
		for(int i = 1; i <= m; ++i)
			scanf("%d", upp + i);
		int tot = 0;
		for(int i = m, sum = 0; i >= 1; --i) {
			sum += cnt[i];
			if(sum > 0)
				tot = max(tot, (sum - 1) / upp[i] + 1);
		}
		static vector<int> out[maxn];
		for(int i = 0; i < tot; ++i)
			vector<int>().swap(out[i]);
		for(int i = m, pos = 0; i >= 1; --i)
			while(cnt[i]--) {
				out[pos].push_back(i);
				(++pos) == tot && (pos = 0);
			}
		printf("%d\n", tot);
		for(int i = 0; i < tot; ++i) {
			printf("%d", (int)out[i].size());
			for(int &x : out[i])
				printf(" %d", x);
			puts("");
		}
	}
	return 0;
}