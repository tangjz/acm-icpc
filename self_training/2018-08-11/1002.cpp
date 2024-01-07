#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
const int maxn = (int)2e5 + 1;
int n, m;
list<int> que[maxn], rev[maxn];
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		while(m--) {
			int typ, x, y, z;
			scanf("%d%d%d", &typ, &x, &y);
			if(typ == 1) {
				scanf("%d", &z);
				if(y == 1) {
					que[x].push_back(z);
					rev[x].push_front(z);
				} else {
					que[x].push_front(z);
					rev[x].push_back(z);
				}
			} else if(typ == 2) {
				if(que[x].empty()) {
					puts("-1");
				} else if(y == 1) {
					printf("%d\n", que[x].back());
					que[x].pop_back();
					rev[x].pop_front();
				} else {
					printf("%d\n", que[x].front());
					que[x].pop_front();
					rev[x].pop_back();
				}
			} else {
				scanf("%d", &z);
				if(z == 1) {
					que[x].splice(que[x].end(), rev[y]);
					rev[x].splice(rev[x].begin(), que[y]);
				} else {
					que[x].splice(que[x].end(), que[y]);
					rev[x].splice(rev[x].begin(), rev[y]);
				}
			}
		}
		for(int i = 1; i <= n; ++i) {
			list<int>().swap(que[i]);
			list<int>().swap(rev[i]);
		}
	}
	return 0;
}
