#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, m, a[maxn], fz, fm = 1, pl, pr;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = n, j = i; i >= 1; --i)
		for( ; j > 1 && a[i] - a[j - 1] <= m; --j)
			if(j < i) {
				int tfz = a[i] - a[j], tfm = a[i] - a[j - 1];
				if((LL)fz * tfm < (LL)tfz * fm) {
					fz = tfz;
					fm = tfm;
				}
			}
	if(fz) {
        printf("%.20f\n", (double)fz / fm);
    } else {
		puts("-1");
	}
	return 0;
}
