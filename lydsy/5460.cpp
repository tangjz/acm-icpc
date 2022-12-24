#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxd = 61;
int n, pos[maxd];
LL x[maxn], sum, ans;
bool vis[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", x + i);
		sum ^= x[i];
	}
	for(int i = maxd - 1; i >= 0; --i) {
		if((sum >> i) & 1)
			continue;
		for(int j = 1; j <= n; ++j)
			if(!vis[j] && (x[j] >> i) & 1)
				if(pos[i]) {
					x[j] ^= x[pos[i]];
				} else {
					pos[i] = j;
					vis[j] = 1;
				}
		if(pos[i] && !((ans >> i) & 1))
			ans ^= x[pos[i]];
	}
	for(int i = maxd - 1; i >= 0; --i) {
		if(!((sum >> i) & 1))
			continue;
		for(int j = 1; j <= n; ++j)
			if(!vis[j] && (x[j] >> i) & 1)
				if(pos[i]) {
					x[j] ^= x[pos[i]];
				} else if(!vis[j]) {
					pos[i] = j;
					vis[j] = 1;
				}
		if(pos[i] && ((ans >> i) & 1))
			ans ^= x[pos[i]];
	}
	printf("%lld\n", ans);
	return 0;
}
