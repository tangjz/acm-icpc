#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int t, n, a[maxn], b[maxn];
bool check() {
	for(int i = 1; i <= n; ++i)
		b[i] = 0;
	for(int o = 1; o <= 2; ++o) {
		for(int i = o; i < n; i += 2) {
			int u = a[i], v = a[i + 1];
			if(u > v)
				swap(u, v);
			b[u] = v;
		}
		set<int> sp;
		sp.insert(maxn);
		for(int i = 1; i <= n; ++i) {
			if(!b[i])
				continue;
			int low = *sp.begin();
			while(low <= i) {
				sp.erase(sp.begin());
				low = *sp.begin();
			}
			if(b[i] > low)
				return 0;
			sp.insert(b[i]);
			b[i] = 0;
		}
	}
	return 1;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			a[x] = i;
		}
		puts(check() ? "Yes" : "No");
	}
	return 0;
}