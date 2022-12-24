#include <bits/stdc++.h>
using namespace std;
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	if((n == 2 && m == 2) || m + m > n) {
		puts("NIE");
	} else {
		int p = n >> 1;
		for(int i = p + 1, j = 1; i <= n; ++i, ++j) {
			printf("%d ", i);
			if(j <= p)
				printf("%d ", j);
		}
	}
	return 0;
}