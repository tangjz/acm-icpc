#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 9;
int t, n;
char buf[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%s", &n, buf);
		n = (n - 1) * 2;
		for(int i = 0; i < n; ++i)
			buf[i] = 'S' - buf[i] + 'E';
		printf("Case #%d: %s\n", Case, buf);
	}
	return 0;
}