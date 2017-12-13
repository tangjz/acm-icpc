#include <set>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int n, m, tot, b[maxn], L[maxn], R[maxn];
LL a[maxn], ans;
set<pair<LL, int> > sp;
int main() {
	scanf("%d%d", &tot, &m);
	int pJ = 0, pL = 0, nJ = 0, nL = 0;
	LL pF = 0, pC = 0, nF = 0, nC = 0;
	for(int i = 0; i < tot; ++i) {
		scanf("%d", b + i);
		ans += b[i];
		if(pC + b[i] >= 0) {
			pC += b[i];
			if(pF < pC) {
				pF = pC;
				pL = pJ + 1;
			}
		} else {
			pC = 0;
			pJ = i;
		}
		if(nC - b[i] >= 0) {
			nC -= b[i];
			if(nF < nC) {
				nF = nC;
				nL = nJ + 1;
			}
		} else {
			nC = 0;
			nJ = i;
		}
	}
	if(pF >= ans + nF) {
		rotate(b, b + pL, b + tot);
	} else {
		rotate(b, b + nL, b + tot);
	}
	ans = 0;
	for(int i = 0; i < tot; ++i) {
		if((b[i] > 0 && a[n] < 0) || (b[i] < 0 && a[n] > 0)) {
			L[n] = n - 1;
			R[n] = n + 1;
			sp.insert(make_pair(abs(a[n]), n));
			a[++n] = 0;
		}
		a[n] += b[i];
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
