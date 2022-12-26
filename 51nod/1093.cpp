#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
int n, m, ans;
int main() {
	scanf("%d%d", &n, &m);
	DB rem = n;
	for(int i = 1; ; i += 2)
		if(rem * i >= m) {
			rem -= (DB)m / i;
			ans += m;
		} else {
			ans += (int)ceil(rem * i);
			break;
		}
	printf("%d\n", ans);
	return 0;
}
