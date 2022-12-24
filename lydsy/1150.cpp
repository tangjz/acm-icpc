#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, INF = 0x3f3f3f3f;
int n, m, a[maxn], pL[maxn], pR[maxn], ans;
priority_queue<pair<int, int> > Q;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		pL[i] = i - 1;
		pR[i - 1] = i;
	}
	pL[0] = 0;
	pR[n] = n;
	for(int i = 1; i < n; ++i) {
		a[i] -= a[i + 1];
		Q.push(make_pair(a[i], i));
	}
	a[0] = a[n] = -INF;
	for(int i = 0; i < m; ++i) {
		pair<int, int> tmp;
		do {
			tmp = Q.top();
			Q.pop();
		} while(!(pL[pR[tmp.second]] == tmp.second && pR[pL[tmp.second]] == tmp.second));
		int mid = tmp.second, lft = pL[mid], rht = pR[mid];
		ans += -tmp.first;
		if(a[lft] != -INF && a[rht] != -INF) {
			tmp.first = a[mid] = a[lft] + a[rht] - tmp.first;
			Q.push(tmp);
		} else {
			a[mid] = -INF;
		}
		pL[mid] = pL[lft];
		pR[mid] = pR[rht];
		pR[pL[lft]] = pL[pR[rht]] = mid;
	}
	printf("%d\n", ans);
	return 0;
}