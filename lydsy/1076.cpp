#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxm = 15, maxs = 1 << 15 | 1;
int n, m, val[maxm], msk[maxm], cur, pre = 1;
DB f[2][maxs];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0, x; i < m; ++i) {
		scanf("%d%d", val + i, &x);
		while(x) {
			msk[i] |= 1 << (--x);
			scanf("%d", &x);
		}
	}
	while(n--) {
		pre ^= 1;
		cur ^= 1;
		for(int i = 0; i < 1 << m; ++i) {
			f[cur][i] = 0;
			for(int j = 0; j < m; ++j)
				if((i & msk[j]) == msk[j])
					f[cur][i] += max(f[pre][i | 1 << j] + val[j], f[pre][i]);
				else
					f[cur][i] += f[pre][i];
			f[cur][i] /= m;
		}
	}
	printf("%.6f\n", f[cur][0]);
	return 0;
}
