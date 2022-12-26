#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, a[maxn], f[maxn], g[maxn];
vector<int> d[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		f[i] += i;
		d[i].push_back(i);
		for(int j = i + i; j <= n; j += i) {
			f[j] -= f[i];
			d[j].push_back(i);
		}
	}
	LL ans = 0;
	for(int i = 1; i <= n; ++i) {
		LL sum = 0;
		for(int j = i; j <= n; j += i) {
			vector<int> &cur = d[a[j]];
			for(vector<int>::iterator it = cur.begin(); it != cur.end(); ++it)
				++g[*it];
		}
		for(int j = i; j <= n; j += i) {
			vector<int> &cur = d[a[j]];
			for(vector<int>::iterator it = cur.begin(); it != cur.end(); ++it)
				if(g[*it]) {
					int k = *it;
					sum += (LL)g[k] * g[k] * f[k];
					g[k] = 0;
				}
		}
		ans += sum * f[i];
	}
	printf("%lld\n", ans % ((int)1e9 + 7));
	return 0;
}
