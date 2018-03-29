#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1;
int n, m, x;
priority_queue<int> Q;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, j = 1; i <= n; ++i) {
		for( ; j <= n && j <= i + m; ++j) {
			scanf("%d", &x);
			Q.push(-x);
		}
		printf("%d\n", -Q.top());
		Q.pop();
	}
	return 0;
}
