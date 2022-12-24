#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1;
int n, m, a[maxn], pL[maxn], pR[maxn], ans;
priority_queue<pair<int, int> > Q;
int main() {
	scanf("%d%d", &n, &m);
	if(n < m + m) {
		puts("Error!");
		return 0;
	}
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		Q.push(make_pair(a[i], i));
		pL[i] = i - 1;
		pR[i - 1] = i;
	}
	pL[0] = n - 1;
	pR[n - 1] = 0;
	for(int i = 0; i < m; ++i) {
		pair<int, int> tmp;
		do {
			tmp = Q.top();
			Q.pop();
		} while(!(pL[pR[tmp.second]] == tmp.second && pR[pL[tmp.second]] == tmp.second));
		int mid = tmp.second, lft = pL[mid], rht = pR[mid];
		ans += tmp.first;
		tmp.first = a[mid] = a[lft] + a[rht] - tmp.first;
		Q.push(tmp);
		pL[mid] = pL[lft];
		pR[mid] = pR[rht];
		pR[pL[lft]] = pL[pR[rht]] = mid;
	}
	printf("%d\n", ans);
	return 0;
}