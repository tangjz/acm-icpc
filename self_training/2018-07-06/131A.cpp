#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, L, R, pos[maxn], ord[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		int v;
		scanf("%d", &v);
		pos[v] = ord[i] = i;
	}
	L = 1;
	R = n;
	scanf("%d", &m);
	while(m--) {
		char op[5];
		int val;
		scanf("%s%d", op, &val);
		pos[val] = op[0] == 'F' ? --L : ++R;
	}
	sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
		return pos[u] < pos[v];
	});
	for(int i = 1; i <= n; ++i)
		printf("%d%c", ord[i], " \n"[i == n]);
	return 0;
}
