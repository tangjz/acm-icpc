#include <bits/stdc++.h>
using namespace std;
const int maxn = 2540161, maxd = 10;
int fact[maxd], f[maxn], ans;
int main() {
	fact[0] = 1;
	for(int i = 1; i < maxd; ++i) {
		f[i] = fact[i] = fact[i - 1] * i;
	}
	for(int i = maxd; i < maxn; ++i) {
		f[i] = f[i / 10] + fact[i % 10];
		if(f[i] == i)
			ans += i;
	}
	printf("%d\n", ans);
	return 0;
}
