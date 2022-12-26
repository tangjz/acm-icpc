#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1;
int n, m, ans;
pair<int, int> rem[maxn];
priority_queue<int, vector<int>, greater<int> > lft, rht, sp;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(x <= y) {
			rem[m++] = make_pair(x, y);
		} else {
			lft.push(x);
			rht.push(y);
			++ans;
		}
	}
	sort(rem, rem + m);
	reverse(rem, rem + m);
	while(!lft.empty()) {
		int x = lft.top();
		lft.pop();
		int y = rht.top();
		rht.pop();
		while(x > y) {
			while(m > 0 && rem[m - 1].first <= y)
				sp.push(-rem[--m].second);
			if(sp.empty()) {
				puts("-1");
				return 0;
			}
			rht.push(-sp.top());
			sp.pop();
			y = rht.top();
			rht.pop();
			++ans;
		}
	}
	printf("%d\n", ans);
	return 0;
}
