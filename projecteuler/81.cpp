#include <bits/stdc++.h>
using namespace std;
const int maxn = 80;
int f[maxn | 1];
int main() {
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for(int i = 0; i < maxn; ++i)
		for(int j = 0, x; j < maxn; ++j) {
			scanf("%d%*c", &x);
			if(j && f[j - 1] < f[j])
				f[j] = f[j - 1];
			f[j] += x;
		}
	printf("%d\n", f[maxn - 1]);
	return 0;
}
