#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxm = 26;
int n, m, que[maxm + 1], ans;
char buf[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < maxm; ++i)
		que[m++] = i;
	for(int i = 1; i <= n; ++i) {
		char op[3];
		scanf("%s%s", op, buf);
		if(i == n)
			break;
		bool vis[maxm + 1] = {};
		for(int j = 0; buf[j]; ++j)
			vis[buf[j] - 'a'] = 1;
		if(op[0] == '!') {
			ans += m == 1;
			int sz = 0;
			for(int j = 0; j < m; ++j)
				if(vis[que[j]])
					que[sz++] = que[j];
			m = sz;
		} else {
			ans += m == 1 && op[0] == '?';
			int sz = 0;
			for(int j = 0; j < m; ++j)
				if(!vis[que[j]])
					que[sz++] = que[j];
			m = sz;
		}
	}
	printf("%d\n", ans);
	return 0;
}
