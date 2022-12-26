#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
#define x first
#define y second
const int maxn = (int)3e5 + 1, maxd = 26, mod = (int)1e9 + 7;

int main() {
	int t = 1;
	// scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int n;
		LL k;
		static int a[maxn];
		scanf("%d%lld", &n, &k);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		const LL INF = (LL)4e18;
		auto calc_cost = [&](int bi, int ai) {
			return bi * (ai - (LL)bi * bi);
		};
		auto calc_diff = [&](int bi, int ai) {
			return bi < ai ? ai - bi * (bi + 1LL) * 3 - 1 : -INF;
		};
		static int b[maxn];
		auto gen = [&](LL lim) {
			// printf("gen %lld\n", lim);
			for(int i = 0; i < n; ++i) {
				int L = 0, R = a[i];
				while(L < R) {
					int M = (L + R) / 2;
					if(calc_diff(M, a[i]) < lim) {
						R = M;
					} else {
						L = M + 1;
					}
				}
				b[i] = L;
				// printf("%d%c", b[i], " \n"[i == n - 1]);
			}
		};
		LL L = -INF, R = INF;
		while(L < R) {
			LL M = L + (R - L + 1) / 2;
			gen(M);
			LL cnt = 0;
			for(int i = 0; i < n; ++i)
				cnt += b[i];
			if(cnt < k) {
				R = M - 1;
			} else {
				L = M;
			}
		}
		gen(L + 1);
		LL rem = k;
		priority_queue<pair<LL, int> > Q;
		for(int i = 0; i < n; ++i) {
			rem -= b[i];
			if(b[i] < a[i])
				Q.push(make_pair(calc_diff(b[i], a[i]), i));
		}
		for( ; rem > 0; --rem) {
			int i = Q.top().second;
			Q.pop();
			if((++b[i]) < a[i])
				Q.push(make_pair(calc_diff(b[i], a[i]), i));
		}
		for(int i = 0; i < n; ++i)
			printf("%d%c", b[i], " \n"[i == n - 1]);
	}
	return 0;
}