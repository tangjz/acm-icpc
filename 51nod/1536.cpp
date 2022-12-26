#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1, maxe = 5;
int n, pr[maxn][maxe], ans;
int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i) {
		if(!pr[i][0])
			for(int j = i; j <= n; j += i)
				pr[j][++pr[j][0]] = i;
		ans += pr[i][0] == 1;
	}
	printf("%d\n", ans);
	return 0;
}
