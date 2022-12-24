#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int t, n, a[maxn], b[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i < n; ++i)
			scanf("%d", b + i);
		bool chk = 1;
		for(int i = 0; chk && i < n; ++i) {
			if(i + 2 < n && a[i] < b[i]) {
				int dt = b[i] - a[i];
				a[i] += dt;
				a[i + 1] += dt + dt;
				a[i + 2] += dt + dt + dt;
			}
			chk &= a[i] == b[i];
		}
		puts(chk ? "TAK" : "NIE");
	}
	return 0;
}