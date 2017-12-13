#include <bits/stdc++.h>
using namespace std;
int n, a[3][7], ord[3];
bool vis[1001];
void dfs(int dep, int val) {
	if(dep == n) {
		vis[val] = 1;
		return;
	}
	dfs(dep + 1, val);
	for(int i = 0; i < 6; ++i)
		dfs(dep + 1, val * 10 + a[ord[dep]][i]);
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		ord[i] = i;
		for(int j = 0; j < 6; ++j)
			scanf("%d", a[i] + j);
	}
	do dfs(0, 0); while(next_permutation(ord, ord + n));
	for(int i = 1; ; ++i)
		if(!vis[i]) {
			printf("%d\n", i - 1);
			break;
		}
	return 0;
}
