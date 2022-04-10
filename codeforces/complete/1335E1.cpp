#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1, maxm = 201, mod = (int)1e9 + 7;
int t, n, m, que[maxm], tim[maxm];
vector<int> pos[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		m = 0;
		for(int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			if(tim[x] != Case) {
				tim[x] = Case;
				vector<int>().swap(pos[x]);
				que[m++] = x;
			}
			pos[x].push_back(i);
		}
		int ans = 0;
		for(int i = 0; i < m; ++i) {
			int u = que[i], uLen = (int)pos[u].size();
			ans = max(ans, uLen);
			for(int j = 0; j < m; ++j) {
				if(i == j)
					continue;
				int v = que[j], vLen = (int)pos[v].size();
				for(int uL = 0, uR = uLen - 1, vL = 0, vR = vLen - 1; uL < uR; ++uL, --uR) {
					for( ; vL <= vR && pos[v][vL] < pos[u][uL]; ++vL);
					for( ; vL <= vR && pos[u][uR] < pos[v][vR]; --vR);
					if(vL > vR)
						break;
					ans = max(ans, vR - vL + 1 + (uL + 1) * 2);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}