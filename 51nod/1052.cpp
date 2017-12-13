#include <set>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 5001;
int n, m, tot, L[maxn], R[maxn];
LL a[maxn], ans;
set<pair<LL, int> > sp;
int main() {
	scanf("%d%d", &tot, &m);
	while(tot--) {
		int x;
		scanf("%d", &x);
		if((x > 0 && a[n] < 0) || (x < 0 && a[n] > 0)) {
			L[n] = n - 1;
			R[n] = n + 1;
			sp.insert(make_pair(abs(a[n]), n));
			a[++n] = 0;
		}
		a[n] += x;
	}
	if(a[n]) {
		L[n] = n - 1;
		R[n] = n + 1;
		sp.insert(make_pair(abs(a[n]), n));
		++n;
	}
	for(int i = 0; i < n; ++i)
		if(a[i] > 0) {
			--m;
			ans += a[i];
		}
	while(m < 0) {
		int pos = sp.begin() -> second;
		sp.erase(make_pair(abs(a[pos]), pos));
		if(a[pos] <= 0 && (L[pos] < 0 || R[pos] >= n)) {
			L[R[pos]] = L[pos];
			R[L[pos]] = R[pos];
			continue;
		}
		ans -= abs(a[pos]);
		if(L[pos] >= 0) {
			int tp = L[pos];
			sp.erase(make_pair(abs(a[tp]), tp));
			L[R[tp]] = L[tp];
			R[L[tp]] = R[tp];
			a[pos] += a[tp];
		}
		if(R[pos] < n) {
			int tp = R[pos];
			sp.erase(make_pair(abs(a[tp]), tp));
			L[R[tp]] = L[tp];
			R[L[tp]] = R[tp];
			a[pos] += a[tp];
		}
		++m;
		sp.insert(make_pair(abs(a[pos]), pos));
	}
	printf("%lld\n", ans);
	return 0;
}
