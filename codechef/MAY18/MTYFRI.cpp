#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e4 + 1, INF = (int)2e5;
int t, n, m, dif;
multiset<int> s[2];
int main() {
	scanf("%d", &t);
	while(t--) {
		dif = 0;
		multiset<int>().swap(s[0]);
		multiset<int>().swap(s[1]);
		scanf("%d%d", &n, &m);
		for(int i = 0, x; i < n; ++i) {
			scanf("%d", &x);
			dif += i & 1 ? x : -x;
			s[i & 1].insert(x);
		}
		while(dif <= 0 && m) {
			int u = s[0].size() ? *s[0].rbegin() : -INF;
			int v = s[1].size() ? *s[1].begin() : INF;
			int adt = (u - v) << 1;
			if(adt <= 0)
				break;
			--m;
			dif += adt;
		}
		puts(dif > 0 ? "YES" : "NO");
	}
	return 0;
}
