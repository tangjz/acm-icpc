/*
 * 石子合并...
 */
#include <queue>
#include <cstdio>
using namespace std;
int n;
long long ans;
priority_queue<int, vector<int>, greater<int> > Q;
int main() {
	scanf("%d", &n);
	for(int i = 0, j; i < n; ++i) {
		scanf("%d", &j);
		Q.push(j);
	}
	for(int i = 1, j; i < n; ++i) {
		j = Q.top(); Q.pop();
		j += Q.top(); Q.pop();
		ans += j;
		Q.push(j);
	}
	printf("%lld\n", ans);
}
