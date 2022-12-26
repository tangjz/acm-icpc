#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 3;
int n, m, tot, pL[maxn], pR[maxn];
LL a[maxn], ans;
priority_queue<pair<LL, int> > Q;
int main() {
	scanf("%d%d", &tot, &m);
	while(tot--) {
		int x;
		scanf("%d", &x);
		if(!n || (x > 0 && a[n] < 0) || (x < 0 && a[n] > 0))
			++n;
		a[n] += x;
	}
	if(!a[n])
		--n;
	for(int i = 1; i <= n; ++i)
		if(a[i] > 0) {
			ans += a[i];
			--m;
		}
	if(m >= 0) {
		printf("%lld\n", ans);
		return 0;
	}
	pL[0] = 0;
	pR[0] = 1;
	for(int i = 1; i <= n; ++i) {
		Q.push(make_pair(-abs(a[i]), i));
		pL[i] = i - 1;
		pR[i] = i + 1;
	}
	pL[n + 1] = n;
	pR[n + 1] = n + 1;
	while(m < 0) {
		pair<LL, int> tmp = Q.top();
		Q.pop();
		int mid = tmp.second, lft = pL[mid], rht = pR[mid];
		if(pL[pR[mid]] != mid || (a[mid] <= 0 && (lft < 1 || rht > n)))
			continue;
		ans += tmp.first;
		++m;
		if(lft >= 1 && rht <= n) {
			a[mid] += a[lft] + a[rht];
			Q.push(make_pair(-abs(a[mid]), mid));
		}
		pL[mid] = pL[lft];
		pR[mid] = pR[rht];
		pL[pR[rht]] = pR[pL[lft]] = mid;
	}
	printf("%lld\n", ans);
	return 0;
}
