#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 61, maxm = (int)1e4 + 1;
int t, n, sz[2];
LL sum, vec[maxn];
pair<LL, LL> f[2][maxm];
void modify(int &sz, pair<LL, LL> f[], LL dt) { // dt > 0
	int tp = 0;
	for(int i = 0, j = 0; i < sz; ++i) {
		if(!f[i].second)
			continue;
		for(LL nxt = f[i].first + dt; j < sz && f[j].first < nxt; ++j);
		if(j < sz)
			f[j].second -= f[i].second;
		f[tp++] = f[i];
	}
	sz = tp;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", sz + 0);
		for(int i = 0; i < sz[0]; ++i)
			scanf("%lld", &f[0][i].first);
		for(int i = 0; i < sz[0]; ++i)
			scanf("%lld", &f[0][i].second);
		sort(f[0], f[0] + sz[0]);
		sum = -f[0][0].first;
		for(int i = 0; i < sz[0]; ++i)
			f[0][i].first += sum;
		sz[1] = sz[0];
		memcpy(f[1], f[0], sz[0] * sizeof(pair<LL, LL>));
		n = 0;
		while(f[0][0].second > 1) {
			vec[n++] = 0;
			for(int i = 0; i < sz[0]; ++i)
				f[0][i].second >>= 1;
		}
		while(sz[0] > 1)
			modify(sz[0], f[0], vec[n++] = f[0][1].first);
		for(int i = n - 1; sum > 0; --i) {
			modify(sz[1], f[1], vec[i]);
			LL nxt = sum - vec[i];
			for(int j = 0; j < sz[1]; ++j)
				if(f[1][j].first == nxt) {
					sum = nxt;
					vec[i] = -vec[i];
					break;
				}
		}
		sort(vec, vec + n);
		printf("Case #%d:", Case);
		for(int i = 0; i < n; ++i)
			printf(" %lld", vec[i]);
		printf("\n");
	}
	return 0;
}
