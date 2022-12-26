#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1 << 20 | 1;
int n;
LL f[maxn];
int main() {
	int t;
	scanf("%d", &t);
	n = 1;
	while(t--) {
		int x, v;
		scanf("%d%d", &x, &v);
		for( ; n <= x; n <<= 1);
		f[x] += v;
	}
	for(int i = 1; i < n; i <<= 1)
		for(int j = 0; j < n; ++j)
			if(j & i)
				f[j ^ i] += f[j];
	int pos = 0;
	for(int i = 1; i <= n; ++i)
		if(f[pos] < f[i])
			pos = i;
	printf("%d %lld\n", pos, f[pos]);
	return 0;
}