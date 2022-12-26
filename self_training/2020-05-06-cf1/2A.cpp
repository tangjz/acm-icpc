#include <bits/stdc++.h>
using namespace std;
int main() {
	int t, n, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		if(n > m)
			swap(n, m);
		puts(n == 1 || m == 2 ? "YES" : "NO");
	}
	return 0;
}