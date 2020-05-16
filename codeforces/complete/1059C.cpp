#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
inline int calc(int x) {
	return x / (x >> 1);
}
int main() {
	int n, m = 1;
	scanf("%d", &n);
	while(n > 1) {
		int k = n / (n >> 1);
		for(int i = 1; i <= n; ++i)
			if(i % k > 0)
				printf("%d ", m);
		n /= k;
		m *= k;
	}
	printf("%d\n", m);
	return 0;
}
