#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1;
int t, x, y, z, px, py, pz, lbt[maxn];
inline int lcm(int x, int y) {
	return x / __gcd(x, y) * y;
}
int main() {
	for(int i = 1; i < maxn; ++i)
		lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
	assert(scanf("%d", &t) == 1 && 1 <= t && t <= 1000);
	while(t--) {
		assert(scanf("%d%d%d", &x, &y, &z) == 3 && 5 <= min(x, min(y, z)) && max(x, max(y, z)) <= 1000);
		int upp = 2 * lcm(x, lcm(y, z)), x2 = x + x, y2 = y + y, z2 = z + z;
		long long mx = 0;
		for(int len = x + y + z; len >= 1; --len)
			for(int i = min(x, len); i >= 0; --i)
				for(int j = min(y, len - i), k = len - i - j; j >= 0 && k <= z; --j, ++k) {
					if(__gcd(i, __gcd(j, k)) > 1)
						continue;
					if(i && j && lbt[i] + lbt[y] == lbt[x] + lbt[j])
						continue;
					if(i && k && lbt[i] + lbt[z] == lbt[x] + lbt[k])
						continue;
					if(j && k && lbt[j] + lbt[z] == lbt[y] + lbt[k])
						continue;
					int tim = lcm(x2 / __gcd(x2, i), lcm(y2 / __gcd(y2, j), z2 / __gcd(z2, k)));
					long long dis = (long long)tim * len;
					if(mx < dis) {
						mx = dis;
						px = i;
						py = j;
						pz = k;
					}
					if(tim == upp)
						goto finished;
				}
finished:
		printf("%d %d %d\n", px, py, pz);
	}
	return 0;
}
