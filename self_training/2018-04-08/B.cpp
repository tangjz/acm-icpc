#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int t, n, a[maxn], b[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i < n; i += 2)
			b[i >> 1] = a[i];
		sort(b, b + ((n + 1) >> 1));
		for(int i = 0; i < n; i += 2)
			a[i] = b[i >> 1];
		for(int i = 1; i < n; i += 2)
			b[i >> 1] = a[i];
		sort(b, b + (n >> 1));
		for(int i = 1; i < n; i += 2)
			a[i] = b[i >> 1];
		int pos = -1;
		for(int i = 1; i < n; ++i)
			if(a[i - 1] > a[i]) {
				pos = i - 1;
				break;
			}
		if(pos >= 0) {
			printf("Case #%d: %d\n", Case, pos);
		} else {
			printf("Case #%d: OK\n", Case);
		}
	}
	return 0;
}
