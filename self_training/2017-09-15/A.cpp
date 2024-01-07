#include <bits/stdc++.h>
using namespace std;
int t, Case, n;
map<int, int> f;
inline int F(int x) {
	if(f.count(x))
		return f[x];
	return f[x] = max(x & 1 ? F(x * 3 + 1) : F(x >> 1), x);
}
int main() {
	f[1] = 1;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &Case, &n);
		printf("%d %d\n", Case, F(n));
	}
	return 0;
}
