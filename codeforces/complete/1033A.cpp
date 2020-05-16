#include <bits/stdc++.h>
using namespace std;
int n, x[3], y[3];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < 3; ++i) {
		scanf("%d%d", x + i, y + i);
		if(i > 0) {
			x[i] -= x[0];
			y[i] -= y[0];
		}
	}
	puts(x[1] * x[2] > 0 && y[1] * y[2] > 0 ? "YES" : "NO");
	return 0;
}
