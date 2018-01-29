#include <bits/stdc++.h>
using namespace std;
const int maxn = 53;
double f[maxn], g[maxn];
int main() {
	f[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		g[i] = 1;
		f[i] = (f[i] + (i - 1) * f[i - 1] + f[i - 2]) / i;
		for(int j = i - 1; j >= 1; --j) {
			f[j] = (f[j] + (j - 1) * f[j - 1] + (j > 1 ? (i - j + 1) * f[j - 2] : 0)) / i;
			g[i] += f[j] * g[j];
		}
		g[i] /= 1 - f[i];
		printf("%d: %.8f\n", i, g[i] - (i > 0));
	}
	return 0;
}
