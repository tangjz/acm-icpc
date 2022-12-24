#include <bits/stdc++.h>
bool init(int &n, int &L, int &R) {
	if(scanf("%d", &n) != 1)
		return 0;
	L = R = -1;
	for(int i = 0, x; i <= n; ++i) {
		scanf("%d", &x);
		if(!x)
			continue;
		if(L == -1)
			L = i;
		R = i;
	}
	return 1;
}
int main() {
	int n, aL, aR, m, bL, bR;
	while(init(n, aL, aR) && init(m, bL, bR))
		puts(aL * m <= bL * n && bR * n <= aR * m ? "YES" : "NO");
	return 0;
}